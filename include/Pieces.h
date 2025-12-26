#ifndef PIECES_H
#define PIECES_H

/* Pieces file holds all the pieces features */

typedef struct
{
    char type;         // piece char
    int color;         // 0 White , 1 Black
    int position[2];   // its cell on the board
    int hasMoved;      // 0
    int enPassant;     // 0 Check if this piece can be captured
    int captured;      // 0
    int **pieceView; 
    int pieceViewSize; // for the king: 8 for left and 9 for right castling
} piece;

void constructPieceView(piece *aPiece);

void freePieceView(piece *aPiece, int pieceviewSize);

#endif