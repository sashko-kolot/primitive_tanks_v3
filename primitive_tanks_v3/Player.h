#pragma once
#include "Board.h"
#include "Unit.h"
class Player
{
private:
	uint number_of_units;
	Board player_board, enemy_board;
	std::vector<Unit> my_units;
public:
	Player() : number_of_units(10), player_board(), enemy_board(), my_units() {}
	std::vector<Unit>& get_my_units();
	void build_units();
};