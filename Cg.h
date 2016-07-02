/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Card Game Header file. Guess-a-card game, user attempts
				to guess a randomly chosen card while being given hints
				as to how close they are to chosen card after each guess
Game:	guess-a-card
-------------------------------------------------------------------------*/

#ifndef _CG_H_
#define _CG_H_

typedef struct CARD_
{
	int m_secret;
	int m_exit;
	int m_Iguess;
	int m_delta;
	char m_guess[10];
} CARD;

void CARD_conversation(CARD *RGC);
void CARD_setup(CARD *RGC);
void CARD_hello(CARD *RGC);
void CARD_listen(CARD *RGC);
void CARD_respond(CARD *RGC);
int CARD_endcheck(CARD *RGC);
void CARD_cleanup(CARD *RGC);
int cvt_card_to_int(char card[10]);
int get_rank(char rc);
int get_suit(char st);

#endif