/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Games Manager, repeatedly gets and runs the user's
				game selection until the user decides to quit playing
Games implimented:	guess-a-card, Nim, Mystery-House
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gm.h"

#define DPRINTF printf

//main program driver
int main()
{
	//testing atom
	srand(time(NULL)); // randomize value based on current time

	GM obj = { 0 }; //initializes GM object

	GM_conversation(&obj);

	return 0;
}
