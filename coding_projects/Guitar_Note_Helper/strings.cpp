#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#include "strings.h"

using namespace std;

string basic_frets[13] = { "E","F","Fis","G","Gis","A","B","H","C","Cis","D","Dis","E" };

Strings::Strings(char which_string) :which_string(which_string)
{
	top_wall = " /\\_/\\_/\\_\n|         |\n";
	down_wall = "|  _  _  _|\n \\/ \\/ \\/\n";
	E6 = "|  M     E|   1   |   2   |   3   |  4  |  5  |  6  |  7  | 8 | 9 |10 |11 |12 |\n";
	H5 = "|  A     H|   1   |   2   |   3   |  4  |  5  |  6  |  7  | 8 | 9 |10 |11 |12 |\n";
	G4 = "|  D     G|   1   |   2   |   3   |  4  |  5  |  6  |  7  | 8 | 9 |10 |11 |12 |\n";
	D3 = "|  M     D|   1   |   2   |   3   |  4  |  5  |  6  |  7  | 8 | 9 |10 |11 |12 |\n";
	A2 = "|  A     A|   1   |   2   |   3   |  4  |  5  |  6  |  7  | 8 | 9 |10 |11 |12 |\n";
	E1 = "|  N     E|   1   |   2   |   3   |  4  |  5  |  6  |  7  | 8 | 9 |10 |11 |12 |\n";
	Creating_string(which_string);
}

void Strings::Creating_string(char which_string)
{
	how_many_points_left = 13;
	points_gained = 0;
	switch (which_string)
	{
	case 'E':
		for (int i = 0; i < 13; i++)
		{
			frets[i] = ::basic_frets[i];
		}
		break;

	case 'A':
		for (int i = 0; i < 13; i++)
		{
			if (i > 7)
			{
				frets[i] = ::basic_frets[i - 7];
			}
			else
				frets[i] = ::basic_frets[i + 5];
		}
		break;

	case 'D':
		for (int i = 0; i < 13; i++)
		{
			if (i > 2)
			{
				frets[i] = ::basic_frets[i - 2];
			}
			else
				frets[i] = ::basic_frets[i + 10];
		}
		break;

	case 'G':
		for (int i = 0; i < 13; i++)
		{
			if (i > 9)
			{
				frets[i] = ::basic_frets[i - 9];
			}
			else
				frets[i] = ::basic_frets[i + 3];
		}
		break;

	case 'H':
		for (int i = 0; i < 13; i++)
		{
			if (i > 5)
			{
				frets[i] = ::basic_frets[i - 5];
			}
			else
				frets[i] = ::basic_frets[i + 7];
		}
		break;

	case 'B':
		for (int i = 0; i < 13; i++)
		{
			if (i > 5)
			{
				frets[i] = ::basic_frets[i - 5];
			}
			else
				frets[i] = ::basic_frets[i + 7];

			frets[0] = "B";
			frets[11] = "Ais";
			frets[12] = "B";
		}
		break;
	}
}

void Strings::Get()
{
	for (int i = 0; i < 13; i++)
	{
		cout << frets[i] << endl;
	}
}

