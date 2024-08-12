#pragma once
#include "player.h"

void endScreen(Player p1, Player p2)
{
	if (!(p1.isAlive()))
	{
		std::cout << std::endl;
		std::cout << "\t\t\t\t\t\t\t\t\t";
		std::cout << "Gracz o nazwie: \"" << p2.getName() << "\" wygral!" << std::endl;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "\t\t\t\t\t\t\t\t\t";
		std::cout << "Gracz o nazwie: \"" << p1.getName() << "\" wygral!" << std::endl;
	}
}