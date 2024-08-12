#pragma once
#include <chrono>
#include "updateenum.h"

std::chrono::high_resolution_clock::time_point lastTimeStamp[UpdateEnum::NumberOfElements] = {};

bool canUpdate(UpdateEnum updateComponent, unsigned short updateTimeInMiliseconds)
{
	auto currentTimeStamp = std::chrono::high_resolution_clock::now();
	static int a = 0, b = 0;
	if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeStamp - lastTimeStamp[updateComponent]).count() >= updateTimeInMiliseconds)
	{
		a++;
		lastTimeStamp[updateComponent] = currentTimeStamp;
		return true;
	}
	else
	{
		b++;
		return false;
	}
}