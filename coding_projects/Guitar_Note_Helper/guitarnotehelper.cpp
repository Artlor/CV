#include <vector>
#include <time.h>
#include <iostream>
#include <Windows.h>

#include "strings.h"

using namespace std;

int main()
{
	srand(time(NULL));
	char which_string;
	string answer;
	int new_random;
	Strings *pointer = NULL;
	bool end_of_while = false;
	int when_to_end_switch;
	vector<int> my_vector;
	vector<int>::iterator it;
	int random_int;
	int drawn_number;

	for (int i = 0; i<13; i++)
	{
		my_vector.push_back(i);
	}

	while (true)
	{
		system("cls");
		delete pointer;
		pointer = NULL;
		cout << "Ktorej struny dzwiekow chcialbys sie nauczyc? (podaj duza litere z zakresu: E, A, D, G, H)\n";
		do
			cin >> which_string;
		while (which_string != 'E' && which_string != 'A' && which_string != 'D' && which_string != 'G' && which_string != 'H' && which_string != 'B');
		system("cls");
		pointer = new Strings(which_string);
		end_of_while = false;
		while (!end_of_while)
		{
			if (!my_vector.size() || answer == "CHANGE")
			{
				my_vector.clear();
				for (int i = 0; i<13; i++)
				{
					my_vector.push_back(i);
				}
			}
			random_int = rand() % my_vector.size();
			drawn_number = my_vector.at(random_int);
			new_random = drawn_number;
			my_vector.erase(my_vector.begin() + random_int);
			do
			{
				answer = pointer->Question(new_random, my_vector.size());
				switch (when_to_end_switch = pointer->Check_answer(answer, new_random, my_vector.size()))
				{
				case 1:			 pointer->Help();
					break;

				case 2:			 end_of_while = true;
					break;

				case 3:			 break;

				case 4:			 break;
				}
			} while (when_to_end_switch == 1 || when_to_end_switch == 4);
		}
	}
	return 0;
}

