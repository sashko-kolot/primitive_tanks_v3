#include "Player.h"
//get units
std::vector<Unit>& Player::get_my_units()
{
	return my_units;
}
const std::vector<Unit>& Player::cget_my_units() const
{
	return my_units;
}
//build units
void Player::build_units()
{
	for (int i = 0; i < number_of_units; ++i)
	{
		Unit unit;
		unit.set_unit_id(i + 1);
		get_my_units().push_back(unit);
	}
}
//get player
Player& Player::get_player()
{
	return *this;
}
//get unit by its id
Unit& Player::find_unit_by_id()
{
	Unit* unit = nullptr;
	int id = 0;
	bool is_unit = false;
	do
	{ 
	std::cout << "Select a unit by entering its id: ";
	std::cin >> id;
	for (int i = 0; i < my_units.size(); ++i)
	{
		if (id == my_units[i].cget_unit_id())
		{
			unit = &my_units[i].get_unit();
			is_unit = true;
		}
	}
	} while (!is_unit);
	return unit->get_unit();
}
//get total ammo
const int& Player::cget_total_ammo() const
{
	return total_ammo;
}
//get turn
bool Player::is_my_turn()
{
	return my_turn;
}
//set turn
void Player::set_my_turn()
{
	my_turn = true;
}
void Player::set_not_my_turn()
{
	my_turn = false;
}
void Player::count_total_ammo()
	{
		for (int i = 0; i < my_units.size(); ++i)
		{
			total_ammo = 0;
			total_ammo += my_units[i].cget_ammo();
		}
	}
	void Player::set_player_name()
	{
		char choice = ' ';
		do
		{ 
		std::cout << "Enter player name: ";
		std::cin >> player_name;
		std::cout << "Press 'y' to confirm or any other key to enter a different name." << std::endl;
		} while (choice != 'y');
	}
	const std::string& Player::cget_player_name() const
	{
		return player_name;
	}
	Board& Player::get_player_board()
	{
		return player_board;
	}
	const Board& Player::cget_player_board() const
	{
		return player_board;
	}
	Board& Player::get_enemy_board()
	{
		return enemy_board;
	}
	const Board& Player::cget_enemy_board() const
	{
		return enemy_board;
	}
	const int& Player::cget_number_of_mines() const
	{
		return number_of_mines;
	}
	const int& Player::cget_number_of_units() const
	{
		return number_of_units;
	}
	void Player::erase_unit(Unit* unit)
	{
		std::vector<Unit>::iterator it;
		int pos;
		for (pos = 0; pos < my_units.size(); ++pos)
		{
			if (my_units[pos].cget_unit_id() == unit->cget_unit_id())
				it = my_units.begin() + pos;
				break;
		}
		my_units.erase(it);
	}