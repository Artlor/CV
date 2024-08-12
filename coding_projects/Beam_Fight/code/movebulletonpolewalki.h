#pragma once
#include "player.h"
#include "whichplayerenum.h"
#include "globalsettings.h"

void placeBulletOnPoleWalki(char* _poleWalkiPointer, Player& _player) //FIRST TIME
{
	_poleWalkiPointer[_player.pociskManager.getBulletPositionX(_player.pociskManager.getNumberOfBullets() - 1)] = _player.pociskManager.getBulletGraphicRepresenation(_player.pociskManager.getNumberOfBullets() - 1);
}

void moveBulletOnPoleWalki(char* _poleWalkiPointer, Player& _player, uint8_t _i) //ALL THE OTHER TIMES TILL THE DESTRUCTION OF BULLET
{
	_poleWalkiPointer[_player.pociskManager.getBulletPositionX(_i)] = _player.pociskManager.getBulletGraphicRepresenation(_i);

	if (_player.getWhichPlayer() == WhichPlayerEnum::Left)
	{
		_poleWalkiPointer[_player.pociskManager.getBulletPositionX(_i) - 1] = ' ';
	}
	else if (_player.getWhichPlayer() == WhichPlayerEnum::Right)
	{
		_poleWalkiPointer[_player.pociskManager.getBulletPositionX(_i) + 1] = ' ';
	}
}