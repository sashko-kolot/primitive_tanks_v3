#include "Player.h"

int main()
{
	Player player1;
	Player player2;
	std::cout << "Player 1, you are welcome." << std::endl;
	player1.get_player().set_player_name();
	system("cls");
	std::cout << "Player 2, you are welcome." << std::endl;
	player2.get_player().set_player_name();
	system("cls");
	player1.get_player().set_my_turn();
	player1.place_mines_and_units(player1.get_player(), player2.get_player());
	player2.place_mines_and_units(player1.get_player(), player2.get_player());
	do
	{
		Player::action(player1.get_player(), player2.get_player());
	} while (!Player::game_over(player1.get_player(), player2.get_player()));
	return 0;
}