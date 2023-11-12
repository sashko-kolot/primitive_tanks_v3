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
//place units on board
/*void Player::place_units()
{
	std::cout << "Now it's time to demonstrate your tactical genious, commander. Order your units to take their combat positions." << std::endl;
	Square* square = nullptr;
	for (uint i = 0; i < number_of_units; ++i)
	{
		do
		{
			system("cls");
			player_board.display_board();
			square = &player_board.get_pos();
		} while (!player_board.is_accessible(*square));
		get_my_units()[i].get_x_pos() = square->cget_x_pos();
		get_my_units()[i].get_y_pos() = square->cget_y_pos();
		square->unhide_square(); 
		square->assign_unit_id(get_my_units()[i].cget_unit().cget_unit_id());
		player_board.locker(*square);
		player_board.display_board();
	}
	std::cout << "All your units are in their combat positions, commander." << std::endl;
	proceed();
	system("cls");
}*/
/*void Player::place_units(Player& player1, Player& player2)
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
	std::cout << "Now it's time to demonstrate your tactical genious, commander. Order your units to take their combat positions." << std::endl;
	Square* square = nullptr;
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
		opponent->enemy_board.find_square(square->cget_x_pos(),square->cget_y_pos()).set_unit();
		square->unhide_square();
		square->assign_unit_id(me->get_my_units()[i].cget_unit().cget_unit_id());
		me->player_board.locker(*square);
		me->player_board.display_board();
	}
	std::cout << "All your units are in their combat positions, commander." << std::endl;
	proceed();
	me->set_not_my_turn();
	opponent->set_my_turn();
	system("cls");
}*/
//try to merge mine_board() and place_units() functions. If it works, delete mine_board() and place_units() functions.
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
/*void Player::set_my_turn()
{
	if (is_my_turn())
	{
		my_turn = false;
	}
	else
	{
		my_turn = true;
	}
}*/
//mine the enemy's player_board
/*void Player::mine_board()
{
	Square* square = nullptr;
	//intro text
	std::cout << "Commander, we have some time before the battle starts. Use it wisely. Our engineers have prepared some surprises for the enemy and are waiting for your orders. Mining is as important as shooting and maneuvering. Think carefully where to plant our mines." << std::endl;
	proceed();
	for (uint i = 0; i < number_of_mines; ++i)
		enemy_board.display_board();
	{
		do
		{
			system("cls");
			square = &enemy_board.get_pos();
			if (square->is_mine())
				std::cout << "We have mined this square already, commander." << std::endl;
		} while (!square->is_mine());
		square->set_mine();
		square->unhide_square();
		enemy_board.display_board();
		proceed();
	}
	std::cout << "Mining complete, commander." << std::endl;
	proceed();
	system("cls");
}*/
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
//find unit
//const Unit& Player::find_unit(Square square) const
//{
//	for (uint i = 0; i < number_of_units; ++i)
//	{
//		if (cget_my_units()[i].cget_unit().cget_x_pos() == square.cget_square().cget_x_pos() && cget_my_units()[i].cget_unit().cget_y_pos() == square.cget_square().cget_y_pos())
//			return cget_my_units()[i].cget_unit();
//	}
//}
