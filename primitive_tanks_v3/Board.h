#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "Square.h"
class Board
{
private:
	static uint x_size, y_size, board_size;
	std::vector <Square> board;
public:
	Board() : board() {}
	std::vector<Square>& get_board();
	const std::vector<Square>& cget_board() const;
	void build_board();
	void display_board() const;
	const Square& cget_pos() const;
	const Square& find_square(uint, uint) const;
	bool is_accessible(Square) const;
	bool is_in_range(int, int) const;
};