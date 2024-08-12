#pragma once
#include <Windows.h>
#include "player.h"

void playersInput(Player* _player1, Player* _player2)
{
	//									P1 input
	if (GetKeyState(0x51) < 0) //Q
	{
		_player1->wantToShootX();
	}
	if (GetKeyState(0x57) < 0) //W
	{
		_player1->wantToShootY();
	}
	if (GetKeyState(0x45) < 0) //E
	{
		_player1->wantToShootZ();
	}
	//									P2 input
	if (GetKeyState(0x50) < 0) //P
	{
		_player2->wantToShootX();
	}
	if (GetKeyState(0xDB) < 0) //[
	{
		_player2->wantToShootY();
	}
	if (GetKeyState(0xDD) < 0) //]
	{
		_player2->wantToShootZ();
	}
}