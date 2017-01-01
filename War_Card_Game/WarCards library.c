#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "WarCards library.h"

/*	Made by  Yoav Saroya - 304835887	Shamir Kritzler - 052993060 */
struct card_t
{
	int value;
	nameCard name;	
	kind shape;
};
extern card pack[52];

kind types (int k)
{
	if (k==1) return Black_Spades;
	if (k==2) return Black_Clubs;
	if (k==3) return Red_Hearts;	
	if (k==4) return Red_Diamonds;	
	return Fail;
}

nameCard names (int k)
{
	if (k==2) return Two;
	if (k==3) return Three;
	if (k==4) return Four;
	if (k==5) return Five;
	if (k==6) return Six;
	if (k==7) return Seven;
	if (k==8) return Eight;
	if (k==9) return Nine;
	if (k==10) return Ten;
	if (k==11) return Jack;
	if (k==12) return Queen;
	if (k==13) return King;
	if (k==14) return Ace;
}

char* printName (nameCard namer)
{
	if (namer == Two) return "Two";
	if (namer == Three) return "Three";
	if (namer == Four) return "Four";
	if (namer == Five) return "Five"; 
	if (namer == Six) return "Six";
	if (namer == Seven) return "Seven";
	if (namer == Eight) return "Eight";
	if (namer == Nine) return "Nine"; 
	if (namer == Ten) return "Ten";
	if (namer == Jack) return "Jack";
	if (namer == Queen) return "Queen";
	if (namer == King) return "King"; 
	if (namer == Ace) return "Ace";
}
char* printShape (kind kinder)
{
	if (kinder == Black_Spades) return "Spades";
	if (kinder == Black_Clubs) return "Clubs";
	if (kinder == Red_Hearts) return "Hearts";
	if (kinder == Red_Diamonds) return "Diamonds"; 
	return "Fail";
}
void read_deck () __attribute__ ((constructor));
void read_deck ()
{
	int i=0, j=1, z=2;
	for (i=0; i<52; i++)
	{
		pack[i] = (card) malloc (sizeof (struct card_t));
		pack[i]->value = z;
		pack[i]->name = names (z);
		pack[i]->shape = types(j);	
		j++;
		if (j>4)
		{
	   		 j=1;
	   		 z++;
		}
	}
}

listItem* addToBottom (listItem* head, card lastCard)
{
	listItem* tail= head;
	listItem* new_item = (listItem*) malloc (sizeof (listItem));
	if (new_item == NULL)
	{
		printf ("Out of memory!\n");
		exit(-1);
	}
	new_item->data= lastCard;
	new_item->next = NULL;
	if (head == NULL) return new_item;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new_item;
	return head;
}

listItem* addDeck (listItem* head, card loserCard)
{
	listItem* uppestCardstack;	
	uppestCardstack = (listItem*) malloc(sizeof (listItem));
	if (uppestCardstack == NULL)
	{
		printf ("Out of memory!\n");
		exit(-1);
	}
	uppestCardstack->data = loserCard;
	uppestCardstack->next= head;
	return uppestCardstack;
}


listItem* removeFromTop (listItem* head, int valuer, kind shaper)
{
	listItem* curr; 
	listItem* prev;
	curr = (listItem*) malloc (sizeof (listItem));
	prev = (listItem*) malloc (sizeof (listItem));
	curr = head;
	prev = head;
	if (head == NULL) return head;
	if (head->data->value == valuer && head->data->shape == shaper)
	{
		curr = head->next;
		free (head);
		return curr;
	}	
}

listItem* Add (listItem* head, card arrayz[], int n)
{
	listItem* uppestCard;	
	uppestCard = (listItem*) malloc(sizeof (listItem));
	if (uppestCard == NULL)
	{
		printf ("Out of memory!\n");
		exit(-1);
	}
	uppestCard->data = arrayz[n];
	uppestCard->next= head;
	return uppestCard;
}

void swap_card (card *a, card *b)
{
    card temp = *a;
    *a = *b;
    *b = temp;
}

