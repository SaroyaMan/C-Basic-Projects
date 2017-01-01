#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*	Made by  Yoav Saroya - 304835887		Shamir Kritzler - 052993060		Yossi Efraim - 302917331          */
typedef struct item
{
	char name[30];
	int price;
}item;

void exit_machine ();							//This function quits the program immediately.
int numberOfItems(int counter);					//This function counts how many items there is inside the file.
void scanFile (int items, item array[]);		//Scan machinedata.txt and transform it into 1 array of structs.
void printFile(int items, item array[]);		//Print the array of structs.
void user_Buy (char nameUser[],int funds);		//This function lets the simple user buy items from the printed list.
void manage_mode ();							//This function prints the manager menu and let choose what we want to do.
void item_Changer ();							//This function lets the admin choose an item and change his name+price.
void replace_list();							//This function replace the machinedata.txt in any other txt file.
void argc_checker (int start_checker);			//This function checks that you entered 3 arguments only!
void argv_checker (char str1[], char str2[]);	//This function checks that your name contains only letters and your money contains only numbers.

int main(int argc, char *argv[])
{	
	char str1[10], str2[8];
	argc_checker(argc);
	strcpy (str1, argv[1]);
	strcpy (str2, argv[2]);	
	argv_checker (str1, str2);
	printf ("Welcome %s!\n",argv[1]);
	printf ("Please pick your purchase :\n");

	int coins = atoi(argv[2]);					//argv[2] transforms into int type
	printf ("Your current funds is: %d\n", coins);
	user_Buy (str1,coins);
	return 0;
}

void exit_machine () 						
{
	printf ("Thank you for using the machine.\nHave a nice day!\n");
	exit (0);
}

void argc_checker (int start_checker)
{
	if ((start_checker !=3))
	{
		printf("Your startup input is not legal. the program will exit now.\n");
		exit (-1);
	}
}

void argv_checker (char argv1[], char argv2[])
{
	int k=0, t=0;	
	while (argv1[k]!='\0')
	{
		if((argv1[k]>=65 && argv1[k]<=90) || (argv1[k]>=97 && argv1[k]<=122)) 	//Checks that argv1 has only letters
		{
			k++;
		}
		else
		{
			printf("Your startup input is not legal. the program will exit now.\n");
			exit (-1);
		}
	}
	while (argv2[t]!='\0')								//Checks that argv2 has only numbers
	{
		if((argv2[t]>='0') && (argv2[t]<='9'))
		{
			t++;
		}		
		else
		{
			printf("Your startup input is not legal. the program will exit now.\n");
			exit (-1);
		}
	}
}

int numberOfItems(int counter)				
{
	int i=0;
	FILE* ItemNums;
	char temp_string[1024];
	ItemNums=fopen("machinedata.txt", "r");
	if (ItemNums == NULL)
	{
	 	printf("The file could not be opened.\n");
	 	exit (-1);
	}
	fscanf(ItemNums,"%[^\n]",temp_string); 		//temp_string = machinedata.txt.
	fclose (ItemNums);
	counter=0;	
	for (i=0; temp_string[i]!='\0';i++)
		{
			if (temp_string[i]=='-')
			counter++;							//counts the number of the '-' appeared inside the string.
		}
	return counter;	
}

void scanFile (int items, item array[])				
{
	int i=0;
	FILE* pItemFile;
	pItemFile = fopen ("machinedata.txt", "r");
	if (pItemFile == NULL) 
	{
		printf ("The file could not opened\n");	
		exit (-1);
	}
	for (i=0; i<items; i++)
	{
		fscanf (pItemFile, "%s", &array[i].name);
		fgetc(pItemFile);
		fgetc(pItemFile);
		fscanf (pItemFile, "%d", &array[i].price);
		fgetc(pItemFile);
		fgetc(pItemFile);
	}
	fclose (pItemFile);
}

void printFile(int items, item array[])				
{
	int i=0;
	printf ("Num\tItem\tPrice\n");
	for (i=0; i<items; i++)
	{
		printf ("[%d]\t%s\t%d\n",i, array[i].name, array[i].price);
	}
}

