#pragma once
#include <bitset>
#include "my_typedefs.h"
class Square
{
private:
	enum State
	{
		hidden,
		locked,
		hit,
		kill,
		unit,
		mine
	};
	std::bitset<6> state;
protected:
	uint x_pos, y_pos, cur_unit;
public:
	Square() : x_pos(0), y_pos(0), cur_unit(0) { state.set(hidden);}
	Square(uint x_pos, uint y_pos) : x_pos(0), y_pos(0), cur_unit(0) {state.set(hidden);}
	Square& get_square();
	const Square& cget_square() const;
	const uint& cget_x_pos() const;
	uint& get_x_pos();
	const uint& cget_y_pos() const;
	uint& get_y_pos();
	bool is_locked() const;
	bool is_hit() const;
	bool is_unit() const;
	bool is_hidden() const;
	bool is_mine() const;
	bool is_kill() const;
	void lock_square();
	void unlock_square();
	void unhide_square();
	void set_mine();
	void set_unit();
	void assign_unit_id(uint);
	uint cget_cur_unit_id() const;
};