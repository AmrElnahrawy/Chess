#ifndef PIECES_H
#define PIECES_H

/* Pieces file holds all the pieces features */

typedef struct
{
    char type;
    int moves;
    int unposson;
    int captured;
} piece;


#endif