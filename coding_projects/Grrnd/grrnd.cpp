#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <time.h>     
#include <algorithm>

int main()
{
	srand(time(NULL));
	uint_fast16_t Total_experience_p1 = 0, Total_experience_p2 = 0, Experience_to_next_level_p1 = 5, Experience_to_next_level_p2 = 5, Level_p1 = 1, Level_p2 = 1;
	bool was_bullet_shot_p1 = false, was_bullet_shot_p2 = false;
	std::pair<uint_fast8_t, uint_fast8_t> bullet_position_p1, bullet_position_p2;
	enum class bullet_directions {LEFT, RIGHT, UP, DOWN, W, A, S ,D};
	bullet_directions bullet_direction_p1, bullet_direction_p2, bullet_temporary_direction_p1 = bullet_directions::UP, bullet_temporary_direction_p2 = bullet_directions::UP;
	uint_fast8_t bullet_time_counter = 0;
	bool bullet_direction_set_p1 = false, bullet_direction_set_p2 = false;
	
	bool player2_stop = false, player1_stop = false;
	uint_fast8_t player2_stop_counter = 0, player1_stop_counter = 0;

	enum Arena_size{HEIGHT = 8, WIDTH = 16};
	char arena[Arena_size::HEIGHT][Arena_size::WIDTH];

	enum class directions{LEFT, RIGHT, UP, DOWN, ESCAPE, W, A, S, D, NOTHING};
	directions Direction_p1 = directions::NOTHING;
	directions Direction_p2 = directions::NOTHING;

	std::pair<int_fast8_t, int_fast8_t> Pair_p1{Arena_size::HEIGHT/2,Arena_size::WIDTH/2};
	std::pair<int_fast8_t, int_fast8_t> Pair_p2{ Arena_size::HEIGHT / 2,(Arena_size::WIDTH / 2 )-1};

	std::vector<std::pair<uint_fast8_t,uint_fast8_t>> Places_player_went_through; //NEEDED TO KNOW WHERE NOT TO PLACE '.'

	std::pair<int_fast8_t, int_fast8_t> random_place; //RANDOM PLACE TO BE FILLED WITH NEW '.'

	bool random_place_bool = false;

	uint_fast8_t how_many_points_are_left = 0;

	while (Direction_p1 != directions::ESCAPE && Direction_p2!=directions::ESCAPE)
	{

		//MAP RESET

		system("CLS");

		if ((rand() % 2) <=1)
		{
			random_place_bool = true;
			random_place = { rand() % Arena_size::HEIGHT, rand() % Arena_size::WIDTH }; //GENERATING WHERE TO PLACE '.' WITHIN ARENA
		}
		else
			random_place_bool = false;
													//RENDERING ARENA
		for (int i = 0; i < Arena_size::HEIGHT; i++)
		{
			for (int j = 0; j < Arena_size::WIDTH; j++)
			{

				if (i == 0 || j == 0 || i == Arena_size::HEIGHT - 1 || j == Arena_size::WIDTH - 1)
					arena[i][j] = 'X';
				else
					arena[i][j] = '.';

				for (int k = 0; k < Places_player_went_through.size(); k++)
				{
					
					if (i == Places_player_went_through[k].first && j == Places_player_went_through[k].second)
					{
						arena[i][j] = ' ';
						break;
					}
				}

				if (random_place_bool) //PLACING NEW '.' AND REMOVING THIS POSITION FROM PLACES_PLAYER_WENT_THROUGH TO AVOID DELETING '.' IMMEDIATELY IN THE NEXT RENDER
				{
					arena[random_place.first][random_place.second] = '.';
					random_place_bool = false;
					for (int i = 0; i < Places_player_went_through.size(); i++)
					{
						if (Places_player_went_through[i].first == random_place.first && Places_player_went_through[i].second == random_place.second)
						{
							Places_player_went_through.erase(Places_player_went_through.begin() + i);
							break;
						}
					}
					
				}

				if (i == Pair_p1.first && j == Pair_p1.second)
					arena[i][j] = 'P';

				if (i == Pair_p2.first && j == Pair_p2.second)
					arena[i][j] = 'L';

				if (was_bullet_shot_p1)
				{
					arena[bullet_position_p1.first][bullet_position_p1.second] = 'o';
					if (bullet_position_p1.first == Pair_p2.first && bullet_position_p1.second == Pair_p2.second)
					{
						was_bullet_shot_p1 = false;
						player2_stop = true;

					}
				}
				if (was_bullet_shot_p2)
				{
					arena[bullet_position_p2.first][bullet_position_p2.second] = '*';
					if (bullet_position_p2.first == Pair_p1.first && bullet_position_p2.second == Pair_p1.second)
					{
						was_bullet_shot_p2 = false;
						player1_stop = true;

					}
				}

			}

		}

		for (int i = 0; i < Arena_size::HEIGHT; i++)
		{
			for (int j = 0; j < Arena_size::WIDTH; j++)
			{
				if (arena[i][j] == '.')
				{
					how_many_points_are_left++;
				}
				else
					continue;
			}
		}

		if (how_many_points_are_left <= 0)
		{
			break;
		}
		else
			how_many_points_are_left = 0;

		if (!player1_stop)
		{
			if (GetAsyncKeyState(VK_LEFT))
				Direction_p1 = directions::LEFT;
			else if (GetAsyncKeyState(VK_RIGHT))
				Direction_p1 = directions::RIGHT;
			else if (GetAsyncKeyState(VK_UP))
				Direction_p1 = directions::UP;
			else if (GetAsyncKeyState(VK_DOWN))
				Direction_p1 = directions::DOWN;

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (!was_bullet_shot_p1 && Total_experience_p1 >=2) //IF IT'S FALSE, MEANS HE DIDN'T SHOOT BEFORE
				{
					if (Total_experience_p1 >= 2)
						Total_experience_p1 -= 2;
					else
						Total_experience_p1 = 0;
					was_bullet_shot_p1 = true;
					bullet_direction_p1 = bullet_temporary_direction_p1;
					switch (bullet_direction_p1)
					{
					case bullet_directions::LEFT:
					{
						bullet_position_p1 = std::make_pair(Pair_p1.first, Pair_p1.second - 1);
						break;
					}
					case bullet_directions::RIGHT:
					{
						bullet_position_p1 = std::make_pair(Pair_p1.first, Pair_p1.second + 1);
						break;
					}
					case bullet_directions::UP:
					{
						bullet_position_p1 = std::make_pair(Pair_p1.first - 1, Pair_p1.second);
						break;
					}
					case bullet_directions::DOWN:
					{
						bullet_position_p1 = std::make_pair(Pair_p1.first + 1, Pair_p1.second);
						break;
					}
					}
				}
			}
		}
		else
		{
			player1_stop_counter++;
			if (player1_stop_counter % 20 == 0)
			{
				player1_stop = false;
				player1_stop_counter = 0;
			}
		}

		if (was_bullet_shot_p1) //STILL FLYING
		{
				switch (bullet_direction_p1)
				{
				case bullet_directions::LEFT:
				{
					bullet_position_p1 = std::make_pair(bullet_position_p1.first, bullet_position_p1.second - 1);
					break;
				}
				case bullet_directions::RIGHT:
				{
					bullet_position_p1 = std::make_pair(bullet_position_p1.first, bullet_position_p1.second + 1);
					break;
				}
				case bullet_directions::UP:
				{
					bullet_position_p1 = std::make_pair(bullet_position_p1.first - 1, bullet_position_p1.second);
					break;
				}
				case bullet_directions::DOWN:
				{
					bullet_position_p1 = std::make_pair(bullet_position_p1.first + 1, bullet_position_p1.second);
					break;
				}
				}

				if (bullet_position_p1.first <= 0)
				{
					was_bullet_shot_p1 = false;
					bullet_direction_set_p1 = false;
				}
				else if (bullet_position_p1.first >= (Arena_size::HEIGHT - 1))
				{
					was_bullet_shot_p1 = false;
					bullet_direction_set_p1 = false;
				}

				if (bullet_position_p1.second <= 0)
				{
					was_bullet_shot_p1 = false;
					bullet_direction_set_p1 = false;
				}
				else if (bullet_position_p1.second >= (Arena_size::WIDTH - 1))
				{
					was_bullet_shot_p1 = false;
					bullet_direction_set_p1 = false;
				}
		}


		if (!player2_stop)
		{
			if (GetAsyncKeyState(0x57))
				Direction_p2 = directions::W;
			else if (GetAsyncKeyState(0x41))
				Direction_p2 = directions::A;
			else if (GetAsyncKeyState(0x53))
				Direction_p2 = directions::S;
			else if (GetAsyncKeyState(0x44))
				Direction_p2 = directions::D;

			if (GetAsyncKeyState(VK_MENU))
			{
				if (!was_bullet_shot_p2 && Total_experience_p2>=2) //IF IT'S FALSE, MEANS HE DIDN'T SHOOT BEFORE
				{
					if (Total_experience_p2 >= 2)
						Total_experience_p2 -= 2;
					else
						Total_experience_p2 = 0;
					was_bullet_shot_p2 = true;
					bullet_direction_p2 = bullet_temporary_direction_p2;
					switch (bullet_direction_p2)
					{
					case bullet_directions::LEFT:
					{
						bullet_position_p2 = std::make_pair(Pair_p2.first, Pair_p2.second - 1);
						break;
					}
					case bullet_directions::RIGHT:
					{
						bullet_position_p2 = std::make_pair(Pair_p2.first, Pair_p2.second + 1);
						break;
					}
					case bullet_directions::UP:
					{
						bullet_position_p2 = std::make_pair(Pair_p2.first - 1, Pair_p2.second);
						break;
					}
					case bullet_directions::DOWN:
					{
						bullet_position_p2 = std::make_pair(Pair_p2.first + 1, Pair_p2.second);
						break;
					}
					}
				}
			}
		}
		else
		{
			player2_stop_counter++;
			if (player2_stop_counter % 20 == 0)
			{
				player2_stop = false;
				player2_stop_counter = 0;
			}
		}

		if (was_bullet_shot_p2) //STILL FLYING
		{
			switch (bullet_direction_p2)
			{
			case bullet_directions::LEFT:
			{
				bullet_position_p2 = std::make_pair(bullet_position_p2.first, bullet_position_p2.second - 1);
				break;
			}
			case bullet_directions::RIGHT:
			{
				bullet_position_p2 = std::make_pair(bullet_position_p2.first, bullet_position_p2.second + 1);
				break;
			}
			case bullet_directions::UP:
			{
				bullet_position_p2 = std::make_pair(bullet_position_p2.first - 1, bullet_position_p2.second);
				break;
			}
			case bullet_directions::DOWN:
			{
				bullet_position_p2 = std::make_pair(bullet_position_p2.first + 1, bullet_position_p2.second);
				break;
			}
			}

			if (bullet_position_p2.first <= 0)
			{
				was_bullet_shot_p2 = false;
				bullet_direction_set_p2 = false;
			}
			else if (bullet_position_p2.first >= (Arena_size::HEIGHT - 1))
			{
				was_bullet_shot_p2 = false;
				bullet_direction_set_p2 = false;
			}

			if (bullet_position_p2.second <= 0)
			{
				was_bullet_shot_p2 = false;
				bullet_direction_set_p2 = false;
			}
			else if (bullet_position_p2.second >= (Arena_size::WIDTH - 1))
			{
				was_bullet_shot_p2 = false;
				bullet_direction_set_p2 = false;
			}
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			Direction_p1 = directions::ESCAPE;
			Direction_p2 = directions::ESCAPE;
		}
		else;

		switch (Direction_p1)
		{
		case directions::LEFT:
			Pair_p1.second--;
			bullet_temporary_direction_p1 = bullet_directions::LEFT;

			if (!bullet_direction_set_p1 && !was_bullet_shot_p1)
			{
				bullet_direction_p1 = bullet_directions::LEFT;
				bullet_direction_set_p1 = true;
			}
			break;
		case directions::RIGHT:
			Pair_p1.second++;
			bullet_temporary_direction_p1 = bullet_directions::RIGHT;
			if (!bullet_direction_set_p1 && !was_bullet_shot_p1)
			{
				bullet_direction_p1 = bullet_directions::RIGHT;
				bullet_direction_set_p1 = true;
			}
			break;
		case directions::UP:
			Pair_p1.first--;
			bullet_temporary_direction_p1 = bullet_directions::UP;
			if (!bullet_direction_set_p1 && !was_bullet_shot_p1)
			{
				bullet_direction_p1 = bullet_directions::UP;
				bullet_direction_set_p1 = true;
			}
			break;
		case directions::DOWN:
			Pair_p1.first++;
			bullet_temporary_direction_p1 = bullet_directions::DOWN;
			if (!bullet_direction_set_p1 && !was_bullet_shot_p1)
			{
				bullet_direction_p1 = bullet_directions::DOWN;
				bullet_direction_set_p1 = true;
			}
			break;
		default: break;
		}


		switch(Direction_p2)
		{
		case directions::W:
			Pair_p2.first--;
			bullet_temporary_direction_p2 = bullet_directions::UP;

			if (!bullet_direction_set_p2 && !was_bullet_shot_p2)
			{
				bullet_direction_p2 = bullet_directions::UP;
				bullet_direction_set_p2 = true;
			}
			break;
		case directions::A:
			Pair_p2.second--;
			bullet_temporary_direction_p2 = bullet_directions::LEFT;

			if (!bullet_direction_set_p2 && !was_bullet_shot_p2)
			{
				bullet_direction_p2 = bullet_directions::LEFT;
				bullet_direction_set_p2 = true;
			}
			break;
		case directions::S:
			Pair_p2.first++;
			bullet_temporary_direction_p2 = bullet_directions::DOWN;

			if (!bullet_direction_set_p2 && !was_bullet_shot_p2)
			{
				bullet_direction_p2 = bullet_directions::DOWN;
				bullet_direction_set_p2 = true;
			}
			break;
		case directions::D:
			Pair_p2.second++;
			bullet_temporary_direction_p2 = bullet_directions::RIGHT;

			if (!bullet_direction_set_p2 && !was_bullet_shot_p2)
			{
				bullet_direction_p2 = bullet_directions::RIGHT;
				bullet_direction_set_p2 = true;
			}
			break;
		default: break;
		}

		Direction_p1 = directions::NOTHING;
		Direction_p2 = directions::NOTHING;

							//NECESSARY TO AVOID FALLING OUT OF ARENA
		if (Pair_p1.first <= 0)
			Pair_p1.first = 1;
		else if (Pair_p1.first >= (Arena_size::HEIGHT-1))
			Pair_p1.first = Arena_size::HEIGHT - 2;

		if (Pair_p1.second <= 0)
			Pair_p1.second = 1;
		else if (Pair_p1.second >= (Arena_size::WIDTH-1))
			Pair_p1.second = Arena_size::WIDTH - 2;

		if (Pair_p2.first <= 0)
			Pair_p2.first = 1;
		else if (Pair_p2.first >= (Arena_size::HEIGHT - 1))
			Pair_p2.first = Arena_size::HEIGHT - 2;

		if (Pair_p2.second <= 0)
			Pair_p2.second = 1;
		else if (Pair_p2.second >= (Arena_size::WIDTH - 1))
			Pair_p2.second = Arena_size::WIDTH - 2;

													//GAINING EXPERIENCE MECHANIC
		if (arena[Pair_p1.first][Pair_p1.second] == '.')
		{
			bool Is_repeated_flag = false;
			for (int i = 0; i < Places_player_went_through.size(); i++)
			{
				if (Places_player_went_through[i].first == Pair_p1.first && Places_player_went_through[i].second == Pair_p1.second)
					Is_repeated_flag = true;
				else
					continue;
			}
			if(!Is_repeated_flag)
				Places_player_went_through.push_back(std::make_pair(Pair_p1.first, Pair_p1.second));

			Total_experience_p1++;
			Experience_to_next_level_p1--;
			if (Experience_to_next_level_p1 <= 0)
			{
				Experience_to_next_level_p1 = Total_experience_p1 + (Total_experience_p1*1/10);
				Level_p1++;
			}
		}

		if (arena[Pair_p2.first][Pair_p2.second] == '.')
		{
			bool Is_repeated_flag = false;
			for (int i = 0; i < Places_player_went_through.size(); i++)
			{
				if (Places_player_went_through[i].first == Pair_p2.first && Places_player_went_through[i].second == Pair_p2.second)
					Is_repeated_flag = true;
				else
					continue;
			}
			if (!Is_repeated_flag)
				Places_player_went_through.push_back(std::make_pair(Pair_p2.first, Pair_p2.second));

			Total_experience_p2++;
			Experience_to_next_level_p2--;
			if (Experience_to_next_level_p2 <= 0)
			{
				Experience_to_next_level_p2 = Total_experience_p2 + (Total_experience_p2 * 1 / 10);
				Level_p2++;
			}
		}

													//DRAWING ARENA WITH PLAYER
		for (int i = 0; i < Arena_size::HEIGHT; i++)
		{
			std::cout << "\t\t\t";
			for (int j = 0; j < Arena_size::WIDTH; j++)
			{
				std::cout << arena[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << "'P' Level: " << Level_p1 << "\t\t\t\t" << "'L' level: " << Level_p2 << "\n" 
			<< "Experience needed to get level " << Level_p1 + 1 << ": " << Experience_to_next_level_p1 << "\t" << "Experience needed to get level " << Level_p2 + 1 << ": " << Experience_to_next_level_p2 << "\n"
			<< "Total experience: " << Total_experience_p1 << "\t\t\t" << "Total experience: " << Total_experience_p2;
	
		Sleep(100);

	}
	std::string winner;
	if (Total_experience_p1 > Total_experience_p2)
		winner = 'P';
	else if (Total_experience_p1 < Total_experience_p2)
		winner = 'L';
	else if (Total_experience_p1 == Total_experience_p2)
		winner = "BOTH OF YOU!";

	std::cout << "\n\n\n\n";
	std::cout << "\t\tEND OF GAME!\n Player: " << winner << " is the winner!" << "\nP: " << Total_experience_p1 << "\nL: " << Total_experience_p2;
	std::cout << "\n\n\n\n";
	getchar(); getchar();
}