void user_Buy (char nameUser[],int funds)
{
	int num,s=0, z=0, lowestPrice;
	char user_index[5];
	int indexes=0;
	FILE* pMachine_Sales;
	int num_of_items = numberOfItems(num_of_items);
	item itemsCustomer[num_of_items];
	scanFile (num_of_items, itemsCustomer);
	
	printf ("Items that you can buy:\n");
	printf ("Num\tItem\tPrice\n");				//prints all the list that the user CAN buy
	for (s=0; s<num_of_items; s++)
	{
		if (funds>= itemsCustomer[s].price)
		{
			printf ("[%d]\t%s\t%d\n",s, itemsCustomer[s].name, itemsCustomer[s].price);
			indexes = s;
		}
	}
	lowestPrice = itemsCustomer[0].price;
	for (z=0; z<indexes; z++)
	{
		if (lowestPrice > itemsCustomer[z].price)
				lowestPrice = itemsCustomer[z].price;		//finds the lowest price item and define it on 'lowestPrice'.
	}
	printf ("Please enter the number item you wish to purchase:\n");
	input:
	scanf ("%s", &user_index);
	num = atoi(user_index);
	
	if (strcmp (user_index, "ILM") ==0 || strcmp (user_index, "ilm") ==0)
		manage_mode();
		
	else if (strcmp (user_index, "exit") ==0 || strcmp (user_index, "EXIT") ==0)
		exit_machine ();
	
	else if (strcmp (user_index, "0") ==0 || strcmp (user_index, "1") ==0  || strcmp (user_index, "2") ==0  || strcmp (user_index, "3") ==0   || strcmp (user_index, "4") ==0   || strcmp (user_index, "5") ==0
	 || strcmp (user_index, "6") ==0  || strcmp (user_index, "7") ==0)
	 	{
	 		num = atoi(user_index);			// 'user_index' transforms into int type and defined to 'num'.
	 		if (num> indexes)
	 		{
	 			printf ("You entered a bad input. please try again!\n");
				goto input;
			}
	 		pMachine_Sales = fopen ("MachineSales.txt", "a");
	 		
			if (pMachine_Sales == NULL) 
			{
				printf ("The file could not opened.\n");
				exit (-1);
			}
			fprintf (pMachine_Sales, "<%s> - <%s> - <%d>, ",nameUser ,itemsCustomer[num].name, itemsCustomer[num].price);
			printf ("The item has successfully bought.");
			funds = funds - itemsCustomer[num].price;
			printf ("Your current funds is: %d\n", funds);
			fclose (pMachine_Sales);
			
			if (lowestPrice > funds)				//Checks that the user still got money to buy.
			{
				printf ("You ran out of money! what a shame :(\n");
				exit_machine ();
			}
			else user_Buy (nameUser,funds);
	 	}
		  
	else
	{
		printf ("You entered a bad input. please try again!\n");
		goto input;
	}
}

void manage_mode ()
{
	char admin_options[5];
	printf ("Accessing admin menu\nWelcome admin, please choose an option :\n");
	printf ("[0] Update database from specified file.\n[1] Print all available items.\n[2] Change an item on the list.\n");
	printf ("Type 'exit' to quit the program:\n");
	admin_options:
	scanf ("%s",admin_options);
	if (strcmp (admin_options, "ILM") ==0 || strcmp (admin_options, "ilm") ==0)
	{
		printf ("You are already the admin!\nLets try again:");
		goto admin_options;
	}
	
	else if (strcmp (admin_options, "0") ==0)
		replace_list ();
	
	else if (strcmp (admin_options, "1") ==0)
	{
		int num_of_items=0;
		num_of_items = numberOfItems(num_of_items);
		item adminItems[num_of_items];
		scanFile (num_of_items,adminItems);
		
		printFile(num_of_items,adminItems);
		manage_mode();
	}
	
	else if (strcmp (admin_options, "2") ==0)
		item_Changer();
	
	else if (strcmp (admin_options, "exit") ==0 || strcmp (admin_options, "EXIT") ==0)
		exit_machine ();
	
	else
	{
		printf ("You entered a bad input. please try again!\n");
		goto admin_options;
	}
}

void replace_list ()						
{
	int counter=0, i=0, j=0;
	char newFileString[1024];
	char yesORno [5];
	char nameoffile[100];
	item manager_items[counter];
	FILE* managerFp;
	printf ("Please enter the name of the file you want to enter:\nType 'exit' to quit the program.\n");
	openfile:
	scanf ("%s",&nameoffile);
	if (strcmp (nameoffile, "exit") ==0 || strcmp (nameoffile, "EXIT") ==0)
			exit_machine ();
	managerFp = fopen(nameoffile, "r");
	if (managerFp == NULL)
	{
		printf("The file could not be opened. Please try again:\n");
		goto openfile;	
	}
	
	else
	{	
		fscanf(managerFp,"%[^\n]",newFileString); 		//str = managerlist.txt
		fclose (managerFp);
		
		for (i=0; newFileString[i]!='\0';i++)
		{
			if (newFileString[i]=='-')
			counter++;
		}
	}
	printf ("a file was found!\nAre you sure that you want to replace your list?\ntype 'yes' or 'no'\n");
	decide:
	scanf ("%s", &yesORno);
	
	if (strcmp (yesORno, "yes") ==0 || strcmp (yesORno, "YES") ==0)
	{
		FILE* oldFp;
		oldFp = fopen("machinedata.txt", "w");
		if (managerFp == NULL) 
		{
			printf("The file could not be opened.\n");
			exit (-1);
		}
		fprintf (oldFp, "%s", newFileString);
		printf ("The file you opened has replaced the old file.\n");
		fclose (oldFp);
		manage_mode ();
	}
	
	else if ((strcmp (yesORno, "no") ==0 || strcmp (yesORno, "NO") ==0)) 
		manage_mode ();
 
	else if (strcmp (yesORno, "exit") ==0 || strcmp (yesORno, "EXIT") ==0)
		exit_machine ();
	
	else
	{
		printf ("Can you decide? 'yes' or 'no' only!\nYou can also exit by type 'exit'\n");
		goto decide;
	}
}

