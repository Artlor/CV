#pragma once
#include "player.h"
#include "whichplayerenum.h"
#include "collisiontype.h"

CollisionType collisionDetector( Player& movingPlayer, Player& otherPlayer)
{
	if (otherPlayer.pociskManager.getNumberOfBullets() != 0)
	{
		if (movingPlayer.getWhichPlayer() == WhichPlayerEnum::Left)
		{
			if (movingPlayer.pociskManager.getBulletPositionX(0) + 1 == otherPlayer.pociskManager.getBulletPositionX(0))
			{
				return CollisionType::BulletHitsBullet;
			}
		}
		else
		if (movingPlayer.getWhichPlayer() == WhichPlayerEnum::Right)
		{
			if (movingPlayer.pociskManager.getBulletPositionX(0) - 1 == otherPlayer.pociskManager.getBulletPositionX(0))
			{
				return CollisionType::BulletHitsBullet;
			}
		}
	}

	if (movingPlayer.getWhichPlayer() == WhichPlayerEnum::Left)
	{
		if (movingPlayer.pociskManager.getBulletPositionX(0) + 1 == otherPlayer.getPosition())
		{
			return CollisionType::BulletHitsPlayer;
		}
	}
	else
	if (movingPlayer.getWhichPlayer() == WhichPlayerEnum::Right)
	{
		if (movingPlayer.pociskManager.getBulletPositionX(0) - 1 == otherPlayer.getPosition())
		{
			return CollisionType::BulletHitsPlayer;
		}
	}

	return CollisionType::NONE;
}