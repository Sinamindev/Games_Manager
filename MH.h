/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	HOUSE game header file
-------------------------------------------------------------------------*/

#ifndef _HOUSE_H_
#define _HOUSE_H_

//typedef struct PLAYER_
//{
//	pROOM m_where_am_i;
//} PLAYER;
//
//typedef struct ZOMBIE_
//{
//	pROOM m_where_am_i;
//} ZOMBIE;

void HOUSE_conversation(pHOUSE MYS);
void HOUSE_setup(pHOUSE MYS);
void HOUSE_Place_Actors(pHOUSE MYS);
pROOM HOUSE_Place_Actors_Helper(pHOUSE MYS);
void HOUSE_hello(pHOUSE MYS);
void HOUSE_listen(pHOUSE MYS);
void HOUSE_respond(pHOUSE MYS);
int HOUSE_endcheck(pHOUSE MYS);
void HOUSE_cleanup(pHOUSE MYS);

#endif