#ifndef GAME_STATE_H
#define GAME_STATE_H

/* Game state file initializes the game */

#include "../include/Pieces.h"

typedef struct
{
    piece ***board;
    char moves[200][7];
    int movesNumber;
} gameState;

void constructNormalBoard(gameState *theGame);

void displayBoard(gameState *theGame);

void allKingMoves(piece *apiece, gameState *theGame);

#endif