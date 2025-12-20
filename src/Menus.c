#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/SaveLoad.h"
#include "../include/Utilities.h"
#include "../include/GameState.h"
#include "../include/Menus.h"

void startNormalGame(int newOrLoad /*0 , 1*/, char fileName[]) {
    gameState *theGame = (gameState*)malloc(sizeof(gameState));
    if (theGame == NULL) {
        printf("ERROR: Not enough memory\n");
        getchar();
        exit(0);
    }

    constructNormalBoard(theGame);
    
    if (newOrLoad == 1)
        loadGame(theGame, fileName); 

    while(1) {
        system("clear"); 
        printf("TO Exit press ( X )\n");
        printf("TO Save press ( S )\n");
        printf("TO Undo press ( U )\n");
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
        } else if (move[0] == 'X') {
            freeBoard(theGame);
            free(theGame);
            return;
        } else if (move[0] == 'S') {
            if (saveGame(theGame)) {
                freeBoard(theGame);
                free(theGame);
                return;
            }
        } else if (move[0] == 'U') {
            if (theGame->movesNumber == 0)
                continue;
            undo(theGame, theGame->moves, theGame->movesNumber);
            free(move);
            continue;
        }

        if (theGame->movesNumber == 0)
            allWhitePiecesMoves(theGame, theGame->allWhite);
        
        moveStoI(move , theGame->moves[theGame->movesNumber]);
        if (checkMoveValidity(theGame->moves[theGame->movesNumber], theGame)) {
            if ((theGame->movesNumber % 2 == 0 && auxiliaryMove(theGame, 0, theGame->moves[theGame->movesNumber])) || (theGame->movesNumber % 2 == 1 && auxiliaryMove(theGame, 1, theGame->moves[theGame->movesNumber]))) // check current player
            {
                free(move);
                continue;
            }    
            doMove(theGame->moves[theGame->movesNumber], theGame);
            printf("Valid move\n");
        }
        else {
            printf("Invalid move\n");
            getchar();
            free(move);
            continue;
        }
        getchar();
        if (theGame->movesNumber % 2 == 0) // Update other player's view 
            allBlackPiecesMoves(theGame, theGame->allBlack);
        else
            allWhitePiecesMoves(theGame, theGame->allWhite);

        if ((theGame->movesNumber % 2 == 1 && isKingInCheck(theGame, theGame->allWhite[4])) || (theGame->movesNumber % 2 == 0 && isKingInCheck(theGame, theGame->allBlack[4]))) // check opponent
        {
            if (finalCheck(theGame, theGame->allWhite, theGame->allBlack))
            {
                system("clear"); 
                printf("=======================================================\n");
                displayBoard(theGame);
                printf("=======================================================\n");
                if (theGame->movesNumber % 2 == 0)
                    printf("White Win\n");
                else
                    printf("Black Win\n");
                getchar( );
                free(move);
                break;
            }
        }
        else // not at check
        {
            if (finalCheck(theGame, theGame->allWhite, theGame->allBlack))
            {
                system("clear"); 
                printf("=======================================================\n");
                displayBoard(theGame);
                printf("=======================================================\n");
                printf("Stalemate\n");
                getchar( );
                free(move);
                break;  
            }
        }
        
        /////////////////////////////////////////////////////////
        viewAllPiecesMoves(theGame->allWhite, theGame->allBlack);
        getchar();
        /////////////////////////////////////////////////////////
        theGame->movesNumber++;
        free(move);
    }
    freeBoard(theGame);
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
            startNormalGame(0 , "");
        }
        else if (choice == 2)
        {
            char* fileName;
            printf("Enter game name: ");
            fileName = loadInput();
            startNormalGame(1 , fileName);
            free(fileName);
        }
        else if (choice == 3)
        {
            exit(0);
        }
    }
}