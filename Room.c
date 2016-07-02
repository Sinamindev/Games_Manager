/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Room game body file
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Room.h"

const char *directions[] = { "the north (N)", "the northeast (NE)", "the east (E)", "the southeast (SE)",
							"the south (S)", "the southwest (SW)", "the west (W)", "the northwest(NW)",
							"stairs leading upward (UP)", "sliding chute leads downward (DN)" };

// Creates a house consisting of rooms (pointers)
// touches pHOUSE; sets m_rooms_head_ptr, m_qdone, m_room_cnt
// ALine count = 5
pHOUSE make_house()
{
	//printf("\n** make house\n");
	pHOUSE ph = malloc(sizeof(HOUSE));
	assert(ph);
	ph->m_rooms_head_ptr = 0;
	ph->m_qdone = 0;
	ph->m_room_cnt = 0;
	return ph;
}

// Reads room information from file to build the house
// touches pHOUSE; sets choice
// ALine count = 4
//issues: unable to correctly read information from file. (hard coded array)
void HOUSE_Read_House(pHOUSE this)
{
	//printf("** HOUSE_Read_House\n");
	char * room_strs[20] =
	{ "kitchen", "a table, stove and a big unreachable knife.",
	"Master_Bedroom", "a huge master bedroom containing a giant four-poster canopy bed.",
	"Long_Hallway,", "a long hallway with green vines and grapes figured into the wallpaper.",
	"Dining_Room", "a long dining room with dim lighting.",
	"Bunny_Room", "a room full of hoppers.",
	"Hallway,", "a hallway with murrals of myths",
	"Child_Bedroom", "a bedroom filled with the dolls of young children.",
	"Bath_Room", "a bathroom with a leaky faucet and dirty mirror",
	"Walk_in_Closet,", "a large closet filled with battered clothing.",
	"Game_Room", "a room with an old CRT television and Super Nintendo system." };

	int ix;
	assert(this);

	for (ix = 0; ix < 20; ix += 2)
	{
		pROOM pr = make_room(room_strs[ix], room_strs[ix + 1]);
		HOUSE_prepend_room(this, pr);
	}

	//int ix;
	//FILE *fp;
	//const size_t buffer_size = 300;
	//char* buffer = malloc(buffer_size);

	//fp = fopen("Room_File.txt", "r");
	//fgets(buffer, buffer_size, (FILE*)fp);

	//printf("1: %s\n", buffer);
	//char * room_strs[20];
	//for (ix = 0; ix < 20; ix += 2)
	//{
	//	fgets(buffer, buffer_size, (FILE*)fp);
	//	room_strs[ix] = buffer;
	//	printf(" %s\n", room_strs[ix]);
	//	fgets(buffer, buffer_size, (FILE*)fp);
	//	room_strs[ix + 1] = buffer;
	//	printf(" %s\n", room_strs[ix + 1]);

	//	pROOM pr = make_room(room_strs[ix], room_strs[ix + 1]);
	//	HOUSE_prepend_room(this, pr);
	//}
	//fclose(fp);
}

// Creates each room of the house based on the descriptions of each room in file
// touches pROOM; sets m_title, m_desc, mMH_next_room, m_exits[]
// ALine count = 7
pROOM make_room(char * rt, char *rd)
{
	//printf("\n** make_room\n");
	pROOM px = malloc(sizeof(ROOM)); //allocates space for a room
	assert(px);
	px->m_title = rt; //sets the title for this room
	px->m_desc = rd; //sets the description for this room
	px->mMH_next_room = 0; //sets the pointer to next room to 0

	for (int i = 0; i < KEXITS_SIZE; ++i)	px->m_exits[i] = 0; //sets all exits to 0
	px = make_exits(px); //create exits for each room

	return px;
}

