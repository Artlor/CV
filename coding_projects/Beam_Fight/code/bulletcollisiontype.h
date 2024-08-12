#pragma once
#include "player.h"
#include "whichplayerenum.h"
#include "bulletcollisiontypeenum.h"


BulletCollisionType getBulletCollisionType(Player& movingPlayer, Player& otherPlayer)
{
		if (movingPlayer.pociskManager.getBulletType(0) == otherPlayer.pociskManager.getBulletType(0))
		{
			return BulletCollisionType::TheSameBullet;
		}
		
		if (movingPlayer.pociskManager.getBulletType(0) == TypPocisku::X && otherPlayer.pociskManager.getBulletType(0) == TypPocisku::Y)
		{
			return BulletCollisionType::XY;
		}
		
		if (movingPlayer.pociskManager.getBulletType(0) == TypPocisku::Y && otherPlayer.pociskManager.getBulletType(0) == TypPocisku::X)
		{
			return BulletCollisionType::YX;
		}
		
		if (movingPlayer.pociskManager.getBulletType(0) == TypPocisku::Y && otherPlayer.pociskManager.getBulletType(0) == TypPocisku::Z)
		{
			return BulletCollisionType::YZ;
		}
		
		if (movingPlayer.pociskManager.getBulletType(0) == TypPocisku::Z && otherPlayer.pociskManager.getBulletType(0) == TypPocisku::Y)
		{
			return BulletCollisionType::ZY;
		}
		
		if (movingPlayer.pociskManager.getBulletType(0) == TypPocisku::X && otherPlayer.pociskManager.getBulletType(0) == TypPocisku::Z)
		{
			return BulletCollisionType::XZ;
		}
		
		if (movingPlayer.pociskManager.getBulletType(0) == TypPocisku::Z && otherPlayer.pociskManager.getBulletType(0) == TypPocisku::X)
		{
			return BulletCollisionType::ZX;
		}
}