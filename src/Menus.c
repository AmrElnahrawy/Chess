#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/GameState.h"
#include "../include/Menus.h"

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
        if (fgets(input, sizeof(input), stdin))
        {
            if (input[1] != '\n' || input[2] != '\0')
                continue;
            sscanf(input, "%d", &choice);
        }
    } while (choice < 1 || 3 < choice);
    if (choice == 1)
    {
        gameState theGame;
        constructNormalBoard(&theGame);
        system("clear");
        displayBoard(&theGame);
        getchar();
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
            if (fgets(input, sizeof(input), stdin))
            {
                if (input[1] != '\n' || input[2] != '\0')
                    continue;
                sscanf(input, "%d", &choice);
            }
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