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
        allPiecesMoves(theGame, theGame->allWhite, theGame->allBlack);
        moveStoI(move , theGame->moves[theGame->movesNumber]);
        if (checkMoveValidity2(theGame->moves[theGame->movesNumber], theGame)) {
            printf("Valid move\n");
            int fromRow = theGame->moves[theGame->movesNumber][1];
            int fromCol = theGame->moves[theGame->movesNumber][0];
            int toRow = theGame->moves[theGame->movesNumber][3];
            int toCol = theGame->moves[theGame->movesNumber][2];
            theGame->board[toRow][toCol] = theGame->board[fromRow][fromCol];
            theGame->board[toRow][toCol]->hasMoved = 1;
            theGame->board[toRow][toCol]->position[0] = toRow ;
            theGame->board[toRow][toCol]->position[1] = toCol;
            if (theGame->movesNumber % 2 == 0) {
                theGame->allWhite[theGame->board[toRow][toCol]->id] = theGame->board[toRow][toCol];                
            } else {
                theGame->allBlack[theGame->board[toRow][toCol]->id] = theGame->board[toRow][toCol];
            }
            theGame->board[theGame->moves[theGame->movesNumber][1]][theGame->moves[theGame->movesNumber][0]] = NULL;
            theGame->movesNumber++;
        }
        else 
            printf("Invalid move2\n");
        getchar();
        /////////////////////////////////////////////////////////
        viewAllPiecesMoves(theGame->allWhite, theGame->allBlack);
        getchar();
        /////////////////////////////////////////////////////////
        free(move);
    }
    free(theGame);
}

int displayModeMenu()
{
    int choice = 0;
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
        return 0;
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
            if (displayModeMenu() == 0)
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