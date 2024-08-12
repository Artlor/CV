#pragma once
#include <iomanip>
#include <iostream>
#include "player.h"

void setupPoleWalki(char* _poleWalkiPointer, const uint8_t _distanceBetweenPlayers, Player _p1, Player _p2)
{
	_poleWalkiPointer[_p1.getPosition()] = playerGraphic1;
	_poleWalkiPointer[_p2.getPosition()] = playerGraphic2;

	for (int i = 1; i < _distanceBetweenPlayers - 1; i++)
	{
		_poleWalkiPointer[i] = ' ';
	}

	std::string upperAndBottomWall(_distanceBetweenPlayers, '-');

	std::cout << "\n\n\n\n\n\n\n\n\n\n";

	std::cout << "\t\t\t\t";
	std::cout << " ";
	std::cout << upperAndBottomWall;
	std::cout << "\n";
	std::cout << "\t\t\t\t" << "|";
	for (int i = 0; i < _distanceBetweenPlayers; i++)
	{
		std::cout << _poleWalkiPointer[i];
	}
	std::cout << "|";
	std::cout << "\n";
	std::cout << "\t\t\t\t";
	std::cout << " ";
	std::cout << upperAndBottomWall;

	_poleWalkiPointer = NULL;
}