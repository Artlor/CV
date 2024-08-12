#pragma once
#include <iostream>
#include "player.h"
#include "globalsettings.h"
char showPositionOfLastBulletArray[distanceBetweenPlayers];

void showPositionOfLastBullet(Player& _p1, Player _p2)
{
	for (int i = 0; i < distanceBetweenPlayers; i++)
	{
		showPositionOfLastBulletArray[i] = ' ';
	}
	uint8_t p1LastBulletPositionIndicator = _p1.pociskManager.getBulletPositionX(0);
	uint8_t p2LastBulletPositionIndicator = _p2.pociskManager.getBulletPositionX(0);

	showPositionOfLastBulletArray[p1LastBulletPositionIndicator] = '>';
	showPositionOfLastBulletArray[p2LastBulletPositionIndicator] = '<';

	std::cout << std::endl;
	std::cout << "\t";
	std::cout << " ";
	for (int i = 0; i < distanceBetweenPlayers; i++)
	{
		std::cout << showPositionOfLastBulletArray[i];
	}
}