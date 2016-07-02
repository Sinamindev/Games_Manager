/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Nim Game Body file. Nim-Game, User plays against a Brain AI.
				Both players take turns choosing a row and removing pebbles
				until the winner removes the final pebble from the game board
Game:	Nim-Game
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "Nim.h"

// NIM's main user interaction function
// touches NIM
// ALine count = 6
void NIM_conversation(NIM *BRA)
{
	NIM_setup(BRA); //setup stub function
	NIM_hello(BRA); //greets user

	do
	{
		NIM_listen(BRA); // reads user's choice from console
		NIM_respond(BRA); // does the needed processing for that input
	} while (NIM_endcheck(BRA)); // exit loop if user inputs 0

	NIM_cleanup(BRA); // thanks user for playing
}

// performs any needed internal setup for the NIM class
// touches NIM; sets Winner, RowCnt, Board
// ALine count = 6
void NIM_setup(NIM *BRA)
{
	BRA->Winner = 0;	// Sets Winner to no-one
	BRA->RowCnt = (rand() % (4 - 1) + 3); // Randomly sets #rows to be 3-5
	BRA->Board = (int*)malloc(sizeof(NIM) * BRA->RowCnt); // Allocates necessary board space

	int i;
	for (i = 0; i < BRA->RowCnt; ++i)	// loops through entire board, setting each row value randomly
	{
		BRA->Board[i] = (rand() % (8 - 1) + 2); // Randomly sets each row value to be 2-8
		printf("Number of pebbles in row %d is: %d\n", i, BRA->Board[i]); // print values of pebbles in each row
	}
}

// Announces the NIM class to the user
// touches NIM
// ALine count = 5
void NIM_hello(NIM *BRA)
{
	printf("\nWelcome to Nim Game!\n");
	printf("\nRules for Nim Game:");
	printf("\nFor each player, \npick one none-empty row and remove one or more pebble(s), up to all of them.\n");
	printf("\nThe game ends when a player takes the last remaining pebble(s) \nfrom the last non-empty row.\n");
	printf("\nTo Exit, enter 999 as Row at anytime!\n\n");
}

// Gets users row/count choice
// touches NIM; sets P1_Row, P1_Count
// ALine count = 8
void NIM_listen(NIM *BRA)
{
	printf("\nPlayer 1\n Choose Row(0-%d): ", BRA->RowCnt - 1); // prompts user to choose a row value
	do{
		scanf("%d", &BRA->P1_Row);	// Reads in Player 1's chosen row value
	} while (NIM_Validate_Row(BRA)); // Validates the chosen row value

	if (BRA->Exit != 1)	// If user chooses not to exit (Row != 999), ask for count
	{
		printf(" Choose Count(1-%d): ", BRA->Board[BRA->P1_Row]); // prompts user to choose a count value
		do{
			scanf("%d", &BRA->P1_Count);	// Reads in Player 1's chosen count value
		} while (NIM_Validate_Count(BRA));	// Validates chosen count value

		printf("\nYou take %d pebble(s) from %d\n", BRA->P1_Count, BRA->P1_Row); // Displays User's decision
	}
}

// Validates the Row choice from user input
// touches NIM; sets valid, Exit
// ALine count = 7
int NIM_Validate_Row(NIM *BRA)
{
	BRA->valid = 1; // initializes valid to 1

	if (0 != BRA->Board[BRA->P1_Row] && BRA->P1_Row < BRA->RowCnt) BRA->valid = 0; // Sets valid to 0 if chosen row is valid
	else if (BRA->P1_Row == 999)	// If user chooses to exit mid-game, (Row = 999)
	{
		BRA->valid = 0; // Set valid to 0 since choosing to exit is a valid option
		BRA->Exit = 1; // sets Exit to 1, since user decided to exit game
	}
	else printf("\nInvalid Row selection.\n Choose Row(0-%d) : ", BRA->RowCnt - 1); // print error if selection is invalid

	return BRA->valid;	// Return valid value to caller (0 or 1)
}

// Validates the Row choice from user input
// touches NIM; sets valid
// ALine count = 4
int NIM_Validate_Count(NIM *BRA)
{
	BRA->valid = 1; // initialized valid to 1

	if (0 < BRA->P1_Count) BRA->valid = 0; // Sets valid to 1 if chosen Count is valid
	else printf("\nInvalid Count selection.\n Choose Count(1-%d): ", BRA->Board[BRA->P1_Row]); // print error if selection is invalid

	return BRA->valid;
}

