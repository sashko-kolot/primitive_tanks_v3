#pragma once
#include <bitset>
#include "my_typedefs.h"
class Square
{
private:
	enum State
	{
		locked,
		hidden,
		hit,
		unit
	};
	std::bitset<4> state;
protected:
	uint x_pos, y_pos;
public:
	Square() : x_pos(0), y_pos(0), state(hidden) {}
	Square(uint x_pos, uint y_pos) : x_pos(0), y_pos(0), state(hidden) {}
	Square& get_square();
	const Square& cget_square() const;
	const uint& cget_x_pos() const;
	uint& get_x_pos();
	const uint& cget_y_pos() const;
	uint& get_y_pos();
	bool is_locked() const;
	bool is_hit() const;
	void lock_square();
};