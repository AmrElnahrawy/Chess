#include <stdio.h>
#include <stdlib.h>
#include "../include/Pieces.h"
#include "../include/CheckState.h"
#include "../include/GameState.h"

void constructNormalBoard(gameState *theGame)
{
    theGame->movesNumber = 0;
    theGame->board = (piece ***)malloc(8 * sizeof(piece **));
    if (theGame->board == NULL) {
        free(theGame->board);
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
                if (i == 1) {
                    theGame->board[i][j]->type = 'P';
                }
                else if (i == 6) {
                    theGame->board[i][j]->type = 'p';
                }
                else if (i == 0) {
                    theGame->board[i][j]->type = blackPieces[j];
                }
                else if (i == 7) {
                    theGame->board[i][j]->type = whitePieces[j];
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
    printf("   ╔═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╗\n");
    for (int i = 0; i < 8; i++)
    {
        printf(" %d ║", i + 1);
        for (int j = 0; j < 8; j++)
        {
            if (theGame->board[i][j] && theGame->board[i][j])
            {
                printf("  %c  ║", theGame->board[i][j]->type);
            }
            else if ((i + j) % 2 == 0)
            {
                printf("  -  ║");
            }
            else
            {
                printf("  ·  ║");
            }
        }
        printf(" %d\n", i + 1);
        if (i != 7)
            printf("   ╠═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╣\n");
    }
    printf("   ╚═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╝\n");
    printf("      A     B     C     D     E     F     G     H   \n");
}

// Castling is handled separately
void allKingMoves(piece *aPiece, gameState *theGame) {
    int movesCounter = 0;
    int currentPosition[2] = {aPiece->position[0] , aPiece->position[1]};
    int di[8] = {1 ,1 ,0 ,-1,-1,-1,0 ,1 };
    int dj[8] = {0 ,1 ,1 , 1,0 ,-1,-1,-1};
    for (int d = 0; d < 8; d++) {
        if (0 < currentPosition[0] + di[d] && currentPosition[0] + di[d] < 9) {
            if (0 < currentPosition[1] + dj[d] && currentPosition[1] + dj[d] < 9) {
                if (!theGame->board[currentPosition[0] + di[d]][currentPosition[1] + dj[d]]) {
                    theGame->moves[movesCounter][0] = currentPosition[0] + di[d];
                    theGame->moves[movesCounter][1] = currentPosition[1] + dj[d];
                    movesCounter++;
                    continue;
                }
                if (theGame->board[currentPosition[0] + di[d]][currentPosition[1] + dj[d]]->color != aPiece->color) {
                    theGame->moves[movesCounter][0] = currentPosition[0] + di[d];
                    theGame->moves[movesCounter][1] = currentPosition[1] + dj[d];
                    movesCounter++;
                    continue;
                }
            }
        }
    }
    return;
}