#ifndef GAME_STATE_H
#define GAME_STATE_H

/* Game state file initializes the game */

#include "../include/Pieces.h"

typedef struct
{
    piece ***board;
    piece *allWhite[16]; // r n b q k b n r p ...
    piece *allBlack[16];
    int moves[400][5];   // from from to to (promotion/flag) -> 1 for en passant, 2 for left castling, 3 for right castling "flags are updated in checkMoveValidity"
    int movesNumber;
} gameState;

void constructNormalBoard(gameState *theGame);

void freeBoard(gameState *theGame);

void displayBoard(gameState *theGame);

void allKingMoves(piece *apiece, gameState *theGame);

void allBishopMoves(piece *aPiece, gameState *theGame);

void allQueenMoves(piece *aPiece, gameState *theGame);

void allKnightMoves(piece *aPiece, gameState *theGame);

void allPawnMoves(piece *aPiece, gameState *theGame);

void allWhitePiecesMoves(gameState *theGame, piece **allWhite);

void allBlackPiecesMoves(gameState *theGame, piece **allBlack);

int isKingInCheck(gameState *theGame, piece *king);

int checkMoveValidity(int *move, gameState *theGame);

void currentBoardString(gameState *theGame);

void doMove(int *move, gameState *theGame);

void undo(gameState *theGame,int moves[400][5], int movesNumber);

int repetition(char* boardString, int boardStringNumber);

int insufficientPieces(gameState *theGame);

int auxiliaryMove(gameState *theGame, int color, int move[5]);

int finalCheck(gameState *theGame, piece **allWhite, piece **allBlack);

/////////////// test functions "will be deleted" ///////////////

void viewAllPiecesMoves(piece **allWhite, piece **allBlack);

#endif
