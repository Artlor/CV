#pragma once
#include <iomanip>
#include <chrono>

#include "typpocisku.h"
#include "whichplayerenum.h"
#include "globalsettings.h"

class Pocisk
{
public:
	Pocisk(TypPocisku _typPocisku, WhichPlayerEnum _whichPlayer);
	~Pocisk();

	bool isAlive();
	TypPocisku getTypPocisku();
	char getGraphicRepresentation();
	uint8_t getPostionX();
	void minusOneHp();
	void minusTwoHp();
	void moveRight();
	void moveLeft();
	bool canMoveTimer();
	bool isOlderThanBulletSpeed();
	bool isHpFull();

	int i;

private:
	uint8_t positionX;
	char bulletGraphicRepresentation;
	uint8_t hp;
	TypPocisku typPocisku;
	std::chrono::high_resolution_clock::time_point lastTimeStamp;
	bool olderThanBulletSpeed;
};

