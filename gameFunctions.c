#include "gameFunctions.h"

void addCardToPlayer(Player* thePlayer, Card* theCard){
    //add card to the front of the players linked list
    insertFrontCard_LList(&thePlayer->winPile, theCard);
    //add 1 to the players cards won and set the cards value to '0'
    thePlayer->cardsWon++;
    theCard->value = '0';
}

bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col){
    //convert row and col to integers to perform arithemtics with
    int introw = row - 48;
    int intcol = col - 97;
    //track index of card in cards list
    int index;
    //check if the input is in range
    if (row < '4' && col < 'n'){
        //find the index from col and row values
        index = introw*13 + intcol;
        //conditionals to check if the card has already been taken
        if (theDeck->cards[index].value != '0'){
            return true;
        }
        else{
            printf("Error: The card you picked is already taken.\n");
            return false;
        }
    }
    //if card has invalid indexes report it
    else{
        printf("Error: The card you picked has invalid index(es).\n");
        return false;
    }
}

bool checkForMatch(Deck* theDeck, Player* thePlayer,
                      char r1, char c1, char r2, char c2){
    //convert rows and cols to integers
    int intr1 = r1 - 48;
    int intr2 = r2 - 48;
    int intc1 = c1 - 97;
    int intc2 = c2 - 97;
    //find the index of the cards in the card array using cols and rows
    int index1 = intr1*13 + intc1;
    int index2 = intr2*13 + intc2;
    //check if the two cards have the same value
    if (theDeck->cards[index1].value == theDeck->cards[index2].value){
        //check if the cars havent been taken
        if (theDeck->cards[index1].value != '0'){
            //check if the cards are not the same
            if (r1 != r2 || c1 != c2){
                return true;
            }
            else{
                printf("Error: Both cards are the same.\n\n");
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool checkForWinner(const Deck* theDeck){
    //for loop that looks if any remaining cards have not been claimed
    for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++){
        if (theDeck->cards[i].value != '0'){
            return false;
        }
    }
    return true;
}
