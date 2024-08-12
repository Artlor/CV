#pragma once
#include "typpocisku.h"
#include "pocisk.h"
#include "whichplayerenum.h"

#include <vector>
#include <memory>
#include <iostream>

class PociskManager
{
public:
	PociskManager(WhichPlayerEnum _whichPlayer);
	~PociskManager();

	void newX(WhichPlayerEnum _whichPlayer);
	void newY(WhichPlayerEnum _whichPlayer);
	void newZ(WhichPlayerEnum _whichPlayer);

	bool CheckIfFrontBulletIsAlive();
	bool canMoveTimer(uint8_t _i);
	void moveBullet(uint8_t _i);
	uint8_t getNumberOfBullets();
	bool isOlderThanLastBulletSpeedTime();
	uint8_t getBulletPositionX(uint8_t _i);
	char getBulletGraphicRepresenation(uint8_t _i);
	void killFirstBullet();
	bool isVectorEmpty();
	TypPocisku getBulletType(uint8_t _i);
	void damageFirstBullet();
	bool isHpFull(uint8_t _i);
	void countBullets();
	{
		int x = 0, y = 0, z = 0;
			for (int i = 0; i < vectorPociskow.size(); i++)
			{
				if (vectorPociskow.at(i)->getTypPocisku() == TypPocisku::X)
					x++;
				if (vectorPociskow.at(i)->getTypPocisku() == TypPocisku::Y)
					y++;
				if (vectorPociskow.at(i)->getTypPocisku() == TypPocisku::Z)
					z++;
			}
			std::cout << "\nX: " << x << "\nY: " << y << "\nZ: " << z << "\n" << "vectorSize: " << vectorPociskow.size();
	}
	void bulletPosition()
	{
		if (!(vectorPociskow.empty()))
		{
			std::vector<int> intVector;
			for (int i = 0; i < vectorPociskow.size(); i++)
			{
				intVector.push_back(vectorPociskow.at(i)->getPostionX());
				if (vectorPociskow.at(i)->getPostionX() > 20)
				{
					delete vectorPociskow.at(i);
					vectorPociskow.at(i) = NULL;
					vectorPociskow.erase(vectorPociskow.begin() + i);
					intVector.erase(intVector.begin() + i);
				}
			}
			int liczba = 0;
			for (int i = 0; i < intVector.size(); i++)
			{
				liczba = intVector.at(i);
				std::cout << liczba << " ";
			}
		}
	}
	void getTimeBetweenBullets()
	{
		std::cout << vectorPociskow.at(1)->i << " ";
	}
private:
	std::vector<Pocisk*> vectorPociskow;
	WhichPlayerEnum whichPlayer;
};

