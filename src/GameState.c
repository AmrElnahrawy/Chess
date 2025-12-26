#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Pieces.h"
#include "../include/GameState.h"

void constructNormalBoard(gameState *theGame)
{
    theGame->movesNumber = 0;
    theGame->board = (piece ***)malloc(8 * sizeof(piece **));
    if (theGame->board == NULL)
    {
        printf("ERROR: Not enough memory\n");
        getchar();
        exit(0);
    }
    for (int i = 0; i < 8; i++)
    {
        theGame->board[i] = (piece **)malloc(8 * sizeof(piece *));
        if (theGame->board[i] == NULL)
        {
            printf("ERROR: Not enough memory\n");
            getchar();
            exit(0);
        }
    }

    char blackPieces[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    char whitePieces[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (1 < i && i < 6)
            {
                theGame->board[i][j] = NULL;
            }
            else
            {
                theGame->board[i][j] = (piece *)malloc(sizeof(piece));
                if (theGame->board[i][j] == NULL)
                {
                    printf("ERROR: Not enough memory\n");
                    getchar();
                    exit(0);
                }
                theGame->board[i][j]->captured = 0;
                theGame->board[i][j]->position[0] = i;
                theGame->board[i][j]->position[1] = j;
                theGame->board[i][j]->hasMoved = 0;
                theGame->board[i][j]->enPassant = 0;
                if (i == 1)
                {
                    theGame->allBlack[8 + j] = theGame->board[i][j];
                    theGame->board[i][j]->type = 'P';
                    theGame->board[i][j]->color = 1;
                    constructPieceView(theGame->board[i][j]);
                }
                else if (i == 6)
                {
                    theGame->allWhite[8 + j] = theGame->board[i][j];
                    theGame->board[i][j]->type = 'p';
                    theGame->board[i][j]->color = 0;
                    constructPieceView(theGame->board[i][j]);
                }
                else if (i == 0)
                {
                    theGame->allBlack[j] = theGame->board[i][j];
                    theGame->board[i][j]->type = blackPieces[j];
                    theGame->board[i][j]->color = 1;
                    constructPieceView(theGame->board[i][j]);
                }
                else if (i == 7)
                {
                    theGame->allWhite[j] = theGame->board[i][j];
                    theGame->board[i][j]->type = whitePieces[j];
                    theGame->board[i][j]->color = 0;
                    constructPieceView(theGame->board[i][j]);
                }
            }
        }
    }
}

void freeBoard(gameState *theGame) {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (theGame->board[i][j] != NULL) {
                freePieceView(theGame->board[i][j], theGame->board[i][j]->pieceViewSize);
                free(theGame->board[i][j]);
            }
        }
        free(theGame->board[i]);
    }
    free(theGame->board);
}

