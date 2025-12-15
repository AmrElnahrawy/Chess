#ifndef PIECES_H
#define PIECES_H

/* Pieces file holds all the pieces features */

typedef struct
{
    char type;         // piece char
    int id;            // index in allWhite and allBlack
    int color;         // 0 White , 1 Black
    int position[2];   // it's cell on the board
    int hasMoved;      // 0
    int pinned;        // 0
    int enPassant;     // 0 Check if this piece can be captured
    int captured;      // 0
    int capturedWhen;  // -1
    int **pieceView; 
    int pieceViewSize; // for the king: 8 for left and 9 for right castling
} piece;

void constructPieceView(piece *aPiece);

#endif