#ifndef WarCards_library
#define WarCards_library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*	Made by  Yoav Saroya - 304835887	Shamir Kritzler - 052993060 */

typedef enum kind {Black_Spades,Black_Clubs,Red_Hearts,Red_Diamonds, Fail}kind;
typedef enum nameCard{Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace}nameCard;
typedef struct card_t* card;
typedef struct listItem						// global struct (linklist)
{
	card data;
	struct listItem* next;
}listItem;


card pack[52];						//the pack of cards as a "black box"

//~Functions Header~//
nameCard names (int k);
char* printName (nameCard namer);
kind types (int k);
char* printShape (kind kinder);
void read_deck ();					//read the deck from a file and store it in an array of cards.
listItem* addToBottom (listItem* head, card lastCard);	// add an object to the last index of a linklist.
listItem* addDeck (listItem*, card loserCard);	//add an object to the top of the linklist.
listItem* removeFromTop (listItem* head, int valuer, kind shaper);	//remove an object from the head of the linklist.
listItem* Add (listItem* head, card arrayz[], int n);	//add a card to a linklist.
void swap_card (card *a, card *b);				//swap between 2 cards. helps to shuffle the dack.
void FreeList (listItem* head);					//get a linked list and free it.
int LinklistCounter(listItem* head);			//counts and return how many objects the linklist has.
void DisplayCard (card ca);						// print a single card.
void DisplayList (listItem* firstptr);			// print a link list.
void shuffle_deck (card array[], int size);		//shuffle the array of cards.
void war (listItem* player1, listItem* player2);		//the fight between the 2 linked list.
#endif
