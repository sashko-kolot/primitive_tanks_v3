#include "gameplay.h"

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
	place_mines_and_units(player1.get_player(), player2.get_player());
	place_loot(player1.get_player_board());
	place_mines_and_units(player1.get_player(), player2.get_player());
	place_loot(player2.get_player_board());
	do
	{
		action(player1.get_player(), player2.get_player());
	} while (!game_over(player1.get_player(), player2.get_player()));
	return 0;
}