// Assigns random exit directions for each room
// touches pROOM; sets m_exits, exit_directions, exit_size
// ALine count = 8
pROOM make_exits(pROOM this)
{
	//printf("\n** make_exits\n");
	int exit_size; //will hold a random value of exits from a specific room
	int exit_direction; //will hold a random direction value
	int exit_possibilities[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //array of possible exits directions

	exit_size = (rand() % (8 - 1) + 2); // chooses random value between 2-8 for # of exits

	for (int i = 0; i < exit_size; ++i) //loops up until the randomly chosen exit_size value
	{
		exit_direction = (rand() % (10 - 1) + 1); //chooses a random direction between 1-10
		this->m_exits[i] = exit_possibilities[exit_direction]; //sets the direction of the ith exit
		exit_possibilities[exit_direction] = 0; //prevents repeating exit directions
	}

	return this;
}

// Links each room of the house together
// touches pROOM, pHOUSE; sets m_room_head_ptr, m_room_cnt, mMH_next_room
// ALine count = 5
void HOUSE_prepend_room(pHOUSE this, pROOM RPR)
{
	//printf("** HOUSE_prepend_room\n");
	pROOM OLD_HEAD_PTR = this->m_rooms_head_ptr; //sets a temp head pointer
	pROOM new_head_ptr = RPR; //sets a new pointer
	new_head_ptr->mMH_next_room = OLD_HEAD_PTR; //sets the next room of the new head pointer
	this->m_rooms_head_ptr = new_head_ptr; //sets the head pointer of pHOUSE
	this->m_room_cnt += 1; //incraments the room count
}

// Displays the information of a specific house
// touches pHOUSE; sets
// ALine count = 10
void HOUSE_show(pHOUSE this)
{
	//printf("** HOUSE_show\n");
	pROOM pr;
	assert(this);
	printf("(house @%p:\n", this); //prints address of house
	printf(" qdone = %d\n", this->m_qdone); //prints quit value
	printf(" m_rooms_head_ptr = %p\n", this->m_rooms_head_ptr); //prints the value of the head pointer
	printf(" Player_location = %p\n", this->Player_location); //prints address of player location
	printf(" Z1_location = %p\n", this->Z1_location); //prints address of zombie 1 location
	printf(" Z2_location = %p\n", this->Z2_location); //prints address of zombie 2 location
	printf(" Z3_location = %p\n", this->Z3_location); //prints address of zombie 3 location
	pr = this->m_rooms_head_ptr; //sets pr to m_rooms_head_ptr
	while (pr) //iterate through pr
	{
		ROOM_show(pr); //display information for room
		pr = pr->mMH_next_room; //advance to next room
	}
	printf(")\n\n");
	PLAYER_Description(this, pr); //describe location of player
}

// Displays the information of a room in the house
// touches pROOM; sets
// ALine count = 7
void ROOM_show(pROOM this)
{
	//printf("** ROOM_show\n");
	int ix;
	assert(this);
	printf("(room @ %p:\n", this); //prints the address of the room
	printf(" title = %s\n", this->m_title); //prints title of room
	printf(" desc = %s\n", this->m_desc); //prints descriptions of room
	printf(" next_room = %p\n", this->mMH_next_room); //prints address of next room
	for (ix = 0; ix < KEXITS_SIZE; ++ix) //iterates though exits of room
	{
		pROOM pr = this->m_exits[ix]; //sets pr to m_exits
		if (pr) printf(" E#%d = %p\n", ix, pr); //prints every exits to the room
	}
}

// Describes the location and exits to the player
// touches pROOM, pHOUSE; sets
// ALine count = 7
void PLAYER_Description(pHOUSE MYS, pROOM PLR)
{
	int ix;
	PLR = MYS->m_rooms_head_ptr; // sets the head pointer to PLR
	while (PLR != MYS->Player_location) PLR = PLR->mMH_next_room; //advance to next room

	printf("You are in the %s with a %s\n", PLR->m_title, PLR->m_desc); //describes room
	printf("\nThere are exits to the ");
	for (ix = 0; ix < KEXITS_SIZE; ++ix) //iterates through all possible exits
	{
		pROOM pr = PLR->m_exits[ix]; //sets pr to m_exit
		if (pr) printf("%s, ", directions[ix]); //prints exit direction if available
	}
}

// Connects each room of the house together
// touches pHOUSE; sets m_exits, exit_count
// ALine count = 8
void HOUSE_connect_rooms(pHOUSE RPH)
{
	//printf("** HOUSE_connect_rooms\n");
	assert(RPH);
	for (int ix = 0; ix < RPH->m_room_cnt; ++ix)//each source room
	{
		pROOM pr_SRC = HOUSE_get_room(RPH, ix);
		assert(pr_SRC);
		int exit_count = 3 + rand() % 5; //sets random value for exit_count
		for (int iy = 0; iy < exit_count; ++iy)//each exit
		{
			//create exit from src to tgt room
			int DIR_ix = rand() % 10; //pick random direction
			int TGT_ix = rand() % RPH->m_room_cnt; //pick random room to go to
			pROOM pr_TGT = HOUSE_get_room(RPH, TGT_ix);//get that room
			pr_SRC->m_exits[DIR_ix] = pr_TGT;//connect src to tgt via exit

		}//for iy //an exit
	}//for ix //each source room
}

// returns a pointer to a room
// touches pHOUSE; sets
// ALine count = 5
pROOM HOUSE_get_room(pHOUSE RPH, int RIX)
{
	//printf("** HOUSE_get_room\n");
	int ix = 0;
	pROOM pr = RPH->m_rooms_head_ptr;
	while (pr)
	{
		if (ix == RIX) break;
		++ix;//adv index
		pr = pr->mMH_next_room;
	}
	return pr;
}



