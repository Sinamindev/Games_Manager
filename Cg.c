/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Card Game Body file. Guess-a-card game, user attempts
				to guess a randomly chosen card while being given hints
				as to how close they are to chosen card after each guess
Game:	guess-a-card
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Cg.h"

// CARD's main user interaction function
// touches CARD
// ALine count = 6
void CARD_conversation(CARD *RGC)
{
	CARD_setup(RGC); //setup stub function
	CARD_hello(RGC); //greets user

	do
	{
		CARD_listen(RGC); // reads user's card choice from console
		CARD_respond(RGC); // does the needed processing for that input
	} while (CARD_endcheck(RGC)); // exit loop if user inputs 0

	CARD_cleanup(RGC); // thanks user for playing
}

// performs any needed internal setup for the guess-a-card class
// touches CARD; sets m_secret
// ALine count = 2
void CARD_setup(CARD *RGC)
{
	//srand(time(NULL)); // randomize value based on current time
	RGC->m_secret = (rand() % (52 - 1) + 1); // reduce random value to be 1-52
	printf("random chosen value is: %d\n", RGC->m_secret); // print value (for debugging)
}

// announces the guess-a-card class to the user
// touches CARD
// ALine count = 1
void CARD_hello(CARD *RGC)
{
	printf("Welcome to Guess-a-Card!\n");
}

// asks/gets the user's card choice
// touches CARD; sets m_Iguess
// ALine count = 7
void CARD_listen(CARD *RGC)
{
	printf("Choose a card from a 52 card deck (eg. 'KS' = King of Spade): ");

	scanf(" %[^\n]", &RGC->m_guess); // reads card choice from user input

	RGC->m_guess[10] = '\0'; // null-terminate the string

	printf("You entered: ");
	int i = 0;
	while (RGC->m_guess[i] != '\0') // print until we've hit \0
		printf("%c", RGC->m_guess[i++]); // prints chosen card
	printf("\n ");

	RGC->m_Iguess = cvt_card_to_int(RGC->m_guess); // calls function to convert char input to int
}

// does the needed processing for chosen card
// touches CARD; sets m_delta
// ALine count = 4
void CARD_respond(CARD *RGC)
{
	//DPRINTF("respond().\n");
	RGC->m_delta = abs(RGC->m_secret - RGC->m_Iguess);	// compare users chosen card to secret card
	printf("Difference between guess and secret card: %d\n\n", RGC->m_delta);	// difference between both cards

	if (0 == RGC->m_delta)	// exit game if player chooses correct card
		RGC->m_exit = 0; // sets exit 0
}

// checks whether the user is done playing guess-a-card
// touches CARD
// ALine count = 2
int CARD_endcheck(CARD *RGC)
{
	if (0 != RGC->m_exit) return 1; //user has not chosen the exit option
	else return 0; //user has chosen the exit option
	printf("\n");
}

// Thanks the user for playing guess-a-card game
// touches CARD
// ALine count = 1
void CARD_cleanup(CARD *RGC)
{
	printf("Thanks for playing!\n"); //to be implemented
}

// returns integer value of chosen card
// sets card[]
// ALine count = 7
int cvt_card_to_int(char card[10])
{
	int card_value = 0;
	int rank_value = 0;
	int suit_value = 0;

	rank_value = get_rank(tolower(card[0])); // sets rank value
	if (rank_value != 0) // checks if rank value is valid
		suit_value = get_suit(tolower(card[1])); // sets suit value

	card_value = rank_value + suit_value; // sets total card value

	return card_value;
}

// returns integer value of chosen card rank
// sets rc
// ALine count = 8
int get_rank(char rc)
{
	int retval = 0;
	// 1...13 for 2...A
	if ('a' == rc) retval = 13;
	else if ('k' == rc) retval = 12;
	else if ('q' == rc) retval = 11;
	else if ('j' == rc) retval = 10;
	else if ('t' == rc) retval = 9;
	else retval = rc - '1';
	if (0 > retval || 13 < retval) retval = 0; // return 0 if invalid
	return retval;
}

// returns integer value of chosen card suit
// sets st
// ALine count = 7
int get_suit(char st)
{
	int retval = 0;
	// 1, 13, 26, 39 for c, d, h, s
	switch (st)
	{
	case 'c': retval = 1; break;
	case 'd': retval = 13; break;
	case 'h': retval = 26; break;
	case 's': retval = 39; break;
	default: retval = 0; //user inputs invalid menu option
	}
	return retval;
}