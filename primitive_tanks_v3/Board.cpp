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
	int x = 0, y = 0;
	do
	{
		std::cout << "Enter coordinates (x y): ";
		std::cin >> x >> y;
		//check range
		if (!is_in_range(x, y))
		std::cout << "Out of range!" << std::endl;
	} while (!is_in_range(x, y));
	return find_square(x, y);
}
//find square
Square& Board::find_square(uint x, uint y) 
{
	for (uint i = 0; i < board_size; ++i)
	{
		if (cget_board()[i].cget_square().cget_x_pos() == x && cget_board()[i].cget_square().cget_y_pos() == y)
			return get_board()[i].get_square();
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
bool Board::is_accessible(Square& square)
{
	uint x = 0, y = 0;
	bool left = false, right = false, top = false, bottom = false;
	if (square.is_locked() || square.is_hit())
	{
		std::cout << "The square is inaccessible." << std::endl;
		proceed();
		return false;
	}
	//check left side
	if (is_in_range(square.cget_x_pos() - 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos();
		left = true;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check right side
	if (is_in_range(square.cget_x_pos() + 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos();
		right = true;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check top
	if (is_in_range(square.cget_x_pos(), square.cget_y_pos() + 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() + 1;
		top = true;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check bottom
	if (is_in_range(square.cget_x_pos(), square.cget_y_pos() - 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() - 1;
		bottom = true;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check top left
	if (left == true && top == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() + 1;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check bottom left
	if (left == true && bottom == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() - 1;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check top right
	if (right == true && top == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() + 1;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	//check bottom right
	if (right == true && bottom == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() - 1;
		if (find_square(x, y).is_locked())
		{
			std::cout << "The square is inaccessible." << std::endl;
			proceed();
			return false;
		}
	}
	return true;
}
//lock squares
void Board::locker(Square& square)
{
	uint x = 0, y = 0;
	bool left = false, right = false, top = false, bottom = false;
	//lock unit square
	square.lock_square();
	//check and lock the square on the left
	if (is_in_range(square.cget_x_pos() - 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos();
		left = true;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the right
	if (is_in_range(square.cget_x_pos() + 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos();
		right = true;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the top
	if (is_in_range(square.cget_x_pos(), square.cget_y_pos() + 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() + 1;
		top = true;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the bottom
	if (is_in_range(square.cget_x_pos(), square.cget_y_pos() - 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() - 1;
		bottom = true;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the top left
	if (left == true && top == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() + 1;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the bottom left
	if (left == true && bottom == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() - 1;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the top right
	if (right == true && top == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() + 1;
		find_square(x, y).lock_square();
	}
	//check and lock the square on the bottom right
	if (right == true && bottom == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() - 1;
		find_square(x, y).lock_square();
	}
}
//unlock squares
void Board::unlocker(Square& square)
{
	uint x = 0, y = 0;
	bool left = false, right = false, top = false, bottom = false;
	//unlock unit square
	square.unlock_square();
	//check and unlock the square on the left
	if (is_in_range(square.cget_x_pos() - 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos();
		left = true;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the right
	if (is_in_range(square.cget_x_pos() + 1, square.cget_y_pos()))
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos();
		right = true;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the top
	if (is_in_range(square.cget_x_pos(), square.cget_y_pos() + 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() + 1;
		top = true;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the bottom
	if (is_in_range(square.cget_x_pos(), square.cget_y_pos() - 1))
	{
		x = square.cget_x_pos();
		y = square.cget_y_pos() - 1;
		bottom = true;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the top left
	if (left == true && top == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() + 1;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the bottom left
	if (left == true && bottom == true)
	{
		x = square.cget_x_pos() - 1;
		y = square.cget_y_pos() - 1;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the top right
	if (right == true && top == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() + 1;
		find_square(x, y).unlock_square();
	}
	//check and unlock the square on the bottom right
	if (right == true && bottom == true)
	{
		x = square.cget_x_pos() + 1;
		y = square.cget_y_pos() - 1;
		find_square(x, y).unlock_square();
	}
}
//check range
bool Board::is_in_range(int x, int y) const
{
	if (x < 1 || x > x_size || y < 1 || y > y_size)
		return false;
	else
		return true;
}
//display board for debug
//void Board::display_board() const
//{
//	for (uint i = 0; i < board_size; ++i)
//	{
//		std::cout <<  cget_board()[i].cget_square().cget_x_pos() << ":" << cget_board()[i].cget_square().cget_y_pos() << "\t";
//		if ((i + 1) % x_size == 0)
//		{
//			std::cout << std::endl;
//		}
//	}
//}
void Board::display_board() const
{
	for (uint i = 0; i < board_size; ++i)
	{
		if (cget_board()[i].cget_square().is_unit() && !cget_board()[i].cget_square().is_hidden())
		{
			std::cout << "U" << cget_board()[i].cget_square().cget_cur_unit_id() << "\t";
		}
		else if (cget_board()[i].cget_square().is_kill())
		{
			std::cout << "kill" << "\t";
		}
		else if (cget_board()[i].cget_square().is_hit())
		{
			std::cout << "hit" << "\t";
		}
		else if (cget_board()[i].cget_square().is_mine() && !cget_board()[i].cget_square().is_hidden())
		{
			std::cout << "mine" << "\t";
		}
		else
		{
			std::cout << cget_board()[i].cget_square().cget_x_pos() << ":" << cget_board()[i].cget_square().cget_y_pos() << "\t";
		}
		if ((i + 1) % x_size == 0)
		{
			std::cout << std::endl;
		}
	}
}
void Board::proceed()
{
	char choice = ' ';
	do
	{
		std::cout << "Press 'y' to continue.\n";
		std::cin >> choice;
	} while (choice != 'y');
}