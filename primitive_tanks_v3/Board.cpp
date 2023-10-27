#include "Board.h"
uint Board::x_size = 15, Board::y_size = 12, Board::board_size = x_size * y_size;
//get board
std::vector<Square>& Board::get_board()
{
	return board;
}
const std::vector<Square>& Board::cget_board() const
{
	return board;
}
//get position from player
Square& Board::get_pos()
{
	uint x = 0, y = 0;
	std::cout << "Enter coordinates (x y): ";
	std::cin >> x >> y;
//check range
	if (x < 1 || x > x_size || y < 1 || y > y_size)
	{
		std::cout << "Out of range!" << std::endl;
		get_pos();
	}
//find square
	for (uint i = 0; i < board_size; ++i)
	{
		if (get_board()[i].get_square().get_x_pos() == x &&
			get_board()[i].get_square().get_y_pos() == y)
		{
			return get_board()[i].get_square();
		}
	}
}
//build board
void Board::build_board()
{
	for (uint i = 0; i < board_size; ++i)
	{
		Square square;
		get_board().push_back(square);
	}
	uint y = y_size, x = 1;
	for (uint i = 0; i < board_size; ++i)
	{
			get_board()[i].get_square().get_x_pos() = x;
			get_board()[i].get_square().get_y_pos() = y;
			++x;
			if (x > x_size)
			{
				x = 1;
				--y;
			}
	}
}
//display board for debug
void Board::display_board() const
{
	for (uint i = 0; i < board_size; ++i)
	{
		std::cout <<  cget_board()[i].cget_square().cget_x_pos() << ":" << cget_board()[i].cget_square().cget_y_pos() << "\t";
		if ((i + 1) % x_size == 0)
		{
			std::cout << std::endl;
		}
	}
}