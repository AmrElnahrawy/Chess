#include <stdio.h>
#include <stdlib.h>
#include "../include/Pieces.h"
#include "../include/GameState.h"

void constructNormalBoard(gameState *theGame)
{
    theGame->movesNumber = 0;
    theGame->board = (piece ***)malloc(8 * sizeof(piece **));
    if (theGame->board == NULL) {
        printf("ERROR: Not enough memory\n");
        getchar();
        exit(0);
    }
    for (int i = 0; i < 8; i++) {
        theGame->board[i] = (piece **)malloc(8 * sizeof(piece *));
        if (theGame->board[i] == NULL) {
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
                if (theGame->board[i][j] == NULL) {
                    printf("ERROR: Not enough memory\n");
                    getchar();
                    exit(0);
                }
                theGame->board[i][j]->captured = 0;
                theGame->board[i][j]->position[0] = i;
                theGame->board[i][j]->position[1] = j;
                theGame->board[i][j]->hasMoved = 0;
                if (i == 1) {
                    theGame->allBlack[8 + j] = theGame->board[i][j];
                    theGame->board[i][j]->type = 'P';
                    theGame->board[i][j]->color = 1;
                    constructPieceView(theGame->board[i][j]);
                }
                else if (i == 6) {
                    theGame->allWhite[8 + j] = theGame->board[i][j];
                    theGame->board[i][j]->type = 'p';
                    theGame->board[i][j]->color = 0;
                    constructPieceView(theGame->board[i][j]);
                }
                else if (i == 0) {
                    theGame->allBlack[j] = theGame->board[i][j];
                    theGame->board[i][j]->type = blackPieces[j];
                    theGame->board[i][j]->color = 1;
                    constructPieceView(theGame->board[i][j]);
                }
                else if (i == 7) {
                    theGame->allWhite[j] = theGame->board[i][j];
                    theGame->board[i][j]->type = whitePieces[j];
                    theGame->board[i][j]->color = 0;
                    constructPieceView(theGame->board[i][j]);
                }
            }
        }
    }
}

void freeBoard(gameState *theGame)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            free(theGame->board[i][j]);
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
                printf("  ·  |");
            }
        }
        printf(" %d\n", 8 - i);
        if (i != 7)
            printf("   +-----+-----+-----+-----+-----+-----+-----+-----+\n");
    }
    printf("   +-----+-----+-----+-----+-----+-----+-----+-----+\n");
    printf("      A     B     C     D     E     F     G     H   \n");
}

void allKingMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[8] = {1 ,1 ,0 ,-1,-1,-1,0 ,1 };
    int dj[8] = {0 ,1 ,1 , 1,0 ,-1,-1,-1};
    for (int d = 0; d < 8; d++) {
        int ni=currentPosition[0] + di[d];
        int nj=currentPosition[1] + dj[d];
            if (0 <= ni && ni < 8 && 0 <= nj && nj < 8) {
                if (!theGame->board[ni][nj]) {
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                }
                else if (theGame->board[ni][nj]->color != aPiece->color) {
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                }
            }
        
    }
    return;
}
void allRookMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[4] = {1, -1, 0, 0};
    int dj[4] = {0, 0, 1, -1};
    for (int d = 0; d < 4; d++) {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        while (0 <= ni && ni < 8 && 0 <= nj && nj < 8) {
            if (!theGame->board[ni][nj]){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                    ni+= di[d];
                    nj+= dj[d];
            }
            else{
                if(theGame->board[ni][nj]->color != aPiece->color){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;                   
                }
                break;
            }
        }
    }
    return;
}

void allBishopMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[4] = {1,-1, 1,-1};
    int dj[4] = {1, 1,-1,-1};
    for (int d = 0; d < 4; d++) {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        while (0 <= ni && ni < 8 && 0 <= nj && nj < 8) {
            if (!theGame->board[ni][nj]){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                    ni+= di[d];
                    nj+= dj[d];
            }
            else{
                if(theGame->board[ni][nj]->color != aPiece->color){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;                   
                }
                break;
            }
        }
    }
    return;
}

void allQueenMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[8] = {1,-1, 1,-1,1,0,-1,0};
    int dj[8] = {1, 1,-1,-1,0,1, 0,-1};
    for (int d = 0; d < 8; d++) {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        while (0 <= ni && ni < 8 && 0 <= nj && nj < 8) {
            if (!theGame->board[ni][nj]){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
                    ni+= di[d];
                    nj+= dj[d];
            }
            else{
                if(theGame->board[ni][nj]->color != aPiece->color){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;                   
                }
                break;
            }
        }
    }
    return;
}

void allKnightMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[8] = {1,2,2,1,-1,-2,-1,-2};
    int dj[8] = {2,1,-1,-2,2,1,-2,-1};
    for (int d = 0; d < 8; d++) {
        int ni = currentPosition[0] + di[d];
        int nj = currentPosition[1] + dj[d];
        if (0 <= ni && ni < 8 && 0 <= nj && nj < 8) {
            if (!theGame->board[ni][nj]||theGame->board[ni][nj]->color != aPiece->color){
                    aPiece->pieceView[movesCounter][0] = ni;
                    aPiece->pieceView[movesCounter][1] = nj;
                    movesCounter++;
            }

        }
    }
    return;
}

void allPawnMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[3] = {1 ,1 ,-1};
    int dj[3] = {0 ,1 ,1};
    for (int d = 0; d < 3; d++) {
        int ni=currentPosition[0] + di[d];
        int nj=currentPosition[1] + dj[d];
        if (0 <= ni && ni < 8 && 0 <= nj && nj < 8) {
            if (!theGame->board[ni][nj]&&(di[d]==1&&dj[d]==0)) {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
            }
            else if (theGame->board[ni][nj]) 
                if (theGame->board[ni][nj]->color != aPiece->color&&(di[d]!=1&&dj[d]!=0)) {
                aPiece->pieceView[movesCounter][0] = ni;
                aPiece->pieceView[movesCounter][1] = nj;
                movesCounter++;
            }
        }
        
    }
    return;
}

void allPiecesMoves(gameState *theGame, piece **allWhite, piece **allBlack) {
    for(int i=0;i<16;i++){
        piece *aPiece = allWhite[i];
        if (aPiece == NULL) continue;
        switch(aPiece->type){
        case'k': 
            allKingMoves(aPiece, theGame);break;
        case'r': 
            allRookMoves(aPiece, theGame);break;
        case'b':
            allBishopMoves(aPiece, theGame);break;
        case'q':
            allQueenMoves(aPiece, theGame);break;
        case'n':
            allKnightMoves(aPiece, theGame);break;
        case'p':
            allPawnMoves(aPiece, theGame);break;        
        }
    }
    for(int i=0;i<16;i++){
        piece *aPiece = allBlack[i];
        if (aPiece == NULL) continue;
        switch(aPiece->type){
        case'K': 
            allKingMoves(aPiece, theGame);break;
        case'R': 
            allRookMoves(aPiece, theGame);break;
        case'B':
            allBishopMoves(aPiece, theGame);break;
        case'Q':
            allQueenMoves(aPiece, theGame);break;
        case'N':
            allKnightMoves(aPiece, theGame);break;
        case'P':
            allPawnMoves(aPiece, theGame);break;        
        }
    }
    return;
}



/////////////// test functions "will be deleted" ///////////////

void viewAllPiecesMoves(piece **allWhite, piece **allBlack) {
    printf("White Pieces view\n");
    for (int i = 0; i < 16; i++) {
        if (allWhite[i]->captured == 1)
            continue;
        printf("%c (%d,%d):\n",allWhite[i]->type, allWhite[i]->position[0], allWhite[i]->position[1]);
        for (int j = 0; j < allWhite[i]->pieceViewSize; j++) {
            printf("    (%d,%d)\n", allWhite[i]->pieceView[j][0], allWhite[i]->pieceView[j][1]);
        }
    }
    printf("Black Pieces view\n");
    for (int i = 0; i < 16; i++) {
        if (allBlack[i]->captured == 1)
            continue;
        printf("%c (%d,%d):\n",allBlack[i]->type, allBlack[i]->position[0], allBlack[i]->position[1]);
        for (int j = 0; j < allBlack[i]->pieceViewSize; j++) {
            printf("    (%d,%d)\n", allBlack[i]->pieceView[j][0], allBlack[i]->pieceView[j][1]);
        }
    }
}