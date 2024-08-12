#pragma once
#include "player.h"

void hitPlayer(char* _poleWalki, Player& _movingPlayer, Player& _otherPlayer)
{
	_otherPlayer.gotShot();
	_poleWalki[_movingPlayer.pociskManager.getBulletPositionX(0)] = ' ';
	_movingPlayer.pociskManager.killFirstBullet();
}