#pragma once

#include "player.h"
#include "whichplayerenum.h"
#include "collisiontypeenum.h"

bool isPlayerHitByBullet(Player& movingPlayer, Player& otherPlayer)
{
	if (movingPlayer.getWhichPlayer() == WhichPlayerEnum::Left)
	{
		if (movingPlayer.pociskManager.getBulletPositionX(0) + 1 == otherPlayer.getPosition())
		{
			return true;
		}
	}
	else
		if (movingPlayer.getWhichPlayer() == WhichPlayerEnum::Right)
		{
			if (movingPlayer.pociskManager.getBulletPositionX(0) - 1 == otherPlayer.getPosition())
			{
				return true;
			}
		}
}