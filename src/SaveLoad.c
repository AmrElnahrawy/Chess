#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/GameState.h"
#include "../include/SaveLoad.h"

#ifdef _WIN32
    #define localtime_safe(timer, buf) (localtime_s(buf, timer) == 0 ? buf : NULL)
#else
    #define localtime_safe(timer, buf) localtime_r(timer, buf)
#endif

int saveGame(gameState *theGame) {
    struct tm temp;
    time_t t = time(NULL);

    if (localtime_safe(&t, &temp) == NULL) {
        printf("Couldn't save game.\n");
        return 0;
    }
    
    char fileName[30];
    if (strftime(fileName, sizeof(fileName), "%m-%d-%y_%I-%M-%S%p", &temp) == 0) {
        printf("Couldn't save game.\n");
        return 0;
    }

    char filesrc[50];
    snprintf(filesrc, sizeof(filesrc), "saves/%s.txt", fileName);

    FILE* fptr = fopen(filesrc, "w");
    if (fptr == NULL) {
        printf("Couldn't save game.\n");
        getchar();
        return 0;
    }
    
    for (int i = 0; i < theGame->movesNumber; i++) {
        for (int j = 0; j < 5; j++) {
            fprintf(fptr, "%d ", theGame->moves[i][j]);
        }
        if (i != theGame->movesNumber - 1)
            fprintf(fptr, "\n");
    }

    fclose(fptr);
    printf("The game has been saved correctly.\n");
    return 1;
}

void loadGame(gameState *theGame ,char* fileName) {    
    char filesrc[100];
    snprintf(filesrc, sizeof(filesrc), "saves/%s.txt", fileName);

    FILE* fptr;
    fptr = fopen(filesrc, "r");
    if (fptr == NULL) {
        printf("Couldn't load game.\n");
        getchar();
        exit(0);
    }

    int i = 0;
    while (fscanf(fptr, "%d %d %d %d %d", &theGame->moves[i][0], &theGame->moves[i][1], &theGame->moves[i][2], &theGame->moves[i][3], &theGame->moves[i][4]) == 5) {
        doMove(theGame->moves[i], theGame);
        i++;
        theGame->movesNumber = i;
        if (i > 398)
            break;
    }

    fclose(fptr);
    return;
}