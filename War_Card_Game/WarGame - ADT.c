#include "WarCards library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*	Made by  Yoav Saroya - 304835887	Shamir Kritzler - 052993060 */
int menu ();

int main(int argc, char *argv[])
{
	printf ("                 __\n");
	printf ("                /  >\n");
	printf ("  *            /  /________________________________________________\n");
	printf (" (O)77777777777)  7                                                `~~--__\n");
	printf ("8OO>>>>>>>>>>>>] <==== Yoav Saroya & Shamir Kritzler <War Game cards-ADT>__-\n");
	printf (" (O)LLLLLLLLLLL)  L________________________________________________.--~~\n");
	printf ("  *            \\  \\\n");
	printf ("                \\__>\n");			//this is just a sword.
	FILE* gameWritertemp;
	gameWritertemp = fopen ("GameResult.txt", "w");
	fclose (gameWritertemp);
	int i=0;
	shuffle_deck (pack, 52);
	listItem* player1_cards = NULL;
	listItem* player2_cards = NULL;
	
	for (i=0; i<26; i++)
		player1_cards = Add (player1_cards, pack,i);		
	for (i=26; i<52; i++)
		player2_cards = Add (player2_cards, pack,i);	
	int menuer = menu();
	while (menuer ==1)
	{
		war (player1_cards, player2_cards);	
		gameWritertemp = fopen ("GameResult.txt", "a");
		fprintf (gameWritertemp, "*********************************************************\n");
		fclose (gameWritertemp);
		while (player1_cards != NULL)		
		{
			free (player1_cards);
			player1_cards=player1_cards->next;
		}	
		while (player2_cards != NULL)		
		{
			free (player2_cards);
			player2_cards=player2_cards->next;
		}
		shuffle_deck (pack, 52);
		for (i=0; i<26; i++)
			player1_cards = Add (player1_cards, pack,i);		
		for (i=26; i<52; i++)
			player2_cards = Add (player2_cards, pack,i);	
		menuer = menu();
	}
	return 0;
}

int menu ()
{
	char input_menu[5];
	printf ("Please choose what you want to do:\n");
	printf ("[1] Autoplay WarGame cards mode.\n[2] Exit the program.\n");
	while (input_menu)					//as long as the input is incorrect - you stay inside the loop.
	{
		scanf ("%s", &input_menu);
		if (strcmp (input_menu, "1") ==0) return 1;
			
		else if (strcmp (input_menu, "2") ==0) 	
		{
			printf ("Thank you for using us! we hope you enjoyed!");
			return 0;
		}
		printf ("You only got 2 options! is it so hard to understand?\nPlease try again what you want to do:\n");
	}		
}
