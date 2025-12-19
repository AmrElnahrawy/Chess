#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Utilities.h"

int singleDigitInput() {
    int number = 0;
    char input[100];
    if (fgets(input, sizeof(input), stdin))
    {
        if (input[1] != '\n' || input[2] != '\0')
            return number;
        if (sscanf(input, "%d", &number) != 1)
            return 0;
    }
    return number;
}

char *pieceMoveInput() {
    char input[100];
    char *move = (char*)malloc(6);
    if (move == NULL) {
        printf("ERROR: Not enough memory\n");
        getchar();
        free(move);
        return NULL;
    }
    if (fgets(input, 100, stdin) == NULL) {
        free(move);
        return NULL;
    }

    if (input[0] == 'X' && input[1] == '\n' && input[2] == '\0') {
        move[0] = 'X';
        move[1] = '\0';
        return move;
    } else if (input[0] == 'S' && input[1] == '\n' && input[2] == '\0') {
        move[0] = 'S';
        move[1] = '\0';
        return move;
    } else if (input[0] == 'U' && input[1] == '\n' && input[2] == '\0') {
        move[0] = 'U';
        move[1] = '\0';
        return move;
    }


    if (input[0] < 'A' || input[0] > 'H') {
        free(move);
        return NULL;
    }
    else if (input[1] < '1' || input[1] > '8') {
        free(move);
        return NULL;
    }
    else if (input[2] < 'A' || input[2] > 'H') {
        free(move);
        return NULL;
    }
    else if (input[3] < '1' || input[3] > '8') {
        free(move);
        return NULL;
    }
    else if (input[0] == input[2] && input[1] == input[3]) {
        free(move);
        return NULL;
    }

    if (input[4] == '\n') {
        if (input[5] != '\0') {
            free(move);
            return NULL;
        }

        strncpy(move, input, 4);
        move[4] = '\0';

    } else if (input[4] == 'R' || input[4] == 'N' || input[4] == 'B' || input[4] == 'Q') {
        if (input[5] != '\n') {
            free(move);
            return NULL;
        } 
        if (input[6] != '\0') {
            free(move);
            return NULL;
        }

        strncpy(move, input, 5);
        move[5] = '\0';

    } else {
        free(move);
        return NULL;
    }

    return move;
}

void moveStoI(char *move, int *moves) {
    moves[4] = 0;
    int i = 0;
    while (move[i] != '\0') {
        if (i == 4) {
            moves[i] = (int) move[i];
        } else if ('A' <= move[i] && move[i] <= 'H') {     
            moves[i] = (int) move[i] - (int) 'A';
        } else if ('1' <= move[i] && move[i] <= '8') {
            moves[i] = (int) '8' - (int) move[i]; 
        }
        i++;
    }
    return;
}

char *loadInput() {
    char input[100];
    char *fileName = (char*)malloc(50);
    if (fileName == NULL) {
        return fileName;
    }
    if (fgets(input, 100, stdin) == NULL) {
        return fileName;
    }
    if (input[20] != '\0') {
        return fileName;
    } else {
        input[strlen(input) - 1] = '\0';
    }

    strcpy(fileName, input);
    return fileName;
}