string Strings::Question(int new_random, int size)
{
	string::size_type position;
	static int last_random = NULL;
	static bool E_lock = true;
	static int zmiana = 0;
	cout << "Twoje punkty: " << points_gained << "\n\n";
	if (points_gained > 12)
		cout << "Opanowales te strune juz calkiem niezle, moze czas na inna? (CHANGE)\n\n";
	cout << "Zostalo Ci jeszcze " << how_many_points_left << " progow do odgadniecia\n";
	cout << "Jesli chcesz wyjsc, wpisz: EXIT\n";
	cout << "Aby uzyskac podpowiedz, wpisz: HELP\n";
	cout << "Aby zmienic strune, wpisz: CHANGE\n";
	cout << "Struna: " << which_string << "\nProg: " << new_random << "\n\n";

	if (new_random || last_random != NULL)
	{
		switch (which_string)
		{
		case 'E':if (E_lock)
		{
			position = E6.find('X');
			if (position != string::npos)
				if (last_random <= 9)
					E6.replace(position, 1, to_string(last_random));
				else
					E6.replace(position - 1, 2, to_string(last_random));

			if (!new_random)
				break;
			position = E6.find(to_string(new_random));
			if (position == string::npos)
				break;
			if (new_random <= 9)
				E6[position] = 'X';
			else
			{
				E6[position] = ' ';
				E6[position + 1] = 'X';
			}
			break;
		}
				 else
				 {
					 position = E1.find('X');
					 if (position != string::npos)
						 if (last_random <= 9)
							 E1.replace(position, 1, to_string(last_random));
						 else
							 E1.replace(position - 1, 2, to_string(last_random));

					 if (!new_random)
						 break;
					 position = E1.find(to_string(new_random));
					 if (position == string::npos)
						 break;
					 if (new_random <= 9)
						 E1[position] = 'X';
					 else
					 {
						 E1[position] = ' ';
						 E1[position + 1] = 'X';
					 }
					 break;
				 }

		case 'H':position = H5.find('X');
			if (position != string::npos)
				if (last_random <= 9)
					H5.replace(position, 1, to_string(last_random));
				else
					H5.replace(position - 1, 2, to_string(last_random));

			if (!new_random)
				break;
			position = H5.find(to_string(new_random));
			if (position == string::npos)
				break;
			if (new_random <= 9)
				H5[position] = 'X';
			else
			{
				H5[position] = ' ';
				H5[position + 1] = 'X';
			}
			break;
		case 'G':position = G4.find('X');
			if (position != string::npos)
				if (last_random <= 9)
					G4.replace(position, 1, to_string(last_random));
				else
					G4.replace(position - 1, 2, to_string(last_random));

			if (!new_random)
				break;
			position = G4.find(to_string(new_random));
			if (position == string::npos)
				break;
			if (new_random <= 9)
				G4[position] = 'X';
			else
			{
				G4[position] = ' ';
				G4[position + 1] = 'X';
			}
			break;

		case 'D':position = D3.find('X');
			if (position != string::npos)
				if (last_random <= 9)
					D3.replace(position, 1, to_string(last_random));
				else
					D3.replace(position - 1, 2, to_string(last_random));

			if (!new_random)
				break;
			position = D3.find(to_string(new_random));
			if (position == string::npos)
				break;
			if (new_random <= 9)
				D3[position] = 'X';
			else
			{
				D3[position] = ' ';
				D3[position + 1] = 'X';
			}
			break;

		case 'A':position = A2.find('X');
			if (position != string::npos)
				if (last_random <= 9)
					A2.replace(position, 1, to_string(last_random));
				else
					A2.replace(position - 1, 2, to_string(last_random));

			if (!new_random)
				break;
			position = A2.find(to_string(new_random));
			if (position == string::npos)
				break;
			if (new_random <= 9)
				A2[position] = 'X';
			else
			{
				A2[position] = ' ';
				A2[position + 1] = 'X';
			}
			break;
		}
		last_random = new_random;
	}

	cout << top_wall << E6 << H5 << G4 << D3 << A2 << E1 << down_wall << endl;
	cout << "Podaj nute: ";
	cin >> answer;
	if (answer == "CHANGE")
	{
		zmiana++;
		if (zmiana % 2)
			E_lock = false;
		else
			E_lock = true;
	}
	cin.clear();
	cin.sync();
	return answer;
}

int Strings::Check_answer(string answer, int new_random, int size)
{

	if (answer == "HELP")
	{
		return 1;
	}
	else if (answer == "CHANGE")
	{
		return 2;
	}
	else if (answer == "EXIT")
	{
		exit(0);
	}
	if (answer == frets[new_random])
	{
		cout << "Dobrze! Lecimy dalej!";
		Sleep(1000);
		system("cls");

		points_gained++;
		how_many_points_left--;
		if (!how_many_points_left)
			how_many_points_left = 13;
		return 3;
	}
	else
	{
		cout << "Zla odpowiedz!";
		points_gained--;
		Sleep(1000);
		system("cls");
		return 4;
	}
}

void Strings::Help()
{
	system("cls");
	cout << "Progi na tej strunie po kolei: \n";
	for (int i = 0; i < 13; i++)
	{
		cout << i << ": " << frets[i] << endl;
	}
	cout << "Aby kontynuowac, kliknij cokolwiek\n";
	system("pause");
	system("cls");
}