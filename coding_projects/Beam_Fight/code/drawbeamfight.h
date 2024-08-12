#pragma once
#include <iomanip>
#include <iostream>
#include "drawborders.h"
#include "globalsettings.h"

void drawBeamFight(char* _poleWalkiPointer, const uint8_t _distanceBetweenPlayers)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < _distanceBetweenPlayers; i++)
	{
		if (_poleWalkiPointer[i] == 'X')
		{
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << _poleWalkiPointer[i];
			SetConsoleTextAttribute(hConsole, 7);
		}
		else
		if (_poleWalkiPointer[i] == 'Y')
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			std::cout << _poleWalkiPointer[i];
			SetConsoleTextAttribute(hConsole, 7);
		}
		else
		if (_poleWalkiPointer[i] == 'Z')
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			std::cout << _poleWalkiPointer[i];
			SetConsoleTextAttribute(hConsole, 7);
		}
		else
		std::cout << _poleWalkiPointer[i];
	}
	_poleWalkiPointer[0] = playerGraphic1;
	_poleWalkiPointer[distanceBetweenPlayers - 1] = playerGraphic2;

	_poleWalkiPointer = NULL;
}