void displayBoard(gameState *theGame)
{
    printf("      A     B     C     D     E     F     G     H   \n");
    printf("   +-----+-----+-----+-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < 8; i++)
    {
        printf(" %d |", 8 - i);
        for (int j = 0; j < 8; j++)
        {
            if (theGame->board[i][j] && theGame->board[i][j])
            {
                printf("  %c  |", theGame->board[i][j]->type);
            }
            else if ((i + j) % 2 == 0)
            {
                printf("  -  |");
            }
            else
            {
                printf("  .  |");
            }
        }
        printf(" %d\n", 8 - i);
        if (i != 7)
            printf("   +-----+-----+-----+-----+-----+-----+-----+-----+\n");
    }
    printf("   +-----+-----+-----+-----+-----+-----+-----+-----+\n");
    printf("      A     B     C     D     E     F     G     H   \n");
}

void allKingMoves(piece *aPiece, gameState *theGame)
{
    int movesCounter = 0;
    int i0 = aPiece->position[0];
    int j0 = aPiece->position[1];
    int di[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dj[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    for (int d = 0; d < 8; d++)
    {
        int ni = i0 + di[d];
        int nj = j0 + dj[d];
        if (0 <= ni && ni < 8 && 0 <= nj && nj < 8)
        {
            if (!theGame->board[ni][nj])
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
            }
            else if (theGame->board[ni][nj]->color != aPiece->color)
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
            }
        }
    }

    for (int i = movesCounter; i < 8; i++) {
        aPiece->pieceView[i][0] = 0;
        aPiece->pieceView[i][1] = 0;
    }

    aPiece->pieceView[8][0] = 0;
    aPiece->pieceView[8][1] = 0;
    aPiece->pieceView[9][0] = 0;
    aPiece->pieceView[9][1] = 0;

    movesCounter = 8;

    if (aPiece->color == 0)
    {
        if (aPiece->hasMoved != 0)
        {
            return;
        }
        if (theGame->allWhite[0]->hasMoved == 0 && theGame->allWhite[0]->captured != 1)
        {
            if (!theGame->board[i0][1] && !theGame->board[i0][2] && !theGame->board[i0][3])
            {
                aPiece->pieceView[movesCounter][0] = i0;
                aPiece->pieceView[movesCounter][1] = j0 - 2;
            }
        }
        movesCounter++;
        if (theGame->allWhite[7]->hasMoved == 0 && theGame->allWhite[7]->captured != 1)
        {
            if (!theGame->board[i0][5] && !theGame->board[i0][6])
            {
                aPiece->pieceView[movesCounter][0] = i0;
                aPiece->pieceView[movesCounter][1] = j0 + 2;
            }
        }
    }
    else
    {
        if (aPiece->hasMoved != 0)
        {
            return;
        }
        if (theGame->allBlack[0]->hasMoved == 0 && theGame->allBlack[0]->captured != 1)
        {
            if (!theGame->board[i0][1] && !theGame->board[i0][2] && !theGame->board[i0][3])
            {
                aPiece->pieceView[movesCounter][0] = i0;
                aPiece->pieceView[movesCounter][1] = j0 - 2;
            }
        }
        movesCounter++;
        if (theGame->allBlack[7]->hasMoved == 0 && theGame->allBlack[7]->captured != 1)
        {
            if (!theGame->board[i0][5] && !theGame->board[i0][6])
            {
                aPiece->pieceView[movesCounter][0] = i0;
                aPiece->pieceView[movesCounter][1] = j0 + 2;
            }
        }
    }

    return;
}

void allRookMoves(piece *aPiece, gameState *theGame)
{
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0], aPiece->position[1]};
    int di[4] = {1, -1, 0, 0};
    int dj[4] = {0, 0, 1, -1};
    for (int d = 0; d < 4; d++)
    {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        while (0 <= ni && ni < 8 && 0 <= nj && nj < 8)
        {
            if (!theGame->board[ni][nj])
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
                ni += di[d];
                nj += dj[d];
            }
            else
            {
                if (theGame->board[ni][nj]->color != aPiece->color)
                {
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                }
                break;
            }
        }
    }

    for (int i = movesCounter; i < 14; i++) {
        aPiece->pieceView[i][0] = 0;
        aPiece->pieceView[i][1] = 0;
    }

    return;
}

void allBishopMoves(piece *aPiece, gameState *theGame)
{
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0], aPiece->position[1]};
    int di[4] = {1, -1, 1, -1};
    int dj[4] = {1, 1, -1, -1};
    for (int d = 0; d < 4; d++)
    {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        while (0 <= ni && ni < 8 && 0 <= nj && nj < 8)
        {
            if (!theGame->board[ni][nj])
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
                ni += di[d];
                nj += dj[d];
            }
            else
            {
                if (theGame->board[ni][nj]->color != aPiece->color)
                {
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                }
                break;
            }
        }
    }

    for (int i = movesCounter; i < 13; i++) {
        aPiece->pieceView[i][0] = 0;
        aPiece->pieceView[i][1] = 0;
    }

    return;
}

