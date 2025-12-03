#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Utilities.h"
#include "../include/GameState.h"
#include "../include/Menus.h"

void startNormalGame() {
    gameState *theGame = (gameState*)malloc(sizeof(gameState));
    constructNormalBoard(theGame);
    while(1) {
        system("clear");
        printf("TO Exit press ( x )\n");
        printf("TO Save press ( s )\n");
        printf("-------------------------------------------------------\n");
        displayBoard(theGame);
        printf("-------------------------------------------------------\n");
        if (theGame->movesNumber % 2 == 0) {
            printf("White to move: ");
        } else {
            printf("Black to move: ");
        }
        char *move = pieceMoveInput();
        if (move)
            printf("%s\n", move);
        else
            printf("Invalid move\n");    
        getchar();
        free(move);
    }
    free(theGame);
}

int displayModeMenu()
{
    int choice = 0;
    char input[100];
    do
    {
        system("clear"); // clear console
        printf("1) Normal \n");
        printf("2) Fischer Random\n");
        printf("3) return\n");
        printf("Enter Option number: ");
        choice = singleDigitInput();
    } while (choice < 1 || 3 < choice);
    if (choice == 1)
    {
        startNormalGame();
    }
    else if (choice == 2)
    {
        return 0;
    }
    else if (choice == 3)
    {
        return 0;
    }
    return 0;
}

void displayMainMenu()
{
    while(1)
    {
        int choice = 0;
        char input[100];
        do
        {
            system("clear"); // clear console
            printf("1) New Game\n");
            printf("2) Load Game\n");
            printf("3) Exit\n");
            printf("Enter Option number: ");
            choice = singleDigitInput();
        } while (choice < 1 || 3 < choice);

        if (choice == 1)
        {
            if (displayModeMenu() == 0);
                continue;
        }
        else if (choice == 2)
        {
        }
        else if (choice == 3)
        {
            exit(0);
        }
    }
}