#pragma once
#include "Square.h"
class Unit : public Square
{
private:
	uint unit_id;
	uint ammo;
	enum State
	{
	invalid,
	};
std::bitset<4> state;
public:
	Unit() : unit_id(0), Square (x_pos, y_pos), ammo(18), state(invalid) {}
	Unit& get_unit();
	const Unit& cget_unit() const;
	const uint& cget_unit_id() const;
	void set_unit_id(uint);
};