#include "gameObjects.h"

void initializeDeck(Deck* theDeck, char* brandName){
    //set brand name
    theDeck->brand = brandName;
    //outer for loop goes starts at the ace of every suit
    for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i = i+13){
        //initialize the cards without numeric values
        theDeck->cards[i].value = 'A';
        theDeck->cards[i+9].value = 'T';
        theDeck->cards[i+10].value = 'J';
        theDeck->cards[i+11].value = 'Q';
        theDeck->cards[i+12].value = 'K';
        //inner for loop initializes cards 2-10 for every suit
        for (int j = 2; j < 10; j++){
            //add '0' to convert j (an integer) to a character
            theDeck->cards[i+(j-1)].value = j + '0';
        }
    }
    //go through cards and assign them a suit
    for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++){
        if (i < 13){
            theDeck->cards[i].suit = Spades;
        }
        else if (i < 26){
            theDeck->cards[i].suit = Hearts;
        }
        else if (i < 39){
            theDeck->cards[i].suit = Clubs;
        }
        else{
            theDeck->cards[i].suit = Diamonds;
        }
    }
}

void shuffleDeck(Deck* theDeck){
    //initialize temporary deck to store values
    Deck t;
    for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++){
        //use the formula from recommended stack overflow link to shuffle
        int j = i + rand() / (RAND_MAX / (NUM_OF_CARDS_IN_DECK - i) + 1);
        //swap algorithm
        t.cards[i] = theDeck->cards[j];
        theDeck->cards[j] = theDeck->cards[i];
        theDeck->cards[i] = t.cards[i];
    }
}

void printDeck(const Deck* theDeck, bool faceUp){\
    //print the columns using ascii values
    int row = 0;
    printf(" ");
    for (int col = 97; col < 110; col++){
        printf("  %c", col);
    }
    printf("\n");
    //check if the deck should be printed face up
    if (faceUp == true){
        for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i = i+13){
            //inner for loop goes through the 13 cards per each suit, checking for
            //what suit it is and printing the appropriate symbol with it
            //at the start of each row print column number
            printf("%d ", row);
            for (int j = 0; j < 13; j++){
                if (theDeck->cards[i+j].suit == Spades){
                    printf("%c", theDeck->cards[i+j].value);
                    printf("\u2660");
                }
                else if (theDeck->cards[i+j].suit == Hearts){
                    printf("%c", theDeck->cards[i+j].value);
                    printf("\u2661");
                }
                else if (theDeck->cards[i+j].suit == Clubs){
                    printf("%c", theDeck->cards[i+j].value);
                    printf("\u2663");
                }
                else{
                    printf("%c", theDeck->cards[i+j].value);
                    printf("\u2662");
                }
                //Adds a space inbetween cards, but not at the beginning or end
                //of each line
                if (j < 12){
                    printf(" ");
                }
            }
            printf("\n");
            row++;
        }
    }
    //if deck needs to be printed face down
    else if (faceUp == false){
        for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i = i+13){
            printf("%d ", row);
            for (int j = 0; j < 13; j++){
                //put an empty space if the card has been taken
                if (theDeck->cards[i+j].value == '0'){
                    printf("  ");
                }
                //print a question mark and a empty box
                else{
                    printf("%c\u218C", '?');
                }
                //add a space between every card
                if (j < 12){
                    printf(" ");
                }
            }
            printf("\n");
            row++;
        }
    }
    printf("\n");
}

void initializePlayer(Player* thePlayer, char* theName){
    //set player name, cards won to 0, and linked list head and tail to null
    thePlayer->name = theName;
    thePlayer->cardsWon = 0;
    thePlayer->winPile.head = NULL;
    thePlayer->winPile.tail = NULL;
}

void clearPlayer(Player* thePlayer){
    //clear players name and set number of cards won to 0
    thePlayer->name = NULL;
    thePlayer->cardsWon = 0;
    //call function to clear linked list
    clearCard_LList(&thePlayer->winPile);
    //set head and tail of linked list to null
    thePlayer->winPile.head = NULL;
    thePlayer->winPile.tail = NULL;
}
