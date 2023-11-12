#pragma once
#include "Board.h"
#include "Unit.h"
class Player
{
private:
	uint number_of_units;
	uint number_of_mines;
	Board player_board, enemy_board;
	std::vector<Unit> my_units;
	bool my_turn;
public:
	Player() : number_of_units(10), player_board(), enemy_board(), my_units(), number_of_mines(5), my_turn(false)
	{
		player_board.build_board();
		enemy_board.build_board();
		build_units();
	}
	std::vector<Unit>& get_my_units();
	const std::vector<Unit>& cget_my_units() const;
	void build_units();
	//void place_units();
	//void place_units(Player&, Player&);
	void place_mines_and_units(Player&, Player&);
	Player& get_player();
	bool is_my_turn();
	void set_my_turn();
	void set_not_my_turn();
	//void mine_board();
	void proceed();
	//const Unit& find_unit(Square) const;
};