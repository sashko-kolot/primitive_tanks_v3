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
	for (uint i = 0; i < number_of_units; ++i)
	{
		Unit unit;
		unit.set_unit_id(i + 1);
		get_my_units().push_back(unit);
	}
}
void Player::place_mines_and_units(Player& player1, Player& player2)
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
	for (uint i = 0; i < number_of_mines; ++i)
	{
		me->enemy_board.display_board();
		do
		{
			square = &me->enemy_board.get_pos();
			if (square->is_mine())
				std::cout << "We have mined this square already, commander." << std::endl;
		} while (square->is_mine());
		square->set_mine();
		opponent->player_board.find_square(square->cget_x_pos(), square->cget_y_pos()).set_mine();
		square->unhide_square();
		me->enemy_board.display_board();
		proceed();
		system("cls");
	}
	std::cout << "Mining complete, commander." << std::endl;
	proceed();
	system("cls");
	std::cout << "Now it's time to demonstrate your tactical genious, commander. Order your units to take their combat positions." << std::endl;
	proceed();
	for (uint i = 0; i < number_of_units; ++i)
	{
		do
		{
			system("cls");
			me->player_board.display_board();
			square = &me->player_board.get_pos();
		} while (!me->player_board.is_accessible(*square));
		me->get_my_units()[i].get_x_pos() = square->cget_x_pos();
		me->get_my_units()[i].get_y_pos() = square->cget_y_pos();
		square->set_unit();
		square->unhide_square();
		square->assign_unit_id(me->get_my_units()[i].cget_unit().cget_unit_id());
		opponent->enemy_board.find_square(square->cget_x_pos(), square->cget_y_pos()).set_unit();
		opponent->enemy_board.find_square(square->cget_x_pos(), square->cget_y_pos()).assign_unit_id(me->get_my_units()[i].cget_unit().cget_unit_id());
		me->player_board.locker(*square);
		me->player_board.display_board();
	}
	std::cout << "All your units are in their combat positions, commander." << std::endl;
	proceed();
	me->set_not_my_turn();
	opponent->set_my_turn();
	system("cls");
}
//get player
Player& Player::get_player()
{
	return *this;
}
//get unit by its id
Unit& Player::find_unit_by_id()
{
	uint id = 0;
	bool is_unit = false;
	do
	{ 
	std::cout << "Select a unit by entering its id: ";
	std::cin >> id;
	for (uint i = 0; i < my_units.size(); ++i)
	{
		if (id == my_units[i].cget_unit_id())
		{
			return my_units[i].get_unit();
			is_unit = true;
		}
	}
	} while (!is_unit);
}
//get total ammo
const uint& Player::cget_total_ammo() const
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
//press space to continue	
void Player::proceed()
	{
		char choice = ' ';
		do
		{
			std::cout << "Press 'y' to continue.\n";
			std::cin >> choice;
		} while (choice != 'y');
	}