void FreeList (listItem* head)
{
	listItem* to_free;
	to_free = (listItem*) malloc (sizeof (listItem));
	to_free = head;
	while (to_free != NULL)
	{
		head = head->next;
		free (to_free);
		to_free = head;
	}
}

int LinklistCounter(listItem* head)
{
	int counter=0;
	while (head != NULL)
	{
		counter++;
		head = head->next;
	}
	return counter;
}

void DisplayCard (card ca)
{
	printf ("%s - %s - %d\n", printName(ca->name), printShape(ca->shape), ca->value);
}

void DisplayList (listItem* firstptr)
{
	while (firstptr!=NULL)
	{
		DisplayCard(firstptr->data);
		firstptr = firstptr->next;
	}
}

void shuffle_deck (card array[], int size)		//shuffle the array by help from time.h library.
{
	
	srand (time(NULL));
	int x;
	for (x= size-1; x>0; x--)
	{
		 int j = rand() % (x+1);
		swap_card(&array[x], &array[j]);		//swap between 2 cards.
	}
}

void war (listItem* player1 ,listItem* player2)
{
	int counter1=0, counter2=0, ender=1;
	listItem* war1;
	listItem* war2;
	card currentCardPlayer1;
	card currentCardPlayer2;
	int x=0, y=0, t=0; 
	int numofcard1, numofcard2;
	card pack1[52], pack2[52];
	card winpack1[52];
	card winpack2[52];
	FILE* gameWriter;
	gameWriter = fopen ("GameResult.txt", "a");
	if (gameWriter == NULL)
	{
		printf ("The GameResult file could not be found.\n");
		exit (-1);
	}
	while (player1 != NULL && player2 != NULL)
	{
		y=0;
		numofcard1 = LinklistCounter (player1);		
		numofcard2 = LinklistCounter (player2);		//counts how many cards each player has
		while (player1 != NULL)
		{
			pack1[y] = player1->data;
			player1 = player1->next;
			y++;
		}
		shuffle_deck (pack1, y);					//shuffle cards of player 1
		for (y=0; y<numofcard1; y++)
			player1 = Add (player1, pack1, y);
		y=0;	
		while (player2 != NULL)
		{
			pack2[y] = player2->data;
			player2 = player2->next;
			y++;
		}
		shuffle_deck (pack2, y);					//shuffle cards of player 2
		for (y=0; y<numofcard2; y++)
			player2 = Add (player2, pack2, y);	


		currentCardPlayer1 = player1->data;			//the current card of player 1
		currentCardPlayer2 = player2->data;			//the current card of player 2
		
		x++;									//x = number of turn
		if (currentCardPlayer1->value > currentCardPlayer2->value)	//if (player1 card > player2 card)
		{
			fprintf (gameWriter, "Turn <%d> Player 1 draws: %s of %s - Player 2 draws: %s of %s | Player 1 Wins\n", x, printName (player1->data->name), printShape(player1->data->shape), printName (player2->data->name), printShape(player2->data->shape)); 
			player1 = removeFromTop (player1, currentCardPlayer1->value, currentCardPlayer1->shape);	//remove the 2 cards from player's hand.
			player2 = removeFromTop (player2, currentCardPlayer2->value, currentCardPlayer2->shape);
			player1 = addToBottom (player1, currentCardPlayer1);	//add player1's card to the bottom of player 1 deck.
			player1 = addToBottom (player1, currentCardPlayer2);	//add player2's card to the bottom of player 1 deck.
		}
		else if (currentCardPlayer1->value < currentCardPlayer2->value) //if (player1 card < player2 card)
		{
			fprintf (gameWriter, "Turn <%d> Player 1 draws: %s of %s - Player 2 draws: %s of %s | Player 2 Wins\n", x, printName (player1->data->name), printShape(player1->data->shape), printName (player2->data->name), printShape(player2->data->shape));
			player1 = removeFromTop (player1, currentCardPlayer1->value, currentCardPlayer1->shape);	
			player2 = removeFromTop (player2, currentCardPlayer2->value, currentCardPlayer2->shape); //remove the 2 cards from players' hand.
			player2 = addToBottom (player2, currentCardPlayer1);	//add player1's card to the bottom of player 2 deck.
			player2 = addToBottom (player2, currentCardPlayer2);	//add player2's card to the bottom of player 2 deck.
		}
		else if (currentCardPlayer1->value == currentCardPlayer2->value) //if its a draw!
		{
			counter2=0;
			war1 = player1;	//war1 will go forward through player1's cards.
			war2 = player2;	//war2 will go forward through player2's cards.
			t=0;
			fprintf (gameWriter, "Turn <%d> Player 1 draws: %s of %s - Player 2 draws: %s of %s | WAR!\n", x, printName (war1->data->name), printShape(war1->data->shape), printName(war2->data->name), printShape(war2->data->shape));	
			do	
			{
				ender= 1;		
				counter1 = 0;
				while (war1->next != NULL && war2->next != NULL && counter1 !=4 )	
				{
					winpack1[t] = war1->data;
					war1 = war1->next;
					fprintf (gameWriter, "Player 1 draws: %s of %s         ", printName (war1->data->name), printShape(war1->data->shape));
					winpack2[t] = war2->data;
					war2 = war2->next;
					fprintf (gameWriter, "Player 2 draws: %s of %s\n", printName (war2->data->name), printShape(war2->data->shape));
					counter1++;
					t++;
				}
				 winpack1[t] = war1->data;
				 winpack2[t] = war2->data;
				
				if (war1->data->value > war2->data->value)	//if player 1 won the war.
				{
					counter2=t;	
					fprintf (gameWriter, "Player 1 wins.\n");
					for (t=0; t<=counter2; t++)
					{	
						player1 = removeFromTop (player1, winpack1[t]->value, winpack1[t]->shape);
						player2 = removeFromTop (player2, winpack2[t]->value, winpack2[t]->shape);						
						player1 = addToBottom (player1, winpack1[t]);
						player1 = addToBottom(player1, winpack2[t]);		//player 1 wins all the cards.
					}
				}
				else if (war1->data->value < war2->data->value)	//if player 2 won the war.
				{
					counter2=t;	
					fprintf (gameWriter, "Player 2 wins.\n");
					for (t=0; t<=counter2; t++)
					{
						player1 = removeFromTop (player1, winpack1[t]->value, winpack1[t]->shape);
						player2 = removeFromTop (player2, winpack2[t]->value, winpack2[t]->shape);						
						player2 = addToBottom (player2, winpack1[t]);
						player2 = addToBottom (player2, winpack2[t]);		//player 2 wins all the cards.
					}
				}
				else		//if there is no winner in this war:
				{
					
					if (war1->next == NULL || war2->next == NULL)	//checks that the players has at least 1 card to draw.
					{
						fprintf (gameWriter,"Its another WAR! but one of the player does not have enough cards to draw. Re-Packing.\n");
						for (; t>=0; t--)
						{
							player1 = addToBottom (player1, winpack1[t]);	//REPACKING!
							player2 = addToBottom (player2, winpack2[t]);
							player1 = removeFromTop (player1, winpack1[t]->value, winpack1[t]->shape);
							player2 = removeFromTop (player2, winpack2[t]->value, winpack2[t]->shape);	
						}
							break;
					}
					else
					{
						ender=0;				//do the loop again! (pull out 4 cards, and check who wins in the 4th card).
						counter1=0;
						t++;
						war1 = war1->next;
						war2 = war2->next;
						fprintf (gameWriter,"Its another WAR!\n");
					}
				}
			}
			while (ender == 0);			//helps to indicate if to do the loop again or stop right here.
		}
	}
	
	if (player1 == NULL)	//indicates that player 1 has no more cards to play with.
	{
		x=0;
		printf ("Player 2 wins the game!\n");
		fprintf (gameWriter, "Player 2 Beated Player 1!\n");
		FreeList (player2);
		fclose (gameWriter);
	}
	else //(player2 == NULL)	//indicates that player 2 has no more cards to play with.
	{
		x=0;
		printf ("Player 1 wins the game!\n");
		fprintf (gameWriter, "Player 1 Beated Player 2!\n");
		FreeList (player1);
		fclose (gameWriter);
	}		
}
