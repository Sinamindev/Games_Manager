/*-------------------------------------------------------------------------
Developer:		Sina Amini
Description:	Nim Game Header file. Nim-Game, User plays against a Brain AI.
				Both players take turns choosing a row and removing pebbles
				until the winner removes the final pebble from the game board
Game:	Nim-Game
-------------------------------------------------------------------------*/

#ifndef _NIM_H_
#define _NIM_H_

typedef struct NIM_
{
	int *Board;
	int RowCnt;
	int PebCnt;
	int P1_Row;
	int P1_Count;
	int Brain_Row;
	int Brain_Count;
	int valid;
	int turn;
	int Winner;
	int Exit;
} NIM;

void NIM_conversation(NIM *BRA);
void NIM_setup(NIM *BRA);
void NIM_hello(NIM *BRA);
void NIM_listen(NIM *BRA);
int NIM_Validate_Row(NIM *BRA);
int NIM_Validate_Count(NIM *BRA);
void NIM_respond(NIM *BRA);
void NIM_Brain(NIM *BRA);
void NIM_Board_State(NIM *BRA);
int NIM_Brain_Choose_Row(NIM *BRA);
void NIM_Check_Win(NIM *BRA);
int NIM_endcheck(NIM *BRA);
void NIM_cleanup(NIM *BRA);

#endif