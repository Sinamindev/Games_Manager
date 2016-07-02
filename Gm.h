/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Games Manager Header file, repeatedly gets and runs the user's
				game selection until the user decides to quite playing
Games implimented:	guess-a-card, Nim
-------------------------------------------------------------------------*/

#ifndef _GM_H_
#define _GM_H_

typedef struct GM_
{
	int choice; // whether user would like to exit or not
} GM;

void GM_conversation(GM *obj);
void GM_setup(GM *obj);
void GM_hello(GM *obj);
void GM_listen(GM *obj);
void GM_respond(GM *obj);
int GM_endcheck(GM *obj);
void GM_cleanup(GM *obj);
void print_menu();

#endif