void allQueenMoves(piece *aPiece, gameState *theGame)
{
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0], aPiece->position[1]};
    int di[8] = {1, -1, 1, -1, 1, 0, -1, 0};
    int dj[8] = {1, 1, -1, -1, 0, 1, 0, -1};
    for (int d = 0; d < 8; d++)
    {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        while (0 <= ni && ni < 8 && 0 <= nj && nj < 8)
        {
            if (!theGame->board[ni][nj])
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
                ni += di[d];
                nj += dj[d];
            }
            else
            {
                if (theGame->board[ni][nj]->color != aPiece->color)
                {
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                }
                break;
            }
        }
    }

    for (int i = movesCounter; i < 27; i++) {
        aPiece->pieceView[i][0] = 0;
        aPiece->pieceView[i][1] = 0;
    }

    return;
}

void allKnightMoves(piece *aPiece, gameState *theGame)
{
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0], aPiece->position[1]};
    int di[8] = {1, 2, 2, 1, -1, -2, -1, -2};
    int dj[8] = {2, 1, -1, -2, 2, 1, -2, -1};
    for (int d = 0; d < 8; d++)
    {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        if (0 <= ni && ni < 8 && 0 <= nj && nj < 8)
        {
            if (!theGame->board[ni][nj] || theGame->board[ni][nj]->color != aPiece->color)
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
            }
        }
    }

    for (int i = movesCounter; i < 8; i++) {
        aPiece->pieceView[i][0] = 0;
        aPiece->pieceView[i][1] = 0;
    }
    return;
}

void allPawnMoves(piece *aPiece, gameState *theGame)
{
    
    // clear en passant before update
    aPiece->enPassant = 0;
    // En passant is stored at the end of the array
    int movesCounter = 0;
    for (int i = 0; i < 5; i++) {
        aPiece->pieceView[i][0] = 0;
        aPiece->pieceView[i][1] = 0;
    }

    int i0 = aPiece->position[0];
    int j0 = aPiece->position[1];
    int dir;
    if (aPiece->color == 0)
    {
        dir = -1;
    }
    else
    {
        dir = 1;
    }
    int ni = i0 + dir;
    int nj = j0;
    if (0 <= ni && ni < 8 && !theGame->board[ni][nj])
    {
        aPiece->pieceView[movesCounter][0] = ni;
        aPiece->pieceView[movesCounter][1] = nj;
        movesCounter++;
        if (aPiece->hasMoved == 0)
        {
            int ni2 = i0 + 2 * dir;
            if (theGame->board[ni2][nj] == NULL)
            {
                aPiece->pieceView[movesCounter][0] = ni2;
                aPiece->pieceView[movesCounter][1] = nj;
                aPiece->enPassant = 1;
                movesCounter++;
            }
        }
    }

    for (int dj = -1; dj <= 1; dj += 2)
    {
        ni = i0 + dir;
        nj = j0 + dj;
        if (0 <= ni && ni < 8 && 0 <= nj && nj < 8)
        {
            if (theGame->board[ni][nj] && theGame->board[ni][nj]->color != aPiece->color)
            {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
            }
            if (theGame->board[i0][nj] && theGame->board[i0][nj]->color != aPiece->color && theGame->board[i0][nj]->enPassant == 1)
            {
                aPiece->pieceView[4][0] = ni;
                aPiece->pieceView[4][1] = nj;
            }
        }
    }

    for (int i = movesCounter; i < 8; i++) {
        aPiece->pieceView[movesCounter][0] = 0;
        aPiece->pieceView[movesCounter][1] = 0;
    }
    return;
}

void allWhitePiecesMoves(gameState *theGame, piece **allWhite)
{
    for (int i = 0; i < 16; i++)
    {
        piece *aPiece = allWhite[i];
        if (aPiece == NULL || aPiece->captured)
            continue;
        switch (aPiece->type)
        {
        case 'k':
            allKingMoves(aPiece, theGame);
            break;
        case 'r':
            allRookMoves(aPiece, theGame);
            break;
        case 'b':
            allBishopMoves(aPiece, theGame);
            break;
        case 'q':
            allQueenMoves(aPiece, theGame);
            break;
        case 'n':
            allKnightMoves(aPiece, theGame);
            break;
        case 'p':
            allPawnMoves(aPiece, theGame);
            break;
        }
    }
    return;
}

