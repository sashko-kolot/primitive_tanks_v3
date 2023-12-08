#pragma once
#include "Board.h"
#include "Unit.h"
#include <random>
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
	void place_mines_and_units(Player&, Player&);
	Player& get_player();
	Unit& find_unit_by_id();
	bool is_my_turn();
	void set_my_turn();
	void set_not_my_turn();
	void proceed();
	void place_loot(Player&);
	void action(Player&, Player&);
	void move_update(Player*, Player*, Unit*, uint, uint);
	void loot(Square&, Unit*);
	bool move(Player*, Player*, Unit*);
	bool is_passable(Player*, uint, uint);
	bool mine_on_path(Player*, Player*, uint, uint, Unit*);
	bool move_fwd(Player*, Player*, Unit*, int);
	bool move_bwd(Player*, Player*, Unit*, int);
	bool move_lft(Player*, Player*, Unit*, int);
	bool move_rgt(Player*, Player*, Unit*, int);
};