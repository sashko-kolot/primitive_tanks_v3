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
const Square& Board::cget_pos() const
{
	int x = 0, y = 0;
	std::cout << "Enter coordinates (x y): ";
	std::cin >> x >> y;
//check range
	if (!is_in_range(x,y))
	{
		std::cout << "Out of range!" << std::endl;
		cget_pos();
	}
	return find_square(x, y);
}
//find square
const Square& Board::find_square(uint x, uint y) const
{
	for (uint i = 0; i < board_size; ++i)
	{
		if (cget_board()[i].cget_square().cget_x_pos() == x && cget_board()[i].cget_square().cget_y_pos() == y)
			return cget_board()[i].cget_square();
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
//check square accessibility
bool Board::is_accessible(Square square) const
{
	uint x = 0, y = 0;
	bool left = false, right = false, top = false, bottom = false;
	if (square.is_locked() || square.is_hit())
	{
		return false;
	}
	//check left side
	else if (is_in_range(square.cget_x_pos() - 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos();
		left = true;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check right side
	else if (is_in_range(square.cget_x_pos() + 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos();
		right = true;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check top
	else if (is_in_range(square.cget_x_pos(), square.cget_y_pos() + 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() + 1;
		top = true;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check bottom
	else if (is_in_range(square.cget_x_pos(), square.cget_y_pos() - 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() - 1;
		bottom = true;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check top left
	else if (left == true && top == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() + 1;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check bottom left
	else if (left == true && bottom == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() - 1;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check top right
	else if (right == true && top == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() + 1;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	//check bottom right
	else if (right == true && top == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() - 1;
		if (find_square(x, y).is_locked())
		{
			return false;
		}
	}
	else
		return true;
}
//check range
bool Board::is_in_range(int x, int y) const
{
	if (x < 1 || x > x_size || y < 1 || y > y_size)
		return false;
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