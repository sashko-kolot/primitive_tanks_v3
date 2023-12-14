#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Unit.h"
#include <random>
#include <string>
class Player
{
private:
	std::string player_name;
	int number_of_units;
	int number_of_mines;
	int total_ammo;
	Board player_board, enemy_board;
	std::vector<Unit> my_units;
	bool my_turn;
public:
	Player() : player_name(), number_of_units(10), player_board(), enemy_board(), my_units(), number_of_mines(5), my_turn(false)
	{
		player_board.build_board();
		enemy_board.build_board();
		build_units();
		for (int i = 0; i < my_units.size(); ++i)
		{
			total_ammo += my_units[i].cget_ammo();
		}
	}
	std::vector<Unit>& get_my_units();
	const std::vector<Unit>& cget_my_units() const;
	Board& get_player_board();
	const Board& cget_player_board() const;
	Board& get_enemy_board();
	const Board& cget_enemy_board() const;
	const int& cget_number_of_mines() const;
	const int& cget_number_of_units() const;
	void build_units();
	const int& cget_total_ammo() const;
	Player& get_player();
	Unit& find_unit_by_id();
	bool is_my_turn();
	void set_player_name();
	void set_my_turn();
	void set_not_my_turn();
	void count_total_ammo();
	void erase_unit(Unit*);
	const std::string& cget_player_name() const;
};
#endif PLAYER_H