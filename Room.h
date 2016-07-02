/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Room game header file
-------------------------------------------------------------------------*/

#ifndef _ROOM_H_
#define _ROOM_H_
#define KEXITS_SIZE 10

typedef struct ROOM_ *pROOM;
typedef struct HOUSE_ *pHOUSE;
typedef struct PLAYER_ *pPlayer;

typedef struct ROOM_
{
	pROOM mMH_next_room;
	char *m_title;
	char *m_desc;
	pROOM m_exits[KEXITS_SIZE];
} ROOM;

typedef struct HOUSE_
{
	pROOM m_rooms_head_ptr;
	pROOM m_rooms;
	int m_room_cnt;
	pROOM m_count;
	int m_qdone;
	pROOM Player_location;
	pROOM Z1_location;
	pROOM Z2_location;
	pROOM Z3_location;
	int Exit;
} HOUSE;

pHOUSE make_house();
void HOUSE_Read_House(pHOUSE this);
pROOM make_room(char * rt, char *rd);
pROOM make_exits(pROOM this);
void HOUSE_prepend_room(pHOUSE this, pROOM RPR);
void HOUSE_show(pHOUSE this);
void ROOM_show(pROOM this);
void PLAYER_Description(pHOUSE MYS, pROOM PLR);
void HOUSE_connect_rooms(pHOUSE RPH);
pROOM HOUSE_get_room(pHOUSE RPH, int RIX);

#endif