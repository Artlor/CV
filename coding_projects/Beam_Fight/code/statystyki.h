#pragma once

#include "player.h"
#include "globalsettings.h"

void statystyki(Player _p1, Player _p2)
{
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << playerName1 << " '" << playerGraphic1 << "' HP: " << _p1.getHp();
	std::cout << std::endl << "\t";
	std::cout << "mana: " << _p1.getMana();
	std::cout << std::endl;
	std::cout << "bullet changes: " << _p1.getBulletChangesCounter();

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << playerName2 << " '" << playerGraphic2 << "' HP: " << _p2.getHp();
	std::cout << std::endl << "\t";
	std::cout << "mana: " << _p2.getMana();
	std::cout << std::endl;
	std::cout << "bullet changes: " << _p2.getBulletChangesCounter();
}

void statystykiEnd(Player _p1, Player _p2)
{

	std::cout << std::endl;
	std::cout << "\t\t\t\t\t\t\t\t\t\t";
	std::cout << playerName1 << " '" << playerGraphic1 << "' HP: " << _p1.getHp();
	std::cout << std::endl;
	std::cout << "\t\t\t\t\t\t\t\t\t\t";
	std::cout << playerName2 << " '" << playerGraphic2 << "' HP: " << _p2.getHp();
}