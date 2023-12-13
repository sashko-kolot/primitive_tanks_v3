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
	uint number_of_units;
	uint number_of_mines;
	uint total_ammo;
	Board player_board, enemy_board;
	std::vector<Unit> my_units;
	bool my_turn;
public:
	Player() : player_name(), number_of_units(10), player_board(), enemy_board(), my_units(), number_of_mines(5), my_turn(false)
	{
		player_board.build_board();
		enemy_board.build_board();
		build_units();
		for (uint i = 0; i < my_units.size(); ++i)
		{
			total_ammo += my_units[i].cget_ammo();
		}
	}
	std::vector<Unit>& get_my_units();
	const std::vector<Unit>& cget_my_units() const;
	void build_units();
	void place_mines_and_units(Player&, Player&);
	const uint& cget_total_ammo() const;
	Player& get_player();
	Unit& find_unit_by_id();
	bool is_my_turn();
	void set_player_name();
	void set_my_turn();
	void set_not_my_turn();
	void proceed();
	void place_loot(Player&);
	static void action(Player&, Player&);
	void move_update(Player*, Player*, Unit*, uint, uint);
	void loot(Square&, Unit*);
	void remove_killed_enemy_unit(Player*, Player*, uint, uint);
	void report(Player*, Player*);
	void count_total_ammo();
	const std::string& cget_player_name() const;
	bool move(Player*, Player*, Unit*);
	bool is_passable(Player*, uint, uint);
	bool mine_on_path(Player*, Player*, uint, uint, Unit*);
	bool move_fwd(Player*, Player*, Unit*, int);
	bool move_bwd(Player*, Player*, Unit*, int);
	bool move_lft(Player*, Player*, Unit*, int);
	bool move_rgt(Player*, Player*, Unit*, int);
	bool move_fwd_rgt(Player*, Player*, Unit*, int, int);
	bool move_fwd_lft(Player*, Player*, Unit*, int, int);
	bool move_bwd_rgt(Player*, Player*, Unit*, int, int);
	bool move_bwd_lft(Player*, Player*, Unit*, int, int);
	bool shoot(Player*, Player*, Unit*);
	bool call_air_support(Player*, Player*, Unit*);
	bool reconnoiter(Player*, Unit*);
	static bool game_over(const Player&, const Player&);
};
#endif PLAYER_H