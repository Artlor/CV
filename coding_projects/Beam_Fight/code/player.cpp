#include "player.h"

Player::Player(uint8_t _positionX, uint8_t _hp, uint16_t _mana, std::string _playerName, WhichPlayerEnum _whichPlayer) : positionX(_positionX), hp(_hp), mana(_mana), 
playerName(_playerName), whichPlayer(_whichPlayer), pociskManager(_whichPlayer)
{
	playerWantsToShootX = false;
	playerWantsToShootY = false;
	playerWantsToShootZ = false;
	typPocisku = TypPocisku::NONE;
	rememberLastBulletType = TypPocisku::NONE;
	manaChangeCounter = 0;
	anchorManaValue = 0;

	previousManaValue = mana;
	manaValueRemainder = 0;
}

Player::~Player()
{

}

void Player::shoot()
{
	switch (typPocisku)
		{
		case TypPocisku::X: pociskManager.newX(whichPlayer); this->playerWantsToShootX = false; break;
		case TypPocisku::Y: pociskManager.newY(whichPlayer); this->playerWantsToShootY = false; break;
		case TypPocisku::Z: pociskManager.newZ(whichPlayer); this->playerWantsToShootZ = false; break;
		case TypPocisku::NONE: break;
		}

		if (rememberLastBulletType != typPocisku)
		{
			mana -= shootManaCost;
			rememberLastBulletType = typPocisku;
			countBulletChanges();
			countManaChange(shootManaCost * (-1));
		}
}

void Player::wantToShootX()
{
	this->playerWantsToShootX = true;  typPocisku = TypPocisku::X;
	this->playerWantsToShootY = false;
	this->playerWantsToShootZ = false; 
}

void Player::wantToShootY()
{
	this->playerWantsToShootY = true; typPocisku = TypPocisku::Y;
	this->playerWantsToShootX = false;
	this->playerWantsToShootZ = false;
}

void Player::wantToShootZ()
{
	this->playerWantsToShootZ = true; typPocisku = TypPocisku::Z;
	this->playerWantsToShootX = false;
	this->playerWantsToShootY = false;
}

void Player::gotShot()
{
	hp -= 1;
}

bool Player::isAlive()
{
	if (hp <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

uint8_t Player::getPosition() const
{
	return positionX;
}

std::string Player::getName() const
{
	return playerName;
}

bool Player::doesPlayerWantToShoot()
{
	if (this->playerWantsToShootX || this->playerWantsToShootY || this->playerWantsToShootZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::setAllWantsToShootToFalse()
{
	typPocisku = TypPocisku::NONE;
	playerWantsToShootX = false;
	playerWantsToShootY = false;
	playerWantsToShootZ = false;
}

WhichPlayerEnum Player::getWhichPlayer()
{
	return whichPlayer;
}

unsigned short Player::getHp()
{
	return hp;
}

TypPocisku Player::getPlayerShootingDecision()
{
	if (playerWantsToShootX)
	{
		return TypPocisku::X;
	}
	else
		if (playerWantsToShootY)
		{
			return TypPocisku::Y;
		}
		else 
			if (playerWantsToShootZ)
			{
				return TypPocisku::Z;
			}
}

unsigned short Player::getMana()
{
	return mana;
}

void Player::addMana(uint8_t _i)
{
	mana+=_i;
	if (mana > 2000)
		mana = 2000;
	countManaChange(_i);
}

void Player::subtractMana(uint8_t _i)
{
	if (mana - _i >= 0)
	{
		mana -= _i;
		countManaChange(_i*(-1));
	}
	else
	{
		mana = 0;
	}
}

bool Player::manaCheck()
{
	if (mana - shootManaCost >= 0)
	{
		return true;
	}
	else
	{
		TypPocisku::NONE;
		playerWantsToShootX = false;
		playerWantsToShootY = false;
		playerWantsToShootZ = false;

		return false;
	}
}

void Player::countBulletChanges()
{
	bulletChangesCounter++;
}

unsigned int Player::getBulletChangesCounter()
{
	return bulletChangesCounter;
}

void Player::periodicallyAddMana(uint8_t _i)
{
	addMana(_i);
	countManaChange(_i);
}

void Player::updateHPBasedOnMana(short _i)
{
	
	if (hp + _i>=1)
		hp += _i;
	else
		hp = 1;

	if (hp > 200)
		hp = 200;

}

unsigned short Player::getManaChangeCounter()
{
	return manaChangeCounter;
}

void Player::countManaChange(int8_t _i)
{
	short manaValueDifference = mana - previousManaValue;

	if (abs(manaValueDifference) >=10)
	{
		manaValueRemainder += manaValueDifference - (10 * (manaValueDifference / 10));
		short addOne=0;
		if (abs(manaValueRemainder)>10)
		{
			addOne = manaValueRemainder / 10;
			manaValueRemainder = manaValueRemainder - (10*(manaValueRemainder/10));
		}
		previousManaValue = mana;
	}
}
