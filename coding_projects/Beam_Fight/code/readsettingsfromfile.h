#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "globalsettings.h"
#include <direct.h>
void readSettingsFromFile()
{
	std::string bufferString;
	const size_t size = 1024;
	char buffer[size];
	if (_getcwd(buffer, size) != NULL)
	{
		bufferString = buffer;
		bufferString += "\\settings.txt";
	}
	else 
	{
		return;
	}


	std::string line;
	int i = 1;
	std::ifstream myFile(bufferString);
	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			i++;
			if (i % 2)
			{
				switch (i)
				{
				case 3: playerHp = static_cast<uint8_t>(std::stoi(line));
				case 5: bulletSpeed = static_cast<unsigned short>(std::stoi(line));
				}
			}
		}
		myFile.close();
	}
	else
	{
		exit(0);
	}
}