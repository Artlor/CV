#include "pocisk.h"

Pocisk::Pocisk(TypPocisku _typPocisku, WhichPlayerEnum _whichPlayer)
{
	int i = 0;
	lastTimeStamp = std::chrono::high_resolution_clock::now();
	olderThanBulletSpeed = false;

	typPocisku = _typPocisku;
	this->hp = 2;

	if (_whichPlayer == WhichPlayerEnum::Left)
		positionX = 1;
	else if (_whichPlayer == WhichPlayerEnum::Right)
		positionX = distanceBetweenPlayers - 2;

	switch (_typPocisku)
	{
	case TypPocisku::X: bulletGraphicRepresentation = 'X'; break;
	case TypPocisku::Y: bulletGraphicRepresentation = 'Y'; break;
	case TypPocisku::Z: bulletGraphicRepresentation = 'Z'; break;
	}
}

Pocisk::~Pocisk()
{

}

bool Pocisk::isAlive()
{
	if (this->hp <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

TypPocisku Pocisk::getTypPocisku()
{
	return typPocisku;
}

char Pocisk::getGraphicRepresentation()
{
	return bulletGraphicRepresentation;
}

void Pocisk::minusOneHp()
{
	hp--;
}

void Pocisk::minusTwoHp()
{
	hp -= 2;
}

void Pocisk::moveRight()
{
	positionX++;
}

void Pocisk::moveLeft()
{
	positionX--;
}

uint8_t Pocisk::getPostionX()
{
	return positionX;
}

bool Pocisk::canMoveTimer()
{
	auto currentTimeStamp = std::chrono::high_resolution_clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeStamp - lastTimeStamp).count() >= bulletSpeed)
	{
		i = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeStamp - lastTimeStamp).count();
		lastTimeStamp = currentTimeStamp;
		olderThanBulletSpeed = true;
		return true;
	}
	else
	{
		return false;
	}
}

bool Pocisk::isOlderThanBulletSpeed()
{
	if (olderThanBulletSpeed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Pocisk::isHpFull()
{
	if (hp == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}