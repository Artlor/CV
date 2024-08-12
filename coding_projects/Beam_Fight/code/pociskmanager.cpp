#include "pociskmanager.h"

PociskManager::PociskManager(WhichPlayerEnum _whichPlayer): whichPlayer(_whichPlayer)
{

}

PociskManager::~PociskManager()
{

}

void PociskManager::newX(WhichPlayerEnum _whichPlayer)
{
	vectorPociskow.push_back(new Pocisk(TypPocisku::X, _whichPlayer));
}

void PociskManager::newY(WhichPlayerEnum _whichPlayer)
{
	vectorPociskow.push_back(new Pocisk(TypPocisku::Y, _whichPlayer));
}

void PociskManager::newZ(WhichPlayerEnum _whichPlayer)
{
	vectorPociskow.push_back(new Pocisk(TypPocisku::Z, _whichPlayer));
}

bool PociskManager::CheckIfFrontBulletIsAlive()
{
	if ((vectorPociskow.at(0)->isAlive()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PociskManager::canMoveTimer(uint8_t _i)
{
	return vectorPociskow.at(_i)->canMoveTimer();
}

void PociskManager::moveBullet(uint8_t _i)
{
	if (whichPlayer == WhichPlayerEnum::Left)
	{
		vectorPociskow.at(_i)->moveRight();
	}
	else if (whichPlayer == WhichPlayerEnum::Right)
	{
		vectorPociskow.at(_i)->moveLeft();
	}
}

uint8_t PociskManager::getNumberOfBullets()
{
		return vectorPociskow.size();
}

bool PociskManager::isOlderThanLastBulletSpeedTime()
{
	if (!(vectorPociskow.empty()))
	{
		return vectorPociskow.at(vectorPociskow.size() - 1)->isOlderThanBulletSpeed();
	}
	else
	{
		return true;
	}
}


uint8_t PociskManager::getBulletPositionX(uint8_t _i)
{
	if (vectorPociskow.empty())
		return 0;
	else
	return vectorPociskow.at(_i)->getPostionX();
}

char PociskManager::getBulletGraphicRepresenation(uint8_t _i)
{
	return vectorPociskow.at(_i)->getGraphicRepresentation();
}

void PociskManager::killFirstBullet()
{
	delete vectorPociskow.at(0);
	vectorPociskow.at(0) = NULL;
	vectorPociskow.erase(vectorPociskow.begin());
}

bool PociskManager::isVectorEmpty()
{
	return vectorPociskow.empty();
}

TypPocisku PociskManager::getBulletType(uint8_t _i)
{
	return vectorPociskow.at(_i)->getTypPocisku();
}

void PociskManager::damageFirstBullet()
{
	vectorPociskow.at(0)->minusOneHp();
}

bool PociskManager::isHpFull(uint8_t _i)
{
	return vectorPociskow.at(_i)->isHpFull();
}