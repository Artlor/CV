#pragma once
#include <stdint.h>
#include <iostream>

#include "typpocisku.h"
#include "globalsettings.h"
#include "pociskmanager.h"
#include "whichplayerenum.h"


class Player
{
public:
	Player(uint8_t _positionX, uint8_t _hp, uint16_t _mana, std::string _playerName, WhichPlayerEnum _whichPlayer);
	~Player();

	PociskManager pociskManager;

	void shoot();
	void wantToShootX();
	void wantToShootY();
	void wantToShootZ();
	void gotShot();

	uint8_t getPosition() const;
	std::string getName() const;
	bool isAlive();
	bool doesPlayerWantToShoot();
	void setAllWantsToShootToFalse();
	WhichPlayerEnum getWhichPlayer();
	unsigned short getHp();
	uint16_t getMana();
	TypPocisku getPlayerShootingDecision();
	void addMana(uint8_t _i);
	void subtractMana(uint8_t _i);
	bool manaCheck();
	void countBulletChanges();
	unsigned int getBulletChangesCounter();
	void periodicallyAddMana(uint8_t _i);
	void updateHPBasedOnMana(short _i);
	unsigned short getManaChangeCounter();
	void countManaChange(int8_t _i);

private:
	uint8_t positionX;
	uint16_t hp;
	unsigned short mana;
	std::string playerName;
	char playerGraphic;
	bool playerWantsToShootX;
	bool playerWantsToShootY;
	bool playerWantsToShootZ;
	TypPocisku typPocisku;
	WhichPlayerEnum whichPlayer;
	TypPocisku rememberLastBulletType;
	unsigned int bulletChangesCounter = 0;
	short manaChangeCounter;
	short anchorManaValue;
	bool updateHPBasedOnManaTrigger;

	short previousManaValue;
	short manaValueRemainder;
	short manaValueRemainderAdditional;
};
