#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "Player.h"
void place_mines_and_units(Player&, Player&);
void place_loot(Board&);
void action(Player& player1, Player& player2);;
bool move(Player*, Player*, Unit*);
bool move_fwd(Player*, Player*, Unit*, int);
bool move_bwd(Player*, Player*, Unit*, int);
bool move_lft(Player*, Player*, Unit*, int);
bool move_rgt(Player*, Player*, Unit*, int);
bool move_fwd_rgt(Player*, Player*, Unit*, int, int);
bool move_fwd_lft(Player*, Player*, Unit*, int, int);
bool move_bwd_rgt(Player*, Player*, Unit*, int, int);
bool move_bwd_lft(Player*, Player*, Unit*, int, int);
bool is_passable(Player*, int, int);
bool mine_on_path(Player*, Player*, int, int, Unit*);
void loot(Square&, Unit*);
void move_update(Player*, Player*, Unit*, Square&, int, int);
bool shoot(Player*, Player*, Unit*);
bool call_air_support(Player*, Player*, Unit*);
void reconnoiter(Player*, Unit*);
void remove_killed_unit(Player*, Player*, int, int);
void report(Player*, Player*);
bool game_over(const Player&, const Player&);
void proceed();
#endif GAMEPLAY_H

