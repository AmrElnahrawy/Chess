#ifndef PIECES_H
#define PIECES_H

/* Pieces file holds all the pieces features */

typedef struct
{
    char type; // piece 
    int color; // 0 White , 1 Black
    int position[2]; // it's cell on the board
    int hasMoved;
    int enPassant;
    int captured;
    int **pieceView;
} piece;

void constructPieceView(piece *aPiece);

#endif