// Does needed processing for user/brain selections if exit was not chosen
// touches NIM; sets turn, Board[]
// ALine count = 10
void NIM_respond(NIM *BRA)
{
	if (BRA->Exit != 1)	// continue if user has chosen not to exit
	{
		// sets row count to 0 if chosen count is larger than given number of pebbles
		if (0 > (BRA->Board[BRA->P1_Row] -= (BRA->P1_Count))) BRA->Board[BRA->P1_Row] = 0;

		BRA->turn = 1;	// specifies its Player 1's turn
		NIM_Board_State(BRA); // shows board state
		NIM_Check_Win(BRA); // Checks to see if player 1 has won

		if (1 != BRA->Winner) // continue if player 1 has not won the game
		{
			BRA->turn = 2; // specifies its Brain's turn
			NIM_Brain(BRA); // Performs Brain's turn
			NIM_Board_State(BRA); // shows board state
			NIM_Check_Win(BRA); // Checks to see if Brain has won
		}
	}
}

// Randomly chooses row/count values for Brain
// touches NIM; sets Brain_Row, Brain_Count, Board[]
// ALine count = 4
void NIM_Brain(NIM *BRA)
{
	BRA->Brain_Row = NIM_Brain_Choose_Row(BRA); // Randomly sets a valid row for Brain
	BRA->Brain_Count = (rand() % ((BRA->Board[BRA->Brain_Row])) + 1); // Randomly sets a valid count for Brain
	BRA->Board[BRA->Brain_Row] -= BRA->Brain_Count; // decraments the chosen count of pebbles from chosen row

	printf("\nI take %d pebble(s) from row %d\n", BRA->Brain_Count, BRA->Brain_Row); // prints Brain's moves
}

// Prints the state of the Nim Game board
// touches NIM;
// ALine count = 2
void NIM_Board_State(NIM *BRA)
{
	int i;
	for (i = 0; i < BRA->RowCnt; ++i) // Loops through the board
		printf("Number of pebbles in row %d is: %d\n", i, BRA->Board[i]); // prints number of pebbles in each row
}

// Helps Brain choose Row randomly
// touches NIM; sets valid, Row
// ALine count = 6
int NIM_Brain_Choose_Row(NIM *BRA)
{
	BRA->valid = 1; // sets valid to 1
	int Row;

	while (BRA->valid) // loops until valid row is chosen for brain
	{
		Row = (rand() % (BRA->RowCnt)); // Selects a random row from given number of rows
		if (0 != BRA->Board[Row]) // checks to see if row is not empty
			BRA->valid = 0; // if row is not empty, set valid to 0
	}
	return Row; // return the chosen valid row value to caller
}

// Checks if either Player 1 or Brain has won the Nim Game
// touches NIM; sets sum, Winner
// ALine count = 6
void NIM_Check_Win(NIM *BRA)
{
	int sum = 0; // sets sum to 0
	int i;

	for (i = 0; i < BRA->RowCnt; ++i) // loops through rows
		sum += BRA->Board[i]; // sums the number of pebbles in each row

	if (0 == sum) // continue if sum of pebbles is 0
		BRA->Winner = BRA->turn; // Selects the winner of the game when sum is 0 on their turn

	if (1 == BRA->Winner) printf("\nCongratulations! You win the Nim game!\n\n"); // Congratulates User for winning
	else if (2 == BRA->Winner) printf("\nWow! Looks like I win the Nim game!\n\n"); // Declares Brain the winner
}

// checks whether the user is done playing Nim Game
// touches NIM
// ALine count = 2
int NIM_endcheck(NIM *BRA)
{
	if (0 == BRA->Winner && 1 != BRA->Exit) return 1; //No-one has won and the user has not chosen the exit option
	else  return 0; //The game was won or the user chose the exit option
	printf("\n");
}

// Thanks the user for playing Nim game
// touches NIM
// ALine count = 2
void NIM_cleanup(NIM *BRA)
{
	free(BRA->Board); // free the malloced space for Nim game board
	printf("Thanks for playing!\n\n"); // Thanks the user for playing
}