void item_Changer ()				//This function lets the admin change a specific item from the list
{
	int y=0, q=0;
	FILE* changeToFile;
	char menu2[10];
	int x=0;
	char new_item_name[100], new_item_price[100];
	int  index_as_int, item_price_int;
	char index_Item[5];
	int num_of_items= numberOfItems (num_of_items);
	
	item itemsChange[num_of_items];		
	scanFile (num_of_items, itemsChange);
	printFile (num_of_items, itemsChange);
	type_index:
	printf ("Please select the number of the item that you want to change:\n");
	scanf ("%s", &index_Item);
	
	if (strcmp (index_Item, "exit" ) ==0 || strcmp (index_Item, "EXIT")==0 )
		exit_machine ();
		
	index_as_int = atoi(index_Item);
	if (index_as_int > num_of_items-1)
	{
		printf ("The name of the item is not legal.\nPlease try again:\n");
		goto type_index;
	}
	
	printf ("Please enter the name of your item:\n");
	scanf("%s",&new_item_name);
	if (strcmp (new_item_name, "exit") ==0 || strcmp (new_item_name, "EXIT") ==0)
		exit_machine ();
	
	for (x=0; new_item_name[x] != '\0'; x++)
	{
		if (new_item_name[x] < 'A')
		{
			printf ("The name of the item is not legal.\nPlease try again:\n");
			goto type_index;
		}
		if (new_item_name[x] > 'Z' && new_item_name[x] < 'a')
		{
			if (new_item_name[x] == '_' )
			goto keepCheck;
			printf ("The name of the item is not legal.\nPlease try again:\n");
			goto type_index;
		}
		keepCheck:
		if (new_item_name[x] > 'z')	
		{
			printf ("The name of the item is not legal.\nPlease try again:\n");
			goto type_index;	
		}
	}
	strcpy(itemsChange[index_as_int].name, new_item_name);

	printf ("Please enter the price of your item:\n");
	scanf ("%s",&new_item_price);
	if (strcmp (new_item_price, "exit") ==0 || strcmp (new_item_price, "EXIT") ==0)
		exit_machine ();
		
	for (x=0; new_item_price[x] != '\0'; x++)
	{
		if (new_item_price[x] < '0' || new_item_price[x] > '9')
		{
			printf ("The name of the item is not legal.\nPlease try again:\n");
			goto type_index;
		}
	}
		
	item_price_int = atoi (new_item_price);
	itemsChange[index_as_int].price = item_price_int;
	changeToFile = fopen("machinedata.txt", "w");
	if (changeToFile == NULL) 
	{
		printf ("The file could not opened.\n");
		exit (-1);
	}
	for (y=0; y<index_as_int; y++)
	{
		fprintf (changeToFile, "%s - %d, ", itemsChange[y].name, itemsChange[y].price);
	}
	
	fprintf (changeToFile, "%s - %d, ", new_item_name, item_price_int);
	
	for (q=index_as_int+1; q<num_of_items; q++)
	{
		fprintf (changeToFile, "%s - %d, ", itemsChange[q].name, itemsChange[q].price);
	}	
	fprintf (changeToFile, ";");
	fclose (changeToFile);
	printf ("The item has successfully changed.\nDo you want to chanage another item? [yes] or [no]\nYou can always type 'exit' to quit:");
	small_menu:
	scanf ("%s", &menu2);
	
	fclose (changeToFile);
	if (strcmp (menu2, "EXIT") ==0 || strcmp (menu2, "exit") ==0)
		exit_machine();
	
	else if (strcmp (menu2, "NO") ==0 || strcmp (menu2, "no") ==0)
		manage_mode ();
			
	else if	(strcmp (menu2, "YES") ==0 || strcmp (menu2, "yes") ==0)
		item_Changer();
	
	else
	{
		printf ("\nYour input is unacceptable!\nPlease try again:");
		goto small_menu;
	}
}
