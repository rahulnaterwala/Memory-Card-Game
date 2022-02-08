#include "Card_LList.h"

Card_LList* createCard_LList(){
    //malloc new Card_LList
    Card_LList* l = malloc(sizeof(Card_LList));
    //check if l was created, if so set head and tail to null
    if (l){
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}

void clearCard_LList(Card_LList* theList){
    //temp variable to store node
    Card_Node* temp;
    //while loop to go till head == null
    while(theList->head != NULL){
        //set temp as current head
        temp = theList->head;
        //set head as next value
        theList->head = theList->head->next;
        //free previous head
        free(temp);
    }
}

bool isEmptyCard_LList(Card_LList* theList){
    //return bool value checking if head == null, which implies list is empty
    return (theList->head == NULL);
}

Card_Node* createNode(Card* theCard){
    //malloc a new node, set the nodes card to input card and next address to
    //null
    Card_Node* node = malloc(sizeof(Card_Node));
    node->card = theCard;
    node->next = NULL;

    return node;
}

void insertFrontCard_LList(Card_LList* theList, Card* theCard){
    //create new node using previous function
    Card_Node* newNode = createNode(theCard);
    //check if list is has elements, if not set head and tail to that node
    if (theList->head == NULL){
        theList->head = newNode;
        theList->tail = newNode;
    }
    //set the head as the new nodes next and new node to theLists head
    else{
        newNode->next = theList->head;
        theList->head = newNode;
    }
}

void insertEndCard_LList(Card_LList* theList, Card* theCard){
    //malloc for a newNode
    Card_Node* newNode = createNode(theCard);
    //check if list is has elements, if not set head and tail to that node
    if (theList->head == NULL){
        theList->head = newNode;
        theList->tail = newNode;
    }
    //set the tails next to the new node and update tail to be the new node
    else{
        theList->tail->next = newNode;
        theList->tail = theList->tail->next;
    }
}

Card* removeFrontCard_LList(Card_LList* theList){
    //initalize a tempcard
    Card* tempCard;
    //if list is empty return null for a card
    if (theList->head == NULL){
        return NULL;
    }
    //set the temp card to the front of the lists card
    else{
        tempCard = theList->head->card;
        //update head of list to the next node
        theList->head = theList->head->next;
    }
    return tempCard;
}

Card* removeEndCard_LList(Card_LList* theList){
    //initalize a tempNode and a tempCard
    Card_Node* tempNode;
    Card* tempCard;
    //if the tail is null return null
    if (theList->tail == NULL){
        return NULL;
    }
    else{
        //set the temp node to the first node in the list
        tempNode = theList->head;
        //iterate through the list until temp nodes next == the lists tail
        while (tempNode->next != theList->tail){
            tempNode = tempNode->next;
        }
        //set the temp card to the tails card so it can be returned
        tempCard = theList->tail->card;
        theList->tail = tempNode;
        //free tail next as last cards been overwritten
        free(theList->tail->next);
        //set the freed address to null
        theList->tail->next = NULL;
        return tempCard;
    }
}
