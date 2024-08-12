#pragma once
#include <iostream>

void drawUpBorder(const uint8_t _distanceBetweenPlayers)
{
	std::string upperAndBottomWall(_distanceBetweenPlayers, '-');
	std::cout << "\t";
	std::cout << " ";
	std::cout << upperAndBottomWall;
	std::cout << "\n";
	std::cout << "\t" << "|";
}

void drawDownBorder(const uint8_t _distanceBetweenPlayers)
{
	std::string upperAndBottomWall(_distanceBetweenPlayers, '-');
	std::cout << "|";
	std::cout << "\n";
	std::cout << "\t";
	std::cout << " ";
	std::cout << upperAndBottomWall;
}