#pragma once

#include <string>

using namespace std;

class Strings
{
	string top_wall;
	string down_wall;
	string E6;
	string H5;
	string G4;
	string D3;
	string A2;
	string E1;

	string frets[13];
	char which_string;
	string answer;
	int points_gained;
	int how_many_points_left;

public:
	Strings(char which_string);
	void Creating_string(char which_string);
	void Get();
	string Question(int new_random, int size);
	int Check_answer(string answer, int new_random, int size);
	void Help();
};
