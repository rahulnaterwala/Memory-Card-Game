#include <stdio.h>
#include <stdlib.h> //for the use of system and srand and rand
#include "gameObjects.h"
#include "gameFunctions.h"

#define MAX_CHAR_NUMBER 16 //each input should have at most 15 characters

//a helper function that clears the screen, works for both unix and Windows,
//though behaviour might be different.
//reference: https://stackoverflow.com/questions/2347770/
//            how-do-you-clear-the-console-screen-in-c
void clear() {
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("printf '\33[H\33[2J'");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

int main() {
  //set the random seed to 0, it'll generate the same sequence
  //normally it is srand(time(NULL)) so the seed is different in every run
  //using 0 makes it deterministic so it is easier to mark
  //do not change it
  srand(0);

  //variables to store user input
  char userInput1[MAX_CHAR_NUMBER];
  char userInput2[MAX_CHAR_NUMBER];
  int whereInDeck1 = 0; //handy for indexing which card based on user input
  int whereInDeck2 = 0; //another variable to track second inputs index

  //set up the players
  Player player1, player2;
  initializePlayer(&player1, "Player 1");
  initializePlayer(&player2, "Player 2");
  Player* currentPlayer = &player1; //this pointer remembers who's turn it is

  //set up the deck: initalize & shuffle
  Deck myDeck;
  initializeDeck(&myDeck, "Bicycle");
  shuffleDeck(&myDeck);

  printDeck(&myDeck, true); //print the shuffled deck, face up
  printf("\n");
  clear(); //clear the screen

  /*
  Implement this part for the game to work.
  It is essentially a do-while loop that repeatedly print the deck,
  ask for user inputs, and do some checking. Ends if someone wins.
  */
  do {
    /////////////////////
    // 1 Round
    ////////////////////
    //Step 1: print the shuffled deck, face down
    printDeck(&myDeck, false);
    printf("\n");

    //Step 2: print who's turn it is by showing the player's name
    printf("%s's turn.\n", currentPlayer->name);

    //Step 3.1 get first input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)

    do{
        printf("Pick the first card you want to turn (e.g., 0 a) then press enter: ");
        scanf(" %c", &userInput1[0]);
        scanf(" %c", &userInput1[1]);
    } while (!checkPlayerInput(&myDeck, currentPlayer, userInput1[0], userInput1[1]));


    //Step 3.2: get second input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)

    do{
        printf("Pick the second card you want to turn (e.g., 1 b) then press enter: ");
        scanf(" %c", &userInput2[0]);
        scanf(" %c", &userInput2[1]);
    } while (!checkPlayerInput(&myDeck, currentPlayer, userInput2[0], userInput2[1]));
    printf("\n");


    //Step 4: print the 2 cards the player picks
    //calculate index of user input
    whereInDeck1 = (userInput1[0] - 48)*13 + (userInput1[1] - 97);
    if (myDeck.cards[whereInDeck1].suit == Spades){
        printf("First card picked: %c\u2660\n", myDeck.cards[whereInDeck1].value);
    }
    else if (myDeck.cards[whereInDeck1].suit == Hearts){
        printf("First card picked: %c\u2661\n", myDeck.cards[whereInDeck1].value);
    }
    else if (myDeck.cards[whereInDeck1].suit == Clubs){
        printf("First card picked: %c\u2663\n", myDeck.cards[whereInDeck1].value);
    }
    else{
        printf("First card picked: %c\u2662\n", myDeck.cards[whereInDeck1].value);
    }
    //calculate index of user input
    whereInDeck2 = (userInput2[0] - 48)*13 + (userInput2[1] - 97);
    if (myDeck.cards[whereInDeck2].suit == Spades){
        printf("Second card picked: %c\u2660\n", myDeck.cards[whereInDeck2].value);
    }
    else if (myDeck.cards[whereInDeck2].suit == Hearts){
        printf("Second card picked: %c\u2661\n", myDeck.cards[whereInDeck2].value);
    }
    else if (myDeck.cards[whereInDeck2].suit == Clubs){
        printf("Second card picked: %c\u2663\n", myDeck.cards[whereInDeck2].value);
    }
    else{
        printf("Second card picked: %c\u2662\n", myDeck.cards[whereInDeck2].value);
    }
    printf("\n");


    //Step 5: call the checkForMatch function to see if the player has picked
    // a matching pair. If so, print the corresponding message and add the cards
    // to the player's winning pile (Player.winPile).
    // Keep the current player as a match leads to an extra round.
    // Otherwise, print the corresponding message and switch player.
    if (checkForMatch(&myDeck, currentPlayer, userInput1[0], userInput1[1], userInput2[0], userInput2[1])){
        addCardToPlayer(currentPlayer, &myDeck.cards[whereInDeck1]);
        addCardToPlayer(currentPlayer, &myDeck.cards[whereInDeck2]);
        if (currentPlayer->name == player1.name){
            printf("Player 1 has found a match! Earns an extra turn.\n");
        }
        else if (currentPlayer->name == player2.name){
            printf("Player 2 has found a match! Earns an extra turn.\n");
        }
    }
    else{
        if (currentPlayer->name == player1.name){
            printf("Player 1 has not found a match.\n");
            currentPlayer = &player2;
        }
        else if (currentPlayer->name == player2.name){
            printf("Player 2 has not found a match.\n");
            currentPlayer = &player1;
        }
    }

  } while (!checkForWinner(&myDeck));

  //Step 6: find out who won the game and announce the winner
  printf("Player 1 has %d cards.\n", player1.cardsWon);
  printf("Player 2 has %d cards.\n", player2.cardsWon);
  if (player1.cardsWon == player2.cardsWon){
      printf("Players have tied!\n");
  }
  else if (player1.cardsWon > player2.cardsWon){
      printf("Player 1 won!\n");
  }
  else{
      printf("Player 2 won!\n");
  }

  //Step 7: clean up player's winning piles
  clearPlayer(&player1);
  clearPlayer(&player2);

  return 0;
}
