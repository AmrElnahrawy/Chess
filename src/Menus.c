#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/SaveLoad.h"
#include "../include/Utilities.h"
#include "../include/GameState.h"
#include "../include/Menus.h"

void startNormalGame() {
    gameState *theGame = (gameState*)malloc(sizeof(gameState));
    if (theGame == NULL) {
        printf("ERROR: Not enough memory\n");
        getchar();
        exit(0);
    }
    constructNormalBoard(theGame);
    while(1) {
        system("clear"); 
        printf("TO Exit press ( x )\n");
        printf("TO Save press ( s )\n");
        printf("TO Undo press ( u )\n");
        printf("=======================================================\n");
        displayBoard(theGame);
        printf("=======================================================\n");
        if (theGame->movesNumber % 2 == 0) {
            printf("White to move: ");
        } else {
            printf("Black to move: ");
        }
        char *move = pieceMoveInput();
        /////////////////////////////////////////////////////////////////////////////////////
        if (!move) {
            printf("Invalid move1\n"); 
            continue;
        } else if (move[0] == 'x') {
            // memory leak still exist
            freeBoard(theGame);
            return;
        } else if (move[0] == 's') {
            if (saveGame(theGame))
                return;
        } else if (move[0] == 'u') {
            
        }

        if (theGame->movesNumber == 0)
            allWhitePiecesMoves(theGame, theGame->allWhite);
        
        moveStoI(move , theGame->moves[theGame->movesNumber]);
        if (checkMoveValidity(theGame->moves[theGame->movesNumber], theGame)) {
            printf("Valid move\n");
            doMove(theGame->moves[theGame->movesNumber], theGame);
        }
        else {
            printf("Invalid move\n");
            getchar();
            continue;
        }
        getchar();
        if (theGame->movesNumber % 2 == 0) // Update other player's view 
            allBlackPiecesMoves(theGame, theGame->allBlack);
        else
            allWhitePiecesMoves(theGame, theGame->allWhite);
        /////////////////////////////////////////////////////////
        viewAllPiecesMoves(theGame->allWhite, theGame->allBlack);
        getchar();
        /////////////////////////////////////////////////////////
        theGame->movesNumber++;
        free(move);
    }
    free(theGame);
}

void displayMainMenu()
{
    while(1)
    {
        int choice = 0;
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
            startNormalGame();
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