//place loot
void Player::place_loot(Player& player)
{
	for(uint i = 0; i < 6; ++i)
	{ 
	int sq = 0;
	do
	{ 
	sq = rand() % player_board.cget_board().size();
	} while (player_board.cget_board()[sq].cget_square().is_unit() || player_board.cget_board()[sq].cget_square().is_mine() || player_board.cget_board()[sq].cget_square().is_loot());
	if(i == 1)
	{
		player_board.get_board()[sq].get_square().set_repair_kit();
	}
	if(i == 2)
	{
		player_board.get_board()[sq].get_square().set_mask_kit();
	}
	if(i == 3)
	{
		player_board.get_board()[sq].get_square().set_recon_kit();
	}
	if(i == 4)
	{
		player_board.get_board()[sq].get_square().set_air_support();
	}
	if(i == 5)
	{
		player_board.get_board()[sq].get_square().set_mine_clearing();
	}
	if(i == 6)
	{
		player_board.get_board()[sq].get_square().set_extra_ammo();
	}
	}
}
static void Player::action(Player& player1, Player& player2)
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
	std::cout << "Player board" << std::endl;
	me->player_board.display_board();
	std::cout << "Enemy board" << std::endl;
	me->enemy_board.display_board();
	Unit* cur_unit = nullptr;
	bool action_completed = false;
	do
	{
		cur_unit = &me->find_unit_by_id();
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
	me->player_board.display_board();
	std::cout << "Enemy board" << std::endl;
	me->enemy_board.display_board();
	std::cout << "End of turn." << std::endl;
	proceed();
	me->set_not_my_turn();
	opponent->set_my_turn();
}
bool Player::move(Player* player1, Player* player2, Unit* unit)
	{
		Square* target_square = nullptr;
		int xdif = 0, ydif = 0, xydif = 0;
		target_square = &player1->player_board.get_pos();
		//check the distance to the target square
		xdif = target_square->cget_x_pos() - unit->cget_x_pos();
		ydif = target_square->cget_y_pos() - unit->cget_y_pos();
		xydif = abs(xdif) + abs(ydif);
		if(xydif > 3)
		{
			std::cout << "You cannot move there, commander." << std::endl;
			proceed();
			return false;
		}
		player1->player_board.unlocker(unit->get_square());
		if (!player1->player_board.is_accessible(target_square->get_square()))
		{
			return false;
		}
		//move fwd
		if(xdif == 0 && ydif > 0)
		{
			if (move_fwd(player1, player2, unit, ydif))
				return true;
			else
				return false;
		}
		//move bwd
		if(xdif == 0 && ydif < 0)
		{
			if (move_bwd(player1, player2, unit, ydif))
				return true;
			else
				return false;
		}
		//move left
		if(ydif == 0 && xdif < 0)
		{
			if (move_lft(player1, player2, unit, xdif))
				return true;
			else
				return false;
		}
		//move right
		if(ydif == 0 && xdif > 0)
		{
			if (move_rgt(player1, player2, unit, xdif))
				return true;
			else
				return false;
		}
		//move fwd & right or right & fwd
		if(xdif > 0 && ydif > 0)
		{
			for (uint i = 0; i < ydif; ++i)
			{
				if(move_fwd_rgt(player1, player2, unit, xdif, ydif))
					return true;
				else
					return false;
			}
		}
		//move fwd & left or left & fwd
		if(xdif < 0 && ydif > 0)
		{
			if (move_fwd_lft(player1, player2, unit, xdif, ydif))
				return true;
			else
				return false;
		}
		//move bwd & right or right & bwd
		if(xdif > 0 && ydif < 0)
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
	}
	void Player::loot(Square& square, Unit* unit)
	{
		if(square.is_repair_kit())
		{
			square.remove_repair_kit();
			unit->set_repair_kit();
			std::cout << "Your unit got a repair kit, commander." << std::endl;
			proceed();
		}
		if(square.is_mask_kit())
		{
			square.remove_mask_kit();
			unit->set_mask_kit();
			std::cout << "Your unit got a mask kit, commander." << std::endl;
			proceed();
		}
		if(square.is_recon_kit())
		{
			square.remove_recon_kit();
			unit->set_recon_kit();
			std::cout << "Your unit got a reconnaissance kit, commander." << std::endl;
			proceed();
		}
		if(square.is_extra_ammo())
		{
			square.remove_extra_ammo();
			unit->get_ammo() += 5;
			std::cout << "Your unit got additional ammo, commander." << std::endl;
			proceed();
		}
		if(square.is_air_support())
		{
			square.remove_air_support();
			unit->set_air_support();
			std::cout << "Your unit got connection with air support, commander." << std::endl;
			proceed();
		}
		if(square.is_mine_clearing())
		{
			square.remove_mine_clearing();
			unit->set_mine_clearing();
			std::cout << "Your unit got a mine clearing kit, commander." << std::endl;
			proceed();
		}
	}
	bool Player::mine_on_path(Player* player1, Player* player2, uint x, uint y, Unit* unit)
	{
		if (player1->player_board.find_square(x, y).is_mine() && !unit->is_mine_clearing() && !unit->is_repair_kit())
		{
			player1->player_board.find_square(x, y).set_kill();
			if (unit->is_recon_kit() && unit->get_reconned_squares().size() > 0)
			{
				for (uint i = 0; i < unit->get_reconned_squares().size(); ++i)
				{
					unit->get_reconned_squares()[i].hide_square();
				}
			}
			player1->my_units.erase(std::remove(my_units.begin(), my_units.end(), *unit), my_units.end());
			player1->count_total_ammo();
			player2->enemy_board.find_square(x, y).set_kill();
			player2->enemy_board.find_square(x, y).remove_mine();
			std::cout << "Your unit was destroyed by a mine, commander." << std::endl;
			proceed();
			return true;
		}
		if (player1->player_board.find_square(x, y).is_mine() && unit->is_mine_clearing())
		{
			player1->player_board.find_square(x, y).remove_mine();
			player2->enemy_board.find_square(x, y).remove_mine();
			player2->enemy_board.find_square(x, y).hide_square();
			unit->remove_mine_clearing();
			std::cout << "Your unit removed a mine on its path, commander." << std::endl;
			proceed();
		}
		if (player1->player_board.find_square(x, y).is_mine() && unit->is_repair_kit())
		{
			player1->player_board.find_square(x, y).remove_mine();
			player2->enemy_board.find_square(x, y).remove_mine();
			player2->enemy_board.find_square(x, y).hide_square();
			unit->remove_repair_kit();
			std::cout << "Your unit was damaged by a mine, commander. Luckily your boys had a repair kit." << std::endl;
			proceed();
		}
		return false;
	}
	bool Player::is_passable(Player* player1, uint x, uint y)
	{
		if(player1->player_board.find_square(x, y).is_locked() || player1->player_board.find_square(x, y).is_hit()
			|| player1->player_board.find_square(x, y).is_kill())
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
	void Player::move_update(Player* player1, Player* player2, Unit* unit, uint x, uint y)
	{
		unit->get_square().remove_unit();
		unit->get_square().hide_square();
		player1->player_board.find_square(x, y).set_unit();
		unit->get_x_pos() = x;
		unit->get_y_pos() = y;
		unit->get_square().unhide_square();
		player1->player_board.locker(unit->get_square());
		player2->enemy_board.find_square(x, y).set_unit();
		if (!player2->enemy_board.find_square(x, y).is_hidden() && unit->is_mask_kit())
		{
			player2->enemy_board.find_square(x, y).hide_square();
			unit->remove_mask_kit();
		}
		std::cout << "Your unit reached the destination, commander." << std::endl;
		proceed();
	}
	bool Player::move_fwd(Player* player1, Player* player2, Unit* unit, int ydif)
	{
		uint x, y;
		for (uint i = 0; i < ydif; ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() + i;
			if (!is_passable(player1, x, y))
			{
				return false;
			}
		}
		x = 0, y = 0;
		for (uint i = 0; i < ydif; ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() + i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		move_update(player1, player2, unit, x, y);
		return true;
	}
	bool Player::move_bwd(Player* player1, Player* player2, Unit* unit, int ydif)
	{

		uint x, y;
		for (uint i = 0; i < abs(ydif); ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() - i;
			if (!is_passable(player1, x, y))
				return false;
		}
		x = 0, y = 0;
		for (uint i = 0; i < abs(ydif); ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() - i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		move_update(player1, player2, unit, x, y);
		return true;
	}
	bool Player::move_lft(Player* player1, Player* player2, Unit* unit, int xdif)
	{
		uint x, y;
		for (uint i = 0; i < abs(xdif); ++i)
		{
			x = unit->cget_x_pos() - i;
			y = unit->cget_y_pos();
			if (!is_passable(player1, x, y))
				return false;
		}
		x = 0, y = 0;
		for (uint i = 0; i < abs(xdif); ++i)
		{
			x = unit->cget_x_pos() - i;
			y = unit->cget_y_pos();
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		move_update(player1, player2, unit, x, y);
		return true;
	}
	bool Player::move_rgt(Player* player1, Player* player2, Unit* unit, int xdif)
	{
		uint x, y;
		for (uint i = 0; i < xdif; ++i)
		{
			x = unit->cget_x_pos() + i;
			y = unit->cget_y_pos();
			if (!is_passable(player1, x, y))
				return false;
		}
			x = 0, y = 0;
			for (uint i = 0; i < xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				y = unit->cget_y_pos();
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->player_board.find_square(x, y), unit);
			}
			move_update(player1, player2, unit, x, y);
			return true;
	}
	bool Player::move_fwd_rgt(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
	{
		uint x, y;
		for (uint i = 0; i < ydif; ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() + i;
			if (!is_passable(player1, x, y))
			{
				for (uint i = 0; i < xdif; ++i)
				{
					x = unit->cget_x_pos() + i;
					y = unit->cget_y_pos();
					if (!is_passable(player1, x, y))
						return false;
				}
				for (uint i = 0; i < ydif; ++i)
				{
					y = unit->cget_y_pos() + i;
					if (!is_passable(player1, x, y))
						return false;
				}
				uint x = 0, y = 0;
				for (uint i = 0; i < xdif; ++i)
				{
					x = unit->cget_x_pos() + i;
					y = unit->cget_y_pos();
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				for (uint i = 0; i < ydif; ++i)
				{
					y = unit->cget_y_pos() + i;
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				move_update(player1, player2, unit, x, y);
				return true;
			}
		}
			for (uint i = 0; i < xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				if (!is_passable(player1, x, y))
					return false;
			}
			uint x = 0, y = 0;
			for (uint i = 0; i < ydif; ++i)
			{
				x = unit->cget_x_pos();
				y = unit->cget_y_pos() + i;
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->player_board.find_square(x, y), unit);
			}
			for (uint i = 0; i < xdif; ++i)
			{
				x = unit->cget_x_pos() + i;
				if (mine_on_path(player1, player2, x, y, unit))
					return true;
				else
					loot(player1->player_board.find_square(x, y), unit);
			}
			move_update(player1, player2, unit, x, y);
			return true;
	}
	bool Player::move_fwd_lft(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
	{
		uint x, y;
		for (uint i = 0; i < ydif; ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() + i;
			if (!is_passable(player1, x, y))
			{
				for (uint i = 0; i < abs(xdif); ++i)
				{
					x = unit->cget_x_pos() - i;
					y = unit->cget_y_pos();
					if (!is_passable(player1, x, y))
						return false;
				}
				for (uint i = 0; i < ydif; ++i)
				{
					y = unit->cget_y_pos() + i;
					if (!is_passable(player1, x, y))
						return false;
				}
				uint x = 0, y = 0;
				for (uint i = 0; i < abs(xdif); ++i)
				{
					x = unit->cget_x_pos() - i;
					y = unit->cget_y_pos();
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				for (uint i = 0; i < ydif; ++i)
				{
					y = unit->cget_y_pos() + i;
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				move_update(player1, player2, unit, x, y);
				return true;
			}
		}
		for (uint i = 0; i < abs(xdif); ++i)
		{
			x = unit->cget_x_pos() - i;
			if (!is_passable(player1, x, y))
				return false;
		}
		uint x = 0, y = 0;
		for (uint i = 0; i < ydif; ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() + i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		for (uint i = 0; i < abs(xdif); ++i)
		{
			x = unit->cget_x_pos() - i;
			y = unit->cget_y_pos();
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		move_update(player1, player2, unit, x, y);
		return true;
	}
	bool Player::move_bwd_rgt(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
	{
		uint x, y;
		for (uint i = 0; i < abs(ydif); ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() - i;
			if (!is_passable(player1, x, y))
			{
				for (uint i = 0; i < xdif; ++i)
				{
					x = unit->cget_x_pos() + i;
					y = unit->cget_y_pos();
					if (!is_passable(player1, x, y))
						return false;
				}
				for (uint i = 0; i < abs(ydif); ++i)
				{
					y = unit->cget_y_pos() - i;
					if (!is_passable(player1, x, y))
						return false;
				}
				uint x = 0, y = 0;
				for (uint i = 0; i < xdif; ++i)
				{
					x = unit->cget_x_pos() + i;
					y = unit->cget_y_pos();
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				for (uint i = 0; i < abs(ydif); ++i)
				{
					y = unit->cget_y_pos() - i;
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				move_update(player1, player2, unit, x, y);
				return true;
			}
		}
		for (uint i = 0; i < xdif; ++i)
		{
			x = unit->cget_x_pos() + i;
			if (!is_passable(player1, x, y))
				return false;
		}
		uint x = 0, y = 0;
		for (uint i = 0; i < abs(ydif); ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() - i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		for (uint i = 0; i < xdif; ++i)
		{
			x = unit->cget_x_pos() + i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		move_update(player1, player2, unit, x, y);
		return true;
	}
	bool Player::move_bwd_lft(Player* player1, Player* player2, Unit* unit, int xdif, int ydif)
	{
		uint x, y;
		for (uint i = 0; i < abs(ydif); ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() - i;
			if (!is_passable(player1, x, y))
			{
				for (uint i = 0; i < abs(xdif); ++i)
				{
					x = unit->cget_x_pos() - i;
					y = unit->cget_y_pos();
					if (!is_passable(player1, x, y))
						return false;
				}
				uint x = 0, y = 0;
				for (uint i = 0; i < abs(ydif); ++i)
				{
					y = unit->cget_y_pos() - i;
					if (!is_passable(player1, x, y))
						return false;
				}
				uint x = 0, y = 0;
				for (uint i = 0; i < abs(xdif); ++i)
				{
					x = unit->cget_x_pos() - i;
					y = unit->cget_y_pos();
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				for (uint i = 0; i < abs(ydif); ++i)
				{
					y = unit->cget_y_pos() - i;
					if (mine_on_path(player1, player2, x, y, unit))
						return true;
					else
						loot(player1->player_board.find_square(x, y), unit);
				}
				move_update(player1, player2, unit, x, y);
				return true;
			}
		}
		for (uint i = 0; i < abs(xdif); ++i)
		{
			x = unit->cget_x_pos() - i;
			if (!is_passable(player1, x, y))
				return false;
		}
		uint x = 0, y = 0;
		for (uint i = 0; i < abs(ydif); ++i)
		{
			x = unit->cget_x_pos();
			y = unit->cget_y_pos() - i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		for (uint i = 0; i < abs(xdif); ++i)
		{
			x = unit->cget_x_pos() - i;
			if (mine_on_path(player1, player2, x, y, unit))
				return true;
			else
				loot(player1->player_board.find_square(x, y), unit);
		}
		move_update(player1, player2, unit, x, y);
		return true;
	}
	bool Player::shoot(Player* player1, Player* player2, Unit* unit)
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
				target_square = &player1->enemy_board.get_pos();
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
			if(target_square->is_unit())
			{
				std::cout << "Target eliminated, commander." << std::endl;
				proceed();
				--unit->get_ammo();
				uint x, y;
				x = target_square->cget_x_pos();
				y = target_square->cget_y_pos();
				remove_killed_enemy_unit(player1, player2, x, y);
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
				player2->player_board.find_square(target_square->cget_x_pos(), target_square->cget_y_pos()).set_hit();
				return true;
			}
		}
	}
	bool Player::call_air_support(Player* player1, Player* player2, Unit* unit)
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
				target_square = &player1->enemy_board.get_pos();
			} while(!player1->enemy_board.is_in_range(target_square->cget_x_pos() - 1, target_square->cget_y_pos())
					|| !player1->enemy_board.is_in_range(target_square->cget_x_pos() + 1, target_square->cget_y_pos())
					|| !player1->enemy_board.is_in_range(target_square->cget_x_pos(), target_square->cget_y_pos() - 1)
					|| !player1->enemy_board.is_in_range(target_square->cget_x_pos(), target_square->cget_y_pos() + 1));
		}
		std::cout << "Coordinates received, commander. Ready to engage." << std::endl;
		proceed();
		uint x, y;
		x = target_square->cget_x_pos();
		y = target_square->cget_y_pos();
		if (target_square->is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//lft
		x = target_square->cget_x_pos() - 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//rgt
		x = target_square->cget_x_pos() + 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//bwd
		x = target_square->cget_x_pos();
		y = target_square->cget_y_pos() - 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//fwd
		y = target_square->cget_y_pos() + 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//fwd lft
		x = target_square->cget_x_pos() - 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//bwd lft
		y = target_square->cget_y_pos() - 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//bwd rgt
		x = target_square->cget_x_pos() + 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		//fwd rgt
		y = target_square->cget_y_pos() + 1;
		if (player1->enemy_board.find_square(x, y).is_unit())
		{
			remove_killed_enemy_unit(player1, player2, x, y);
		}
		std::cout << "Air assault finished, commander." << std::endl;
		proceed();
		return true;
	}
	void Player::remove_killed_enemy_unit(Player* player1, Player* player2, uint x, uint y)
	{
		player1->enemy_board.find_square(x, y).remove_unit();
		player1->enemy_board.find_square(x, y).set_kill();
		player2->player_board.unlocker(player2->player_board.find_square(x, y));
		for (uint i = 0; i < player2->my_units.size(); ++i)
		{
			Unit* enemy_unit = &player2->my_units[i];
			if (enemy_unit->cget_x_pos() == x && enemy_unit->cget_y_pos() == y)
			{
				if (enemy_unit->is_recon_kit() && enemy_unit->get_reconned_squares().size() > 0)
				{
					for (uint i = 0; i < enemy_unit->get_reconned_squares().size(); ++i)
					{
						enemy_unit->get_reconned_squares()[i].hide_square();
					}
				}
				player2->my_units.erase(std::remove(my_units.begin(), my_units.end(), *enemy_unit), my_units.end());
				break;
			}
		}
		player2->player_board.find_square(x, y).set_kill();
	}
	bool Player::reconnoiter(Player* player1, Unit* unit)
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
				target_square = &player1->enemy_board.get_pos();
			} while (!player1->enemy_board.is_in_range(target_square->cget_x_pos() - 1, target_square->cget_y_pos())
				|| !player1->enemy_board.is_in_range(target_square->cget_x_pos() + 1, target_square->cget_y_pos())
				|| !player1->enemy_board.is_in_range(target_square->cget_x_pos(), target_square->cget_y_pos() - 1)
				|| !player1->enemy_board.is_in_range(target_square->cget_x_pos(), target_square->cget_y_pos() + 1));
		}
		std::cout << "Coordinates received, commander. Ready to recon." << std::endl;
		proceed();
		uint x, y;
		x = target_square->cget_x_pos();
		y = target_square->cget_y_pos();
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		x = target_square->cget_x_pos() - 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		x = target_square->cget_x_pos() + 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		x = target_square->cget_x_pos();
		y = target_square->cget_y_pos() - 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		y = target_square->cget_y_pos() + 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		x = target_square->cget_x_pos() - 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		y = target_square->cget_y_pos() - 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		x = target_square->cget_x_pos() + 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		y = target_square->cget_y_pos() + 1;
		unit->get_reconned_squares().push_back(player1->enemy_board.find_square(x, y));
		for (uint i = 0; i < unit->get_reconned_squares().size(); ++i)
		{
			unit->get_reconned_squares()[i].unhide_square();
		}
		std::cout << "The selected area is being surveilled, commander. Should any enemy unit appear in the area, you will see it on your enemy board." << std::endl;
		proceed();
		return true;
	}
	void Player::report(Player* player1, Player* player2)
	{
		std::cout << "You have " << player1->cget_my_units().size() << " units, commander.\n";
		for (uint i = 0; i < player1->cget_my_units().size(); ++i)
		{
			std::cout << "U" << player1->cget_my_units()[i].cget_unit_id() << ": ammo = " << player1->cget_my_units()[i].cget_ammo()
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
		std::cout << "\nEnemy units destroyed: " << number_of_units - player2->cget_my_units().size() << "\n";
		std::cout << "Total ammo: " << player1->cget_total_ammo() << std::endl;
	}
	void Player::count_total_ammo()
	{
		for (uint i = 0; i < my_units.size(); ++i)
		{
			total_ammo = 0;
			total_ammo += my_units[i].cget_ammo();
		}
	}
	static bool Player::game_over(const Player& player1, const Player& player2)
	{
		if (player1.cget_total_ammo() == 0 && player2.cget_my_units().size() == 0)
		{
			std::cout << "Game over! Commander " << player1.cget_player_name() << " wins!" << std::endl;
			proceed();
			return true;
		}
		else if(player2.cget_total_ammo() == 0 && player1.cget_my_units().size() == 0)
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