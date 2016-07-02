/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Room game body file
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Room.h"
#include "MH.h"

// HOUSE's main user interaction function
// touches HOUSE
// ALine count = 6
void HOUSE_conversation(pHOUSE MYS)
{
	HOUSE_setup(MYS); //setup stub function
	HOUSE_hello(MYS); //greets user

	do
	{
		HOUSE_listen(MYS); // reads user's choice from console
		HOUSE_respond(MYS); // does the needed processing for that input
	} while (HOUSE_endcheck(MYS)); // exit loop if user inputs 0

	HOUSE_cleanup(MYS); // thanks user for playing
}

// performs any needed internal setup for the HOUSE class
// touches HOUSE; sets MYS
// ALine count = 5
void HOUSE_setup(pHOUSE MYS)
{
	//printf("\n** HOUSE_setup");
	MYS = make_house(); //creates a house
	assert(MYS);
	HOUSE_Read_House(MYS); //reads in the room information for the house
	HOUSE_Place_Actors(MYS); //places the actors in their respective rooms
	HOUSE_show(MYS); //show the information of all rooms in the house
	HOUSE_connect_rooms(MYS); //connects all the rooms together with exits respectively
}

// helps places an actor (player/zombie) in separate rooms from eachother
// touches HOUSE
// ALine count = 7
void HOUSE_Place_Actors(pHOUSE MYS)
{
	MYS->Player_location = HOUSE_Place_Actors_Helper(MYS); //assigns player a room
	do{
		MYS->Z1_location = HOUSE_Place_Actors_Helper(MYS); //assigns zombie 1 a room
		MYS->Z2_location = HOUSE_Place_Actors_Helper(MYS); //assigns zombie 2 a room
		MYS->Z3_location = HOUSE_Place_Actors_Helper(MYS); //assigns zombie 3 a room
	} while (MYS->Player_location == MYS->Z1_location || MYS->Player_location == MYS->Z2_location || //loops back if
		MYS->Player_location == MYS->Z3_location || MYS->Z1_location == MYS->Z2_location || //any actors were
		MYS->Z1_location == MYS->Z3_location || MYS->Z2_location == MYS->Z3_location); //placed in the same rooms
}

// places an actor (player/zombie) in a random room
// touches HOUSE
// ALine count = 7
pROOM HOUSE_Place_Actors_Helper(pHOUSE MYS)
{
	int room_number; //create a room number integer
	int ix = 0;
	pROOM pr; // create a pROOM pointer
	pr = MYS->m_rooms_head_ptr; //sets pr to the head of house point MYS

	room_number = (rand() % (10 - 1) + 1); //sets random value to room number between 1-10
	while (ix < room_number){ //iterates through all rooms
		pr = pr->mMH_next_room; //advance to next room
		++ix; //incrament ix
	}
	return pr; //return pr
}

// Announces the HOUSE class to the user
// touches HOUSE
// ALine count = 1
void HOUSE_hello(pHOUSE MYS)
{
	//printf("\nWelcome to HOUSE Game!\n");
	//printf("\nRules for HOUSE Game:");
}

// Gets users move choice
// touches HOUSE; sets
// ALine count = 1
void HOUSE_listen(pHOUSE MYS)
{
	printf("\n\nWhat next?> ");
}

// Does needed processing for user/brain selections if exit was not chosen
// touches HOUSE; sets
// ALine count = 1
void HOUSE_respond(pHOUSE MYS)
{
	printf("\n** HOUSE_respond");
}

// checks whether the user is done playing HOUSE Game
// touches HOUSE
// ALine count = 1
int HOUSE_endcheck(pHOUSE MYS)
{
	printf("\n** HOUSE_endcheck");
	return 0;
}

// Thanks the user for playing HOUSE game
// touches HOUSE
// ALine count = 1
void HOUSE_cleanup(pHOUSE MYS)
{
	printf("\n** HOUSE_cleanup");
}