void allBlackPiecesMoves(gameState *theGame, piece **allBlack)
{
    for (int i = 0; i < 16; i++)
    {
        piece *aPiece = allBlack[i];
        if (aPiece == NULL || aPiece->captured)
            continue;
        switch (aPiece->type)
        {
        case 'K':
            allKingMoves(aPiece, theGame);
            break;
        case 'R':
            allRookMoves(aPiece, theGame);
            break;
        case 'B':
            allBishopMoves(aPiece, theGame);
            break;
        case 'Q':
            allQueenMoves(aPiece, theGame);
            break;
        case 'N':
            allKnightMoves(aPiece, theGame);
            break;
        case 'P':
            allPawnMoves(aPiece, theGame);
            break;
        }
    }
    return;
}

int isKingInCheck(gameState *theGame, piece *king)
{
    int i = king->position[0];
    int j = king->position[1];
    int enemyColor = (king->color == 0 ? 1 : 0);

    int kdi[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int kdj[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    for (int d = 0; d < 8; d++)
    {
        int ni = i + kdi[d];
        int nj = j + kdj[d];
        if (ni < 0 || ni >= 8 || nj < 0 || nj >= 8)
            continue;
        piece *p = theGame->board[ni][nj];
        if (p && p->color == enemyColor && (p->type == 'n' || p->type == 'N'))
            return 1;
    }

    int pawnDir = (king->color == 0 ? -1 : +1);
    int pi = i + pawnDir;
    int pj1 = j + 1;
    int pj2 = j - 1;
    if (pi >= 0 && pi < 8)
    {
        if (pj1 >= 0 && pj1 < 8)
        {
            piece *p = theGame->board[pi][pj1];
            if (p && p->color == enemyColor && (p->type == 'p' || p->type == 'P'))
                return 1;
        }
        if (pj2 >= 0 && pj2 < 8)
        {
            piece *p = theGame->board[pi][pj2];
            if (p && p->color == enemyColor && (p->type == 'p' || p->type == 'P'))
                return 1;
        }
    }

    int bdi[4] = {1, -1, 1, -1};
    int bdj[4] = {1, 1, -1, -1};
    for (int d = 0; d < 4; d++)
    {
        int ni = i + bdi[d];
        int nj = j + bdj[d];
        while (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
        {
            piece *p = theGame->board[ni][nj];
            if (!p)
            {
                ni += bdi[d];
                nj += bdj[d];
                continue;
            }
            if (p->color == king->color)
                break;
            if (p->color == enemyColor &&
                (p->type == 'b' || p->type == 'B' || p->type == 'q' || p->type == 'Q'))
                return 1;
            break;
        }
    }

    int rdi[4] = {1, -1, 0, 0};
    int rdj[4] = {0, 0, 1, -1};
    for (int d = 0; d < 4; d++)
    {
        int ni = i + rdi[d];
        int nj = j + rdj[d];
        while (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
        {
            piece *p = theGame->board[ni][nj];
            if (!p)
            {
                ni += rdi[d];
                nj += rdj[d];
                continue;
            }
            if (p->color == king->color)
                break;
            if (p->color == enemyColor &&
                (p->type == 'r' || p->type == 'R' || p->type == 'q' || p->type == 'Q'))
                return 1;
            break;
        }
    }
    
    int mdi[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int mdj[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    for (int d = 0; d < 8; d++)
    {
        int ni = i + mdi[d];
        int nj = j + mdj[d];
        if (ni < 0 || ni >= 8 || nj < 0 || nj >= 8)
            continue;
        piece *p = theGame->board[ni][nj];
        if (p && p->color == enemyColor && (p->type == 'k' || p->type == 'K'))
            return 1;
    }
    return 0;
}

int checkMoveValidity(int *move, gameState *theGame)
{
    // this function doesn't check pinned pieces
    int isBlack = 1;
    if (theGame->movesNumber % 2 == 0) // 0 index
        isBlack = 0;
    if (!theGame->board[move[1]][move[0]]) // choose to move an empty cell
    {
        return 0;
    }
    if (theGame->board[move[1]][move[0]]->color != isBlack) // choose to move an oppist color piece
    {
        return 0;
    }
    if (move[3] == 0 || move[3] == 7) // pawn without promotion
    {
        if (theGame->board[move[1]][move[0]]->type == 'P' || theGame->board[move[1]][move[0]]->type == 'p')
        {
            if (move[4] == 0)
                return 0;
        }
    }
    for (int i = 0; i < theGame->board[move[1]][move[0]]->pieceViewSize; i++) // check piece view
    {
        if (theGame->board[move[1]][move[0]]->pieceView[i][0] == move[3] && theGame->board[move[1]][move[0]]->pieceView[i][1] == move[2])
        {
            if ((theGame->board[move[1]][move[0]]->type == 'p' || theGame->board[move[1]][move[0]]->type == 'P') && i == 4) // en passant
                move[4] = 1;
            if ((theGame->board[move[1]][move[0]]->type == 'k' || theGame->board[move[1]][move[0]]->type == 'K')) // castling
            {
                if (i == 8) 
                    move[4] = 2;
                else if (i == 9)
                    move[4] = 3;
            }
                
            return 1;
        }
    }
    return 0;
}

void promotion(piece *aPiece, int type) {
    freePieceView(aPiece, aPiece->pieceViewSize);
    if (aPiece->color == 1)
        aPiece->type = (char) type;
    else
        aPiece->type = (char) type + 32;
    constructPieceView(aPiece);
}

void doMove(int *move, gameState *theGame)
{
    int fromRow = move[1];
    int fromCol = move[0];
    int toRow = move[3];
    int toCol = move[2];

    if (theGame->board[toRow][toCol])
        theGame->board[toRow][toCol]->captured = 1;
    else if (move[4] == 1) // en passant
    {
        if (theGame->movesNumber % 2 == 0) {
            theGame->board[fromRow][toCol]->captured = 1;
            theGame->board[fromRow][toCol] = NULL;
        }
        else {
            theGame->board[fromRow][toCol]->captured = 1;
            theGame->board[fromRow][toCol] = NULL;
        }
    } 
    else if (move[4] == 2) // rook move in left castling
    {
        if (theGame->movesNumber % 2 == 0) {
            theGame->board[7][3] = theGame->board[7][0];
            theGame->board[7][3]->hasMoved = 1;
            theGame->board[7][3]->position[0] = 7;
            theGame->board[7][3]->position[1] = 3;
            theGame->board[7][0] = NULL;
        }
        else {
            theGame->board[0][3] = theGame->board[0][0];
            theGame->board[0][3]->hasMoved = 1;
            theGame->board[0][3]->position[0] = 0;
            theGame->board[0][3]->position[1] = 3;
            theGame->board[0][0] = NULL;
        }
    } 
    else if (move[4] == 3) // rook move in right castling
    {
        if (theGame->movesNumber % 2 == 0) {
            theGame->board[7][5] = theGame->board[7][7];
            theGame->board[7][5]->hasMoved = 1;
            theGame->board[7][5]->position[0] = 7;
            theGame->board[7][5]->position[1] = 5;
            theGame->board[7][7] = NULL;
        }
        else {
            theGame->board[0][5] = theGame->board[0][7];
            theGame->board[0][5]->hasMoved = 1;
            theGame->board[0][5]->position[0] = 0;
            theGame->board[0][5]->position[1] = 5;
            theGame->board[0][7] = NULL;
        }
    }
    
    
    theGame->board[toRow][toCol] = theGame->board[fromRow][fromCol];
    theGame->board[toRow][toCol]->hasMoved = 1;
    theGame->board[toRow][toCol]->position[0] = toRow;
    theGame->board[toRow][toCol]->position[1] = toCol;
    
    theGame->board[fromRow][fromCol] = NULL;
    
    if (move[4] > 4) {
        promotion(theGame->board[toRow][toCol], move[4]);
    }
}

void undo(gameState *theGame,int moves[400][5], int movesNumber) {
    freeBoard(theGame);
    constructNormalBoard(theGame);
    int i = 0;
    while (i < movesNumber - 1) {
        doMove(moves[i], theGame);
        i++;
    }
    theGame->movesNumber = i;
    allWhitePiecesMoves(theGame, theGame->allWhite);
    allBlackPiecesMoves(theGame, theGame->allBlack);
    return;
}

int auxiliaryMove(gameState *theGame, int color, int move[5])
{
    int flag = 0;
    int fromRow = move[1];
    int fromCol = move[0];
    int toRow = move[3];
    int toCol = move[2];

    if (move[4] == 1) // en passant
    {
        piece *temp = theGame->board[fromRow][toCol];
        theGame->board[fromRow][toCol] = NULL;
        theGame->board[toRow][toCol] = theGame->board[fromRow][fromCol];
        theGame->board[fromRow][fromCol] = NULL;

        if (color)
            flag = isKingInCheck(theGame, theGame->allBlack[4]);
        else
            flag = isKingInCheck(theGame, theGame->allWhite[4]);

        theGame->board[fromRow][fromCol] = theGame->board[toRow][toCol];
        theGame->board[fromRow][toCol] = temp;

        return flag;
    } 
    
    piece *temp = theGame->board[toRow][toCol];
    theGame->board[toRow][toCol] = theGame->board[fromRow][fromCol];
    theGame->board[fromRow][fromCol] = NULL;
    theGame->board[toRow][toCol]->position[0] = toRow;
    theGame->board[toRow][toCol]->position[1] = toCol;

    if (color)
        flag = isKingInCheck(theGame, theGame->allBlack[4]);
    else
        flag = isKingInCheck(theGame, theGame->allWhite[4]);

    theGame->board[fromRow][fromCol] = theGame->board[toRow][toCol];
    theGame->board[toRow][toCol] = temp;
    theGame->board[fromRow][fromCol]->position[0] = fromRow;
    theGame->board[fromRow][fromCol]->position[1] = fromCol;

    return flag;
}

int finalCheck(gameState *theGame, piece **allWhite, piece **allBlack) // 0 for at least one valid move, 1 no Valid move
{
    if (theGame->movesNumber % 2 == 0) // end of white's turn, check black
    {
        for (int i = 0; i < 16; i++) // check moves of each piece
        {
            if (!allBlack[i] || allBlack[i]->captured == 1)
                continue;
            for (int j = 0; j < allBlack[i]->pieceViewSize; j++) 
            {
                if (allBlack[i]->pieceView[j][0] == 0)
                    continue;

                int move[5] = {allBlack[i]->position[1], allBlack[i]->position[0], allBlack[i]->pieceView[j][1], allBlack[i]->pieceView[j][0]};
                if (allBlack[i]->type == 'P')
                {
                    if (j == 4) // enpassant check
                        move[4] = 1;
                }
                else if (allBlack[i]->type == 'K')
                    if (j == 8 || j == 9)
                        continue;
                
                int flag = auxiliaryMove(theGame, 1, move);
                if (flag == 0)
                    return 0;
                else
                {
                    allBlack[i]->pieceView[j][0] = 0;
                    allBlack[i]->pieceView[j][1] = 0;
                }
            }
        }
    }
    else // end of black's turn, check white
    {
        for (int i = 0; i < 16; i++) // check moves of each piece
        {
            if (!allWhite[i] || allWhite[i]->captured == 1)
                continue;

            for (int j = 0; j < allWhite[i]->pieceViewSize; j++) 
            {
                if (allWhite[i]->pieceView[j][0] == 0)
                    continue;

                int move[5] = {allWhite[i]->position[1], allWhite[i]->position[0], allWhite[i]->pieceView[j][1], allWhite[i]->pieceView[j][0]};
                if (allWhite[i]->type == 'p') 
                {
                    if (j == 4) // enpassant check
                        move[4] = 1;
                }
                else if (allWhite[i]->type == 'k')
                    if (j == 8 || j == 9)
                        continue;
                
                int flag = auxiliaryMove(theGame, 0, move);
                if (flag == 0)
                    return 0;
                else
                {
                    allWhite[i]->pieceView[j][0] = 0;
                    allWhite[i]->pieceView[j][1] = 0;
                }
            }
        }
    }
    return 1;
}

void currentBoardString(gameState *theGame, char boardString[66]) {
    boardString[0] = (theGame->movesNumber % 2 == 0 ? '0' : '1');
    int index = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            piece *p = theGame->board[i][j];
            if (p == NULL) {
                boardString[index] = '.';
            } else {
                boardString[index] = p->type;
            }
            index++;
        }
    }
    boardString[65] = '\0';
}

int repetition(gameState *theGame, char* boardString) {
    int repeats = 0;
    for (int i = theGame->movesNumber - 1; i >= 0; i--) {
        if (strcmp(boardString, theGame->boardString[i]) == 0) {
            repeats++;
            if (repeats >= 2) {
                return 1;
            }
        }
    }
    return 0;
}
    
int insufficientMaterial(gameState *theGame) {
    int knights = 0, bishops = 0;
    for (int i = 0; i < 16; i++)
    {
        if (theGame->allWhite[i] == NULL || theGame->allWhite[i]->captured == 1 || theGame->allWhite[i]->type == 'k')
            continue;
        switch (theGame->allWhite[i]->type)
        {
        case 'q':
        case 'r':
        case 'p':
            return 0;
        case 'b':
            bishops++;
            break;
        case 'n':
            knights++;
            break;
        }
    }
    if (knights + bishops > 1)
        return 0;   
    
    knights = 0;
    bishops = 0;         

    for (int i = 0; i < 16; i++)
    {
        if (theGame->allBlack[i] == NULL || theGame->allBlack[i]->captured == 1 || theGame->allBlack[i]->type == 'K')
            continue;
        switch (theGame->allBlack[i]->type)
        {
        case 'Q':
        case 'R':
        case 'P':
            return 0;
        case 'B':
            bishops++;
            break;
        case 'N':
            knights++;
            break;
        }
    }
    if (knights + bishops > 1)
        return 0;
    return 1;
}

/////////////// test functions "will be deleted" ///////////////

void viewAllPiecesMoves(piece **allWhite, piece **allBlack)
{
    printf("White Pieces view\n");
    for (int i = 0; i < 16; i++)
    {
        if (allWhite[i]->captured == 1)
            continue;
        printf("%c (%d,%d):\n", allWhite[i]->type, allWhite[i]->position[0], allWhite[i]->position[1]);
        for (int j = 0; j < allWhite[i]->pieceViewSize; j++)
        {
            printf("    (%d,%d)\n", allWhite[i]->pieceView[j][0], allWhite[i]->pieceView[j][1]);
        }
    }
    printf("Black Pieces view\n");
    for (int i = 0; i < 16; i++)
    {
        if (allBlack[i]->captured == 1)
            continue;
        printf("%c (%d,%d):\n", allBlack[i]->type, allBlack[i]->position[0], allBlack[i]->position[1]);
        for (int j = 0; j < allBlack[i]->pieceViewSize; j++)
        {
            printf("    (%d,%d)\n", allBlack[i]->pieceView[j][0], allBlack[i]->pieceView[j][1]);
        }
    }
}