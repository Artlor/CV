#pragma once
#include "player.h"
#include "bulletcollisiontype.h"
bool movingPlayerBulletIsBetter(char* _poleWalki, Player& _movingPlayer, Player& _otherPlayer);
bool movingPlayerBulletIsWorse(char* _poleWalki, Player& _movingPlayer, Player& _otherPlayer);

bool collideAndCheckIsFatal(BulletCollisionType _collisionType, char* _poleWalki, Player& _movingPlayer, Player& _otherPlayer)
{
	if (_collisionType == BulletCollisionType::TheSameBullet)
	{
		if ((_movingPlayer.pociskManager.isHpFull(0) && _otherPlayer.pociskManager.isHpFull(0)) || (!(_movingPlayer.pociskManager.isHpFull(0)) && !(_otherPlayer.pociskManager.isHpFull(0))))
		{
			_poleWalki[_movingPlayer.pociskManager.getBulletPositionX(0)] = ' ';
			_movingPlayer.pociskManager.killFirstBullet();
			_poleWalki[_otherPlayer.pociskManager.getBulletPositionX(0)] = ' ';
			_otherPlayer.pociskManager.killFirstBullet();
			return true;
		}
		else
		if (_movingPlayer.pociskManager.isHpFull(0) && !(_otherPlayer.pociskManager.isHpFull(0)))
		{
			return movingPlayerBulletIsBetter(_poleWalki, _movingPlayer, _otherPlayer);
		}
		else
		if (!(_movingPlayer.pociskManager.isHpFull(0)) && _otherPlayer.pociskManager.isHpFull(0))
		{
			return movingPlayerBulletIsWorse(_poleWalki, _movingPlayer, _otherPlayer);
		}
	}
	else
	if(_collisionType == BulletCollisionType::XY)
	{
		return movingPlayerBulletIsWorse(_poleWalki, _movingPlayer, _otherPlayer);
	}
	else
	if (_collisionType == BulletCollisionType::YX)
	{
		return movingPlayerBulletIsBetter(_poleWalki, _movingPlayer, _otherPlayer);
	}
	else
	if (_collisionType == BulletCollisionType::XZ)
	{
		return movingPlayerBulletIsBetter(_poleWalki, _movingPlayer, _otherPlayer);
	}
	else
	if (_collisionType == BulletCollisionType::ZX)
	{
		return movingPlayerBulletIsWorse(_poleWalki, _movingPlayer, _otherPlayer);
	}
	else
	if (_collisionType == BulletCollisionType::YZ)
	{
		return movingPlayerBulletIsWorse(_poleWalki, _movingPlayer, _otherPlayer);
	}
	else
	if (_collisionType == BulletCollisionType::ZY)
	{
		return movingPlayerBulletIsBetter(_poleWalki, _movingPlayer, _otherPlayer);
	}
}


bool movingPlayerBulletIsBetter(char* _poleWalki, Player& _movingPlayer, Player& _otherPlayer)
{
	_movingPlayer.addMana(1);
	_otherPlayer.subtractMana(1);

	_poleWalki[_otherPlayer.pociskManager.getBulletPositionX(0)] = ' ';
	_otherPlayer.pociskManager.killFirstBullet();

	_movingPlayer.pociskManager.damageFirstBullet();
	if (!(_movingPlayer.pociskManager.CheckIfFrontBulletIsAlive()))
	{
		_poleWalki[_movingPlayer.pociskManager.getBulletPositionX(0)] = ' ';
		_movingPlayer.pociskManager.killFirstBullet();
		return true;
	}
	else
	{
		return false;
	}
}

bool movingPlayerBulletIsWorse(char* _poleWalki, Player& _movingPlayer, Player& _otherPlayer)
{
	_movingPlayer.subtractMana(1);
	_otherPlayer.addMana(1);

	_poleWalki[_movingPlayer.pociskManager.getBulletPositionX(0)] = ' ';
	_movingPlayer.pociskManager.killFirstBullet();
	_otherPlayer.pociskManager.damageFirstBullet();
	if (!(_otherPlayer.pociskManager.CheckIfFrontBulletIsAlive()))
	{
		_poleWalki[_otherPlayer.pociskManager.getBulletPositionX(0)] = ' ';
		_otherPlayer.pociskManager.killFirstBullet();
	}
	return true;
}