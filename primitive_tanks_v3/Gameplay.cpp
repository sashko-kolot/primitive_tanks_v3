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
			sq = rand() % player_board.get_board().size();
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
			me->count_total_ammo();
			opponent->get_enemy_board().find_square(cur_unit->cget_x_pos(), cur_unit->cget_y_pos()).remove_mine();
			std::cout << "Your unit was destroyed by a mine, commander." << std::endl;
			proceed();
			break;
		}
		char action = ' ';
		std::cout << "Press 'm' to move, 's' to shoot, 'r' to reconnoiter, or 'a' to call air support: ";
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
		case 'r':
			if (reconnoiter(me, cur_unit))
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
		return false;
	}
	//move fwd
	if (xdif == 0 && ydif > 0)
	{
		if (move_fwd(player1, player2, unit, ydif))
			return true;
		else
			return false;
	}
	//move bwd
	if (xdif == 0 && ydif < 0)
	{
		if (move_bwd(player1, player2, unit, ydif))
			return true;
		else
			return false;
	}
	//move left
	if (ydif == 0 && xdif < 0)
	{
		if (move_lft(player1, player2, unit, xdif))
			return true;
		else
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
				return false;
		}
	}
	//move fwd & left or left & fwd
	if (xdif < 0 && ydif > 0)
	{
		if (move_fwd_lft(player1, player2, unit, xdif, ydif))
			return true;
		else
			return false;
	}
	//move bwd & right or right & bwd
	if (xdif > 0 && ydif < 0)
	{
		if (move_bwd_rgt(player1, player2, unit, xdif, ydif))
			return true;
		else
			return false;
	}
	//move bwd & left or left & bwd
	if (xdif < 0 && ydif < 0)
	{
		if (move_bwd_lft(player1, player2, unit, xdif, ydif))
		
			return true;
		else
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
	int x, y;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (!is_passable(player1, x, y))
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
	}
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
		y = unit->cget_y_pos() + i;
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
	int x, y;
	for (int i = 1; i <= ydif; ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() + i;
		if (!is_passable(player1, x, y))
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
	}
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
		y = unit->cget_y_pos() + i;
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
		y = unit->cget_y_pos();
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
	int x, y;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (!is_passable(player1, x, y))
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
	}
	for (int i = 1; i <= xdif; ++i)
	{
		x = unit->cget_x_pos() + i;
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
	int x, y;
	for (int i = 1; i <= abs(ydif); ++i)
	{
		x = unit->cget_x_pos();
		y = unit->cget_y_pos() - i;
		if (!is_passable(player1, x, y))
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
	}
	for (int i = 1; i <= abs(xdif); ++i)
	{
		x = unit->cget_x_pos() - i;
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
		std::cout << "The square is inaccessible, commander." << std::endl;
		proceed();
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
		if (unit->is_recon_kit() && unit->get_reconned_squares().size() > 0)
		{
			/*for (int i = 0; i < unit->get_reconned_squares().size(); ++i)
			{
				unit->get_reconned_squares()[i].hide_square();
			}*/
			for (auto& ptr : unit->get_reconned_squares())
			{
				ptr->unhide_square();
			}
		}
		player1->get_player_board().find_square(unit->cget_x_pos(), unit->cget_y_pos()).remove_unit();
		player1->erase_unit(unit);
		player1->count_total_ammo();
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
	prev_square.remove_unit();
	prev_square.hide_square();
	player1->get_player_board().unlocker(prev_square);
	unit->get_x_pos() = x;
	unit->get_y_pos() = y;
	unit->get_square().set_unit();
	player1->get_player_board().find_square(x, y).set_unit();
	player1->get_player_board().find_square(x, y).unhide_square();
	player1->get_player_board().find_square(x, y).assign_unit_id(unit->cget_unit_id());
	player1->get_player_board().locker(unit->get_square());
	player2->get_enemy_board().find_square(x, y).set_unit();
	if (!player2->get_enemy_board().find_square(x, y).is_hidden() && unit->is_mask_kit())
	{
		player2->get_enemy_board().find_square(x, y).hide_square();
		unit->remove_mask_kit();
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
			player1->count_total_ammo();
			player2->count_total_ammo();
			return true;
		}
		else
		{
			std::cout << "Missed, commander." << std::endl;
			proceed();
			--unit->get_ammo();
			target_square->set_hit();
			player2->get_player_board().find_square(target_square->cget_x_pos(), target_square->cget_y_pos()).set_hit();
			player1->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
		player2->count_total_ammo();
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
bool reconnoiter(Player* player1, Unit* unit)
{
	Square* target_square = nullptr;
	if (!unit->is_recon_kit())
	{
		std::cout << "Your unit has no reconnaissance kit, commander." << std::endl;
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
	std::cout << "Coordinates received, commander. Ready to recon." << std::endl;
	proceed();
	int x, y;
	x = target_square->cget_x_pos();
	y = target_square->cget_y_pos();
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	x = target_square->cget_x_pos() - 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	x = target_square->cget_x_pos() + 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	x = target_square->cget_x_pos();
	y = target_square->cget_y_pos() - 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	y = target_square->cget_y_pos() + 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	x = target_square->cget_x_pos() - 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	y = target_square->cget_y_pos() - 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	x = target_square->cget_x_pos() + 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	y = target_square->cget_y_pos() + 1;
	unit->get_reconned_squares().push_back(std::make_shared<Square>(player1->get_enemy_board().find_square(x, y)));
	//for (int i = 0; i < unit->get_reconned_squares().size(); ++i)
	for(auto& ptr : unit->get_reconned_squares())
	{
		ptr->unhide_square();
	}
	std::cout << "The selected area is being surveilled, commander. Should any enemy unit appear in the area, you will see it on your enemy board." << std::endl;
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
			if (unit->is_recon_kit() && unit->get_reconned_squares().size() > 0)
			{
				//for (int i = 0; i < unit->get_reconned_squares().size(); ++i)
				/*{
					unit->get_reconned_squares()[i].hide_square();
				}*/
				for (auto& ptr : unit->get_reconned_squares())
				{
					ptr->unhide_square();
				}
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
		else if (player1->cget_my_units()[i].is_air_support())
			std::cout << " air support |";
		else if (player1->cget_my_units()[i].is_mask_kit())
			std::cout << " mask kit |";
		else if (player1->cget_my_units()[i].is_mine_clearing())
			std::cout << " mine clearing kit |";
		else if (player1->cget_my_units()[i].is_recon_kit())
			std::cout << " reconnaissance kit |";
		else
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