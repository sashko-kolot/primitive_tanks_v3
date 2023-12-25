#include <random>
#include <ctime>
#include "gameplay.h"
void place_mines_and_units(Player& player1, Player& player2)
{
	Player* me = nullptr;
	Player* opponent = nullptr;
	if (player1.get_player().is_my_turn())
	{
		me = &player1.get_player();
		opponent = &player2.get_player();
	}
	else
	{
		me = &player2.get_player();
		opponent = &player1.get_player();
	}
	std::cout << "Commander " << me->cget_player_name() << ", it's your turn." << std::endl;
	proceed();
	Square* square = nullptr;
	//intro text
	std::cout << "Commander, we have some time before the battle starts. Use it wisely. Our engineers have prepared some surprises for the enemy and are waiting for your orders. Mining is as important as shooting and maneuvering. Think carefully where to plant our mines." << std::endl;
	proceed();
	for (int i = 0; i < me->cget_number_of_mines(); ++i)
	{
		me->cget_enemy_board().display_board();
		do
		{
			square = &me->get_enemy_board().get_pos();
			if (square->is_mine())
				std::cout << "We have mined this square already, commander." << std::endl;
		} while (square->is_mine());
		square->set_mine();
		if (opponent->get_player_board().find_square(square->cget_x_pos(), square->cget_y_pos()).is_unit())
		{
			opponent->get_player_board().find_square(square->cget_x_pos(), square->cget_y_pos()).hide_square();
		}
		square->unhide_square();
		opponent->get_player_board().find_square(square->cget_x_pos(), square->cget_y_pos()).set_mine();
		system("cls");
	}
	std::cout << "Mining complete, commander." << std::endl;
	proceed();
	system("cls");
	std::cout << "Now it's time to demonstrate your tactical genious, commander. Order your units to take their combat positions." << std::endl;
	proceed();
	for (int i = 0; i < me->cget_number_of_units(); ++i)
	{
		me->get_player_board().display_board();
		do
		{
			square = &me->get_player_board().get_pos();
		} while (!me->get_player_board().is_accessible(*square));
		me->get_my_units()[i].get_x_pos() = square->cget_x_pos();
		me->get_my_units()[i].get_y_pos() = square->cget_y_pos();
		square->set_unit();
		square->unhide_square();
		square->assign_unit_id(me->get_my_units()[i].cget_unit().cget_unit_id());
		opponent->get_enemy_board().find_square(square->cget_x_pos(), square->cget_y_pos()).set_unit();
		opponent->get_enemy_board().find_square(square->cget_x_pos(), square->cget_y_pos()).assign_unit_id(me->get_my_units()[i].cget_unit().cget_unit_id());
		if (square->is_mine())
		{
			square->hide_square();
		}
		me->get_player_board().locker(*square);
		system("cls");
	}
	std::cout << "All your units are in their combat positions, commander." << std::endl;
	proceed();
	me->set_not_my_turn();
	opponent->set_my_turn();
	system("cls");
}
void place_loot(Board& player_board)
{
	for (int i = 1; i <= 6; ++i)
	{
		int sq = 0;
		do
		{
			std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
			std::uniform_int_distribution<int> distribution(0, player_board.get_board().size() - 1);
			sq = distribution(rng);
		} while (player_board.get_board()[sq].cget_square().is_unit() || player_board.cget_board()[sq].cget_square().is_mine() || player_board.cget_board()[sq].cget_square().is_loot());
		if (i == 1)
		{
			player_board.get_board()[sq].get_square().set_repair_kit();
		}
		if (i == 2)
		{
			player_board.get_board()[sq].get_square().set_mask_kit();
		}
		if (i == 3)
		{
			player_board.get_board()[sq].get_square().set_recon_kit();
		}
		if (i == 4)
		{
			player_board.get_board()[sq].get_square().set_air_support();
		}
		if (i == 5)
		{
			player_board.get_board()[sq].get_square().set_mine_clearing();
		}
		if (i == 6)
		{
			player_board.get_board()[sq].get_square().set_extra_ammo();
		}
	}
}
void action(Player& player1, Player& player2)
{
	Player* me = nullptr;
	Player* opponent = nullptr;
	if(player1.get_player().is_my_turn())
	{
		me = &player1.get_player();
		opponent = &player2.get_player();
	}
	else
	{
		me = &player2.get_player();
		opponent = &player1.get_player();
	}
	std::cout << "Commander " << me->cget_player_name() << ", it's your turn." << std::endl;
	proceed();
	report(me, opponent);
	std::cout << "\nPlayer board" << std::endl;
	me->cget_player_board().display_board();
	std::cout << "\nEnemy board" << std::endl;
	me->cget_enemy_board().display_board();
	Unit* cur_unit = nullptr;
	bool action_completed = false;
	do
	{
		cur_unit = &me->find_unit_by_id();
		if (me->get_player_board().find_square(cur_unit->cget_x_pos(), cur_unit->cget_y_pos()).is_mine())
		{
			remove_killed_unit(opponent, me, cur_unit->cget_x_pos(),cur_unit->cget_y_pos());
			opponent->get_enemy_board().find_square(cur_unit->cget_x_pos(), cur_unit->cget_y_pos()).remove_mine();
			std::cout << "Your unit was destroyed by a mine, commander." << std::endl;
			proceed();
			break;
		}
		//proceed();
		char action = ' ';
		std::cout << "Press 'm' to move, 's' to shoot, or 'a' to call air support: ";
		std::cin >> action;
		switch (action)
		{
		case 'm':
			if(move(me, opponent, cur_unit))
			{
				action_completed = true;
			}
			break;
		case 's':
			if(shoot(me, opponent, cur_unit))
			{
				action_completed = true;
			}
			break;
		case 'a':
			if(call_air_support(me, opponent, cur_unit))
			{
				action_completed = true;
			}
			break;
		default:
			std::cout << "Invalid action." << std::endl;
		}
	} while (!action_completed);
	system("cls");
	me->count_total_ammo();
	opponent->count_total_ammo();
	std::cout << "Player board" << std::endl;
	me->cget_player_board().display_board();
	std::cout << "\nEnemy board" << std::endl;
	me->cget_enemy_board().display_board();
	std::cout << "End of turn." << std::endl;
	proceed();
	system("cls");
	me->set_not_my_turn();
	opponent->set_my_turn();
}
bool move(Player* player1, Player* player2, Unit* unit)
{
	Square* target_square = nullptr;
	int xdif = 0, ydif = 0, xydif = 0;
	target_square = &player1->get_player_board().get_pos();
	//check the distance to the target square
	xdif = target_square->cget_x_pos() - unit->cget_x_pos();
	ydif = target_square->cget_y_pos() - unit->cget_y_pos();
	xydif = abs(xdif) + abs(ydif);
	if (xydif > 3)
	{
		std::cout << "You cannot move there, commander." << std::endl;
		proceed();
		return false;
	}
	player1->get_player_board().unlocker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
	if (!player1->get_player_board().is_accessible(target_square->get_square()))
	{
		player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
		return false;
	}
	//move fwd
	if (xdif == 0 && ydif > 0)
	{
		if (move_fwd(player1, player2, unit, ydif))
			return true;
		else
			player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			return false;
	}
	//move bwd
	if (xdif == 0 && ydif < 0)
	{
		if (move_bwd(player1, player2, unit, ydif))
			return true;
		else
			player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			return false;
	}
	//move left
	if (ydif == 0 && xdif < 0)
	{
		if (move_lft(player1, player2, unit, xdif))
			return true;
		else
			player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			return false;
	}
	//move right
	if (ydif == 0 && xdif > 0)
	{
		if (move_rgt(player1, player2, unit, xdif))
			return true;
		else
			return false;
	}
	//move fwd & right or right & fwd
	if (xdif > 0 && ydif > 0)
	{
		for (int i = 0; i < ydif; ++i)
		{
			if (move_fwd_rgt(player1, player2, unit, xdif, ydif))
				return true;
			else
				player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
				return false;
		}
	}
	//move fwd & left or left & fwd
	if (xdif < 0 && ydif > 0)
	{
		if (move_fwd_lft(player1, player2, unit, xdif, ydif))
			return true;
		else
			player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			return false;
	}
	//move bwd & right or right & bwd
	if (xdif > 0 && ydif < 0)
	{
		if (move_bwd_rgt(player1, player2, unit, xdif, ydif))
			return true;
		else
			player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			return false;
	}
	//move bwd & left or left & bwd
	if (xdif < 0 && ydif < 0)
	{
		if (move_bwd_lft(player1, player2, unit, xdif, ydif))
		
			return true;
		else
			player1->get_player_board().locker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			return false;
	}
	player1->get_player_board().unlocker(player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
	return false;
}
bool move_fwd(Player* player1, Player* player2, Unit* unit, int ydif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (!is_passable(player1, x, y))
		{
			return false;
		}
	}
	x = 0, y = 0;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool move_bwd(Player* player1, Player* player2, Unit* unit, int ydif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square,x, y);
	return true;
}
bool move_lft(Player* player1, Player* player2, Unit* unit, int xdif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y;
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		y = unit->cget_y_pos();
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		y = unit->cget_y_pos();
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool move_rgt(Player* player1, Player* player2, Unit* unit, int xdif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y;
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		y = unit->cget_y_pos();
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		y = unit->cget_y_pos();
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool move_fwd_rgt(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y, y_offset = 0;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (!is_passable(player1, x, y) || (is_passable(player1, x, y) && !is_passable(player1, x + 1, y) && ydif == 1))
		{
			for (int i = 1; i <= xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				y = unit->cget_y_pos();
				if (!is_passable(player1, x, y))
					return false;
			}
			for (int i = 1; i <= ydif; ++i)
			{
				y = unit->cget_y_pos() + i;
				if (!is_passable(player1, x, y))
					return false;
			}
			x = 0, y = 0;
			for (int i = 1; i <= xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				y = unit->cget_y_pos();
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			for (int i = 1; i <= ydif; ++i)
			{
				y = unit->cget_y_pos() + i;
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			move_update(player1, player2, unit, prev_square, x, y);
			return true;
		}
		y_offset = i;
	}
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		y = unit->cget_y_pos() + y_offset;
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool move_fwd_lft(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y, y_offset = 0;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (!is_passable(player1, x, y) || (is_passable(player1, x, y) && !is_passable(player1, x - 1, y) && ydif == 1))
		{
			for (int i = 1; i <= abs(xdif); ++i)
			{
				x = unit->cget_x_pos() - i;
				y = unit->cget_y_pos();
				if (!is_passable(player1, x, y))
					return false;
			}
			for (int i = 1; i <= ydif; ++i)
			{
				y = unit->cget_y_pos() + i;
				if (!is_passable(player1, x, y))
					return false;
			}
			x = 0, y = 0;
			for (int i = 1; i <= abs(xdif); ++i)
			{
				x = unit->cget_x_pos() - i;
				y = unit->cget_y_pos();
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			for (int i = 1; i <= ydif; ++i)
			{
				y = unit->cget_y_pos() + i;
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			move_update(player1, player2, unit, prev_square, x, y);
			return true;
		}
		y_offset = i;
	}
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		y = unit->cget_y_pos() + y_offset;
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool move_bwd_rgt(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y, y_offset = 0;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (!is_passable(player1, x, y) || (is_passable(player1, x, y) && !is_passable(player1, x + 1, y) && ydif == - 1))
		{
			for (int i = 1; i <= xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				y = unit->cget_y_pos();
				if (!is_passable(player1, x, y))
					return false;
			}
			for (int i = 1; i <= abs(ydif); ++i)
			{
				y = unit->cget_y_pos() - i;
				if (!is_passable(player1, x, y))
					return false;
			}
			x = 0, y = 0;
			for (int i = 1; i <= xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				y = unit->cget_y_pos();
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			for (int i = 1; i <= abs(ydif); ++i)
			{
				y = unit->cget_y_pos() - i;
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			move_update(player1, player2, unit, prev_square, x, y);
			return true;
		}
		y_offset = i;
	}
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		y = unit->cget_y_pos() - y_offset;
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool move_bwd_lft(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
{
	Square& prev_square = player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos());
	int x, y, y_offset = 0;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (!is_passable(player1, x, y) || (is_passable(player1, x, y) && !is_passable(player1, x - 1, y) && ydif == - 1))
		{
			for (int i = 1; i <= abs(xdif); ++i)
			{
				x = unit->cget_x_pos() - i;
				y = unit->cget_y_pos();
				if (!is_passable(player1, x, y))
					return false;
			}
			x = 0, y = 0;
			for (int i = 1; i <= abs(ydif); ++i)
			{
				y = unit->cget_y_pos() - i;
				if (!is_passable(player1, x, y))
					return false;
			}
			x = 0, y = 0;
			for (int i = 1; i <= abs(xdif); ++i)
			{
				x = unit->cget_x_pos() - i;
				y = unit->cget_y_pos();
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			for (int i = 1; i <= abs(ydif); ++i)
			{
				y = unit->cget_y_pos() - i;
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->get_player_board().find_square(x, y), unit);
			}
			move_update(player1, player2, unit, prev_square, x, y);
			return true;
		}
		y_offset = i;
	}
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		y = unit->cget_y_pos() - y_offset;
		if (!is_passable(player1, x, y))
			return false;
	}
	x = 0, y = 0;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		if (mine_on_path(player1, player2, x, y, unit))
			return true;
		else
			loot(player1->get_player_board().find_square(x, y), unit);
	}
	move_update(player1, player2, unit, prev_square, x, y);
	return true;
}
bool is_passable(Player* player1, int x, int y)
{
	if (player1->get_player_board().find_square(x, y).is_locked() || player1->get_player_board().find_square(x, y).is_hit()
		|| player1->get_player_board().find_square(x, y).is_kill())
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool mine_on_path(Player* player1, Player* player2, int x, int y, Unit* unit)
{
	if (player1->get_player_board().find_square(x, y).is_mine() && !unit->is_mine_clearing() && !unit->is_repair_kit())
	{
		player1->get_player_board().find_square(x, y).set_kill();
		player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()).remove_unit();
		player2->get_enemy_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()).remove_unit();
		if (unit->is_recon_kit())
		{
			player1->get_enemy_board().recon_hide(player1->get_enemy_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
		}
		if (unit->is_mask_kit())
		{
			player2->get_enemy_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()).remove_no_recon();
		}
		player1->erase_unit(unit);
		player1->get_player_board().find_square(x, y).set_kill();
		player1->get_player_board().find_square(x, y).remove_mine();
		player2->get_enemy_board().find_square(x, y).set_kill();
		player2->get_enemy_board().find_square(x, y).remove_mine();
		std::cout << "Your unit was destroyed by a mine, commander." << std::endl;
		proceed();
		return true;
	}
	if (player1->get_player_board().find_square(x, y).is_mine() && unit->is_mine_clearing())
	{
		player1->get_player_board().find_square(x, y).remove_mine();
		player2->get_enemy_board().find_square(x, y).remove_mine();
		player2->get_enemy_board().find_square(x, y).hide_square();
		unit->remove_mine_clearing();
		std::cout << "Your unit removed a mine on its path, commander." << std::endl;
		proceed();
	}
	if (player1->get_player_board().find_square(x, y).is_mine() && unit->is_repair_kit())
	{
		player1->get_player_board().find_square(x, y).remove_mine();
		player2->get_enemy_board().find_square(x, y).remove_mine();
		player2->get_enemy_board().find_square(x, y).hide_square();
		unit->remove_repair_kit();
		std::cout << "Your unit was damaged by a mine, commander. Luckily your boys had a repair kit." << std::endl;
		proceed();
	}
	return false;
}
void loot(Square& square, Unit* unit)
{
	if (square.is_repair_kit())
	{
		square.remove_repair_kit();
		unit->set_repair_kit();
		std::cout << "Your unit got a repair kit, commander." << std::endl;
		proceed();
	}
	if (square.is_mask_kit())
	{
		square.remove_mask_kit();
		unit->set_mask_kit();
		std::cout << "Your unit got a mask kit, commander." << std::endl;
		proceed();
	}
	if (square.is_recon_kit())
	{
		square.remove_recon_kit();
		unit->set_recon_kit();
		std::cout << "Your unit got a reconnaissance kit, commander." << std::endl;
		proceed();
	}
	if (square.is_extra_ammo())
	{
		square.remove_extra_ammo();
		unit->get_ammo() += 5;
		std::cout << "Your unit got additional ammo, commander." << std::endl;
		proceed();
	}
	if (square.is_air_support())
	{
		square.remove_air_support();
		unit->set_air_support();
		std::cout << "Your unit got connection with air support, commander." << std::endl;
		proceed();
	}
	if (square.is_mine_clearing())
	{
		square.remove_mine_clearing();
		unit->set_mine_clearing();
		std::cout << "Your unit got a mine clearing kit, commander." << std::endl;
		proceed();
	}
}
void move_update(Player* player1, Player* player2, Unit* unit, Square& prev_square, int x, int y)
{
	if (unit->is_recon_kit())
	{
		player1->get_enemy_board().recon_hide(player1->get_enemy_board().find_square(prev_square.cget_x_pos(), prev_square.cget_y_pos()));
	}
	if (unit->is_mask_kit())
	{
		player2->get_enemy_board().find_square(prev_square.cget_x_pos(), prev_square.cget_y_pos()).remove_no_recon();
	}
	prev_square.remove_unit();
	player2->get_enemy_board().find_square(prev_square.cget_x_pos(), prev_square.cget_y_pos()).remove_unit();
	prev_square.hide_square();
	player1->get_player_board().unlocker(prev_square);
	unit->get_x_pos() = x;
	unit->get_y_pos() = y;
	//unit->get_square().set_unit();
	player1->get_player_board().find_square(x, y).set_unit();
	player1->get_player_board().find_square(x, y).unhide_square();
	player1->get_player_board().find_square(x, y).assign_unit_id(unit->cget_unit_id());
	player2->get_enemy_board().find_square(x, y).assign_unit_id(unit->cget_unit_id());
	player1->get_player_board().locker(unit->get_square());
	player2->get_enemy_board().find_square(x, y).set_unit();
	if (unit->is_recon_kit())
	{
		player1->get_enemy_board().recon_unhide(player1->get_enemy_board().find_square(x, y));
	}
	if (unit->is_mask_kit())
	{
		player2->get_enemy_board().find_square(x,y).set_no_recon();
		player2->get_enemy_board().find_square(x, y).hide_square();
	}
	std::cout << "Your unit reached the destination, commander." << std::endl;
	proceed();
}
bool shoot(Player* player1, Player* player2, Unit* unit)
{
	if (unit->cget_ammo() == 0)
	{
		std::cout << "Your unit is out of ammo, commander." << std::endl;
		proceed();
		return false;
	}
	else
	{
		Square* target_square = nullptr;
		do
		{
			target_square = &player1->get_enemy_board().get_pos();
			if (target_square->is_hit())
			{
				std::cout << "We have already hit that square, commander." << std::endl;
				proceed();
			}
			if (target_square->is_kill())
			{
				std::cout << "We have already distroyed that unit, commander." << std::endl;
				proceed();
			}
			if (target_square->is_mine())
			{
				std::cout << "We planted a mine there, commander." << std::endl;
				proceed();
			}

		} while (target_square->is_hit() || target_square->is_kill() || target_square->is_mine());
		if (target_square->is_unit())
		{
			std::cout << "Target eliminated, commander." << std::endl;
			proceed();
			--unit->get_ammo();
			int x, y;
			x = target_square->cget_x_pos();
			y = target_square->cget_y_pos();
			remove_killed_unit(player1, player2, x, y);
			return true;
		}
		else
		{
			std::cout << "Missed, commander." << std::endl;
			proceed();
			--unit->get_ammo();
			target_square->set_hit();
			player2->get_player_board().find_square(target_square->cget_x_pos(), target_square->cget_y_pos()).set_hit();
			return true;
		}
	}
}
bool call_air_support(Player* player1, Player* player2, Unit* unit)
{
	Square* target_square = nullptr;
	if (!unit->is_air_support())
	{
		std::cout << "Your unit has no connection with air support, commander." << std::endl;
		proceed();
		return false;
	}
	else
	{
		do
		{
			target_square = &player1->get_enemy_board().get_pos();
		} while (!player1->get_enemy_board().is_in_range(target_square->cget_x_pos() - 1, target_square->cget_y_pos())
			|| !player1->get_enemy_board().is_in_range(target_square->cget_x_pos() + 1, target_square->cget_y_pos())
			|| !player1->get_enemy_board().is_in_range(target_square->cget_x_pos(), target_square->cget_y_pos() - 1)
			|| !player1->get_enemy_board().is_in_range(target_square->cget_x_pos(), target_square->cget_y_pos() + 1));
	}
	std::cout << "Coordinates received, commander. Ready to engage." << std::endl;
	proceed();
	int x, y;
	x = target_square->cget_x_pos();
	y = target_square->cget_y_pos();
	if (target_square->is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//lft
	x = target_square->cget_x_pos() - 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//rgt
	x = target_square->cget_x_pos() + 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//bwd
	x = target_square->cget_x_pos();
	y = target_square->cget_y_pos() - 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//fwd
	y = target_square->cget_y_pos() + 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//fwd lft
	x = target_square->cget_x_pos() - 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//bwd lft
	y = target_square->cget_y_pos() - 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//bwd rgt
	x = target_square->cget_x_pos() + 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	//fwd rgt
	y = target_square->cget_y_pos() + 1;
	if (player1->get_enemy_board().find_square(x, y).is_unit())
	{
		remove_killed_unit(player1, player2, x, y);
	}
	else
	{
		player1->get_enemy_board().find_square(x, y).set_hit();
		player2->get_player_board().find_square(x, y).set_hit();
	}
	unit->remove_air_support();
	std::cout << "Air assault finished, commander." << std::endl;
	proceed();
	return true;
}
void remove_killed_unit(Player* player1, Player* player2, int x, int y)
{
	player1->get_enemy_board().find_square(x, y).remove_unit();
	player1->get_enemy_board().find_square(x, y).set_kill();
	player2->get_player_board().unlocker(player2->get_player_board().find_square(x, y));
	for (int i = 0; i < player2->cget_my_units().size(); ++i)
	{
		Unit* unit = &player2->get_my_units()[i];
		if (unit->cget_x_pos() == x && unit->cget_y_pos() == y)
		{
			if (unit->is_recon_kit())
			{
				player2->get_enemy_board().recon_hide(player2->get_enemy_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()));
			}
			if (unit->is_mask_kit())
			{
					player2->get_enemy_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()).remove_no_recon();
			}
			player2->erase_unit(unit);
			break;
		}
	}
	player2->get_player_board().find_square(x, y).remove_unit();
	player2->get_player_board().find_square(x, y).set_kill();
}
void report(Player* player1, Player* player2)
{
	std::cout << "You have " << player1->cget_my_units().size() << " units, commander.\n";
	for (int i = 0; i < player1->cget_my_units().size(); ++i)
	{
		std::cout << "\nU" << player1->cget_my_units()[i].cget_unit_id() << ": ammo = " << player1->cget_my_units()[i].cget_ammo()
			<< "\nUpgrades:";
		if (player1->cget_my_units()[i].is_repair_kit())
			std::cout << " repair kit |";
		if (player1->cget_my_units()[i].is_air_support())
			std::cout << " air support |";
		if (player1->cget_my_units()[i].is_mask_kit())
			std::cout << " mask kit |";
		if (player1->cget_my_units()[i].is_mine_clearing())
			std::cout << " mine clearing kit |";
		if (player1->cget_my_units()[i].is_recon_kit())
			std::cout << " reconnaissance kit |";
		if(!player1->cget_my_units()[i].is_repair_kit() && !player1->cget_my_units()[i].is_air_support() && !player1->cget_my_units()[i].is_mask_kit()
			&& !player1->cget_my_units()[i].is_mine_clearing() && !player1->cget_my_units()[i].is_recon_kit())
			std::cout << "n/a";
	}
	std::cout << "\nEnemy units destroyed: " << player2->cget_number_of_units() - player2->cget_my_units().size() << "\n";
	std::cout << "Total ammo: " << player1->cget_total_ammo() << std::endl;
}
bool game_over(const Player& player1, const Player& player2)
{
	if (player1.cget_total_ammo() == 0 && player2.cget_my_units().size() == 0)
	{
		std::cout << "Game over! Commander " << player1.cget_player_name() << " wins!" << std::endl;
		proceed();
		return true;
	}
	else if (player2.cget_total_ammo() == 0 && player1.cget_my_units().size() == 0)
	{
		std::cout << "Game over! Commander " << player2.cget_player_name() << " wins!" << std::endl;
		proceed();
		return true;
	}
	else if (player1.cget_my_units().size() == 0 || player1.cget_total_ammo() == 0)
	{
		std::cout << "Game over! Commander " << player2.cget_player_name() << " wins!" << std::endl;
		proceed();
		return true;
	}
	else if (player2.cget_my_units().size() == 0 || player2.cget_total_ammo() == 0)
	{
		std::cout << "Game over! Commander " << player1.cget_player_name() << " wins!" << std::endl;
		proceed();
		return true;
	}
	else
	{
		return false;
	}
}
void proceed()
{
	char choice = ' ';
	do
	{
		std::cout << "Press 'y' to continue.\n";
		std::cin >> choice;
	} while (choice != 'y');
}
void intro_text()
{
	std::cout << "Primitive Tanks\n" <<
		"This is a two - player turn - based board game played on one computer.\n" <<
		"\nGame Setup\n" <<
		"Each player has two boards 15X12 squares.The Player Board is used to move the player's units and collect loot items.\n"
		<< "The Enemy Board is used to plant mines, shoot, and reconnoiter.\n"
		<< "At the beginning of the game, players plant mines on their Enemy Boards and place their units on their Player Boards.\n" <<
		"When a unit is placed, it locks squares around itself, which means that other units cannotbe placed there or move through those squares.\n"
		<< "This ensures some maneuvering space for units.So, when you place two units near each other, the distance between them must be at least two squares.\n"
		<< "You plant mines and place units by entering their coordinates.After each action, the result will be displayed on the screen.\n"
		<< "Each player plants five mines and places ten units.\n"
		<< "Once both players have finished planting mines and placing units, the program randomly distributes loot items on Player Boards.\n"
		<< "Then the combat begines.\n"
		<< "\nGame Process\n"
		<< "Each turn consists of the following stages: selecting unit, selecting an action to be performed by the selected unit, and displaying the result.\n"
		<< "Only one action can be performed on one turn.You can move your unit, shoot with your unit, or make an air assault.\n"
		<< "For the latter, the selected unit needs to have a special loot item.\n"
		<< "You can move your units forward, backward, left, right, or you can move in any of the mentioned directions with one turn, like knight in chess.\n"
		<< "But the length of your move must not exceed three squares.\n"
		<< "You cannot move through squares locked by other units(marked as lock), hit by you opponent's shots(hit), or occupied by destroyed units (kill).\n"
		<< "While moving, you may collect loot items or get destroyed by a mine.\n"
		<< "Use your Enemy Board for shooting.The result will be displayed both on your Enemy Board and your opponent's Player Board.\n"
		<< "If you have a unit with the air support item, you can select a square on your Enemy Board as a central target point.\n"
		<< "The air support will hit that square and all adjacent squares, killing all enemy units in that area.\n"
		<< "You cannot select squares on board edges as the central target for the air assault.\n"
		<< "\nLoot Items\n"
		<< "Reapir Kit and Mine Clearing Kit help your unit to cope with mines.Once your unit encounters a mine, it will survive, losing the item.\n"
		<< "Air Support enables your unit to call air support.Unfortunately, you can do it only once during a game.\n"
		<< "If your unit has Reconnaissance Kit, you will see on your Enemy Board if there are enemy units in the area relevant\n"
		<< "to you unit's current position and its locked squares. Of course, provided that the enemy unit does not have Mask Kit.\n"
		<< "If a unit with Mask Kit enters and then leaves the reconnoitered area, the square will remain invisible until being reconnoitered again.\n"
		<< "Reconnaissance Kit and Mask Kit remain with their owners while they live.\n"
		<< "You can also find Extra Ammo, adding + 5 to your unit's ammo.\n"
		<< "\nGame End\n"
		<< "Who loses their units or is out of ammo first, loses the game.\n"
		<< "An now just enjoy playing." << std::endl;
	proceed();
}