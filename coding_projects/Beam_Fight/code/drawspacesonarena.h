#pragma once

void drawSpacesOnArena(char* _poleWalkiPointer, uint8_t _distanceBetweenPlayers)
{
	for (int i = 1; i < _distanceBetweenPlayers - 1; i++)
	{
		_poleWalkiPointer[i] = ' ';
	}
	_poleWalkiPointer = NULL;
}