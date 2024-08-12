#pragma once

#include "player.h"
#include "globalsettings.h"

void punishForTooManyBulletChanges(Player& _p1, Player& _p2)
{
	if (_p1.getBulletChangesCounter() != 0 && _p2.getBulletChangesCounter() != 0)
	{
		if (_p1.getBulletChangesCounter() - 1 > _p2.getBulletChangesCounter())
		{
			manaPunishment = _p1.getBulletChangesCounter()-_p2.getBulletChangesCounter();
			_p1.subtractMana(manaPunishment);
		}
		else 
		if (_p2.getBulletChangesCounter() - 1 > _p1.getBulletChangesCounter())
		{
			manaPunishment = _p2.getBulletChangesCounter() - _p1.getBulletChangesCounter();
			_p2.subtractMana(manaPunishment);
		}
	}
}