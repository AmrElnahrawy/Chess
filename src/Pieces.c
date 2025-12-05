#include <stdio.h>
#include <stdlib.h>
#include "../include/GameState.h"
#include "../include/Pieces.h"

// the caller must free it
void constructPieceView(piece *aPiece) {
    int rows = 0;
    if (aPiece->type == 'p' || aPiece->type == 'P') {
        rows = 3;
    }
    else if (aPiece->type == 'r' || aPiece->type == 'R') {
        rows = 14;
    }
    else if (aPiece->type == 'n' || aPiece->type == 'N') {
        rows = 8;
    }
    else if (aPiece->type == 'b' || aPiece->type == 'B') {
        rows = 13;
    }
    else if (aPiece->type == 'q' || aPiece->type == 'Q') {
        rows = 27;
    }
    else if (aPiece->type == 'k' || aPiece->type == 'K') {
        rows = 8;
    }

    aPiece->pieceView = (int**)malloc(rows * sizeof(int*));
    if (aPiece->pieceView == NULL) {
        printf("ERROR: Not enough memory\n");
        getchar();
        exit(0);
    }
    for (int i = 0; i < rows; i++) {
        aPiece->pieceView[i] = (int*)calloc(2 , sizeof(int));
        if (aPiece->pieceView[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(aPiece->pieceView[j]);
            }
            free(aPiece->pieceView);
            aPiece->pieceView = NULL;
            printf("ERROR: Not enough memory\n");
            getchar();
            exit(0);
        }
    }
}

