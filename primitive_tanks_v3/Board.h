#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include<memory>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include "Square.h"
class Board
{
private:
	static int x_size, y_size, board_size;
	std::vector <Square> board;
public:
	Board() : board() {}
	std::vector<Square>& get_board();
	const std::vector<Square>& cget_board() const;
	void build_board();
	void display_board() const;
	Square& get_pos();
	Square& find_square(int, int);
	bool is_accessible(Square&);
	bool is_in_range(int, int) const;
	void locker(Square&);
	void unlocker(Square&);
	void recon_unhide(Square&);
	void recon_hide(Square&);
	void proceed();
};
#endif BOARD_H