#include "Player.h"

int main()
{
	Player player1;
	Player player2;
	player1.get_player().set_my_turn();
	player1.place_mines_and_units(player1.get_player(), player2.get_player());
	player2.place_mines_and_units(player1.get_player(), player2.get_player());
	//Gameplay game;
	//game.game_setup();

	/*Board board;
	board.build_board();
	board.display_board();*/
	return 0;
}