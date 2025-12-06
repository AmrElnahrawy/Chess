#ifndef GAME_STATE_H
#define GAME_STATE_H

/* Game state file initializes the game */

#include "../include/Pieces.h"

typedef struct
{
    piece ***board;
    piece *allWhite[16];
    piece *allBlack[16];
    char moves[200][7];
    int movesNumber;
} gameState;

void constructNormalBoard(gameState *theGame);

void displayBoard(gameState *theGame);

void allKingMoves(piece *apiece, gameState *theGame);

void allBishopMoves(piece *aPiece, gameState *theGame);

void allQueenMoves(piece *aPiece, gameState *theGame);

void allKnightMoves(piece *aPiece, gameState *theGame);

void allPawnMoves(piece *aPiece, gameState *theGame);

void allPiecesMoves(gameState *theGame, piece **allWhite, piece **allBlack);



/////////////// test functions "will be deleted" ///////////////

void viewAllPiecesMoves(piece **allWhite, piece **allBlack);

#endif
