/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Games Manager Body file, repeatedly gets and runs the user's
				game selection until the user decides to quite playing
Games implimented:	guess-a-card, Nim, Mystery-House
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "Gm.h"
#include "Cg.h"
#include "Nim.h"
#include "Room.h"
#include "MH.h"


// main user interaction function
// touches GM
// ALine count = 6
void GM_conversation(GM *obj)
{
	GM_setup(obj); //setup stub function
	GM_hello(obj); //greets user

	do
	{
		GM_listen(obj); //reads user's game choice from consol
		GM_respond(obj); //does the needed processing for that input
	} while (GM_endcheck(obj)); //exit loop if user inputs 0

	GM_cleanup(obj); //cleanup stub function
}

// performs any needed internal setup for the class
// touches GM
// ALine count = 1
void GM_setup(GM *obj)
{
	printf("Setup stub function\n"); //to be implemented
}

// announces the class to the user
// touches GM
// ALine count = 1
void GM_hello(GM *obj)
{
	printf("Welcome to Games Manager\n\n");
}

// asks/gets the user's input, cleaned up if needed
// touches GM; sets choice
// ALine count = 2
void GM_listen(GM *obj)
{
	print_menu(); //print Games Manager menu for user
	scanf("%d", &obj->choice); //read input from console
}

// does the needed processing for that input
// touches GM, CARD
// ALine count = 6
void GM_respond(GM *obj)
{
	//DPRINTF("respond().\n");
	printf("user response: %d\n\n", obj->choice);
	switch (obj->choice)
	{
	case 0: //user decides to exit
		printf("Thanks for playing\n");
		break;
	case 1: //user decides to play guess-a-card
	{
		CARD RGC;
		CARD_conversation(&RGC);
	}
	break;
	case 2: //user decides to play game 2
	{
		NIM BRA;
		NIM_conversation(&BRA);
	}
		break;
	case 3: //user decides to play game 3
	{
		HOUSE MYS;
		HOUSE_conversation(&MYS);
	}
	break;
	default: //user inputs invalid menu option
		printf("Invalid option\n\n");
	}
}

// checks whether the user is done
// touches GM
// ALine count = 1
int GM_endcheck(GM *obj)
{
	if (0 != obj->choice) return 1; //user has not chosen the exit option
	else return 0; //user has chosen the exit option
	printf("\n");
}

// performs any needed internal shutdown for the class
// touches GM
// ALine count = 1
void GM_cleanup(GM *obj)
{
	printf("Cleanup stub function\n"); //to be implemented
}

//prints game menu to user
// ALine count = 1
void print_menu()
{
	printf("Menu\n");
	printf("0. EXIT\n");
	printf("1. Guess-a-Card\n");
	printf("2. Nim Game\n");
	printf("3. Mystery House");
}