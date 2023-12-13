#ifndef UNIT_H
#define UNIT_H
#include <vector>
#include "Square.h"
class Unit : public Square
{
private:
	uint unit_id;
	uint ammo;
	enum State
	{
	invalid,
	repair_kit,
	mask_kit,
	recon_kit,
	air_support,
	mine_clearing,
	extra_ammo
	};
std::bitset<7> state;
std::vector<Square> reconned_squares;
public:
	Unit() : unit_id(0), Square(x_pos, y_pos), ammo(18), reconned_squares() {state.set(invalid);}
	Unit& get_unit();
	const Unit& cget_unit() const;
	const uint& cget_unit_id() const;
	const uint& cget_ammo() const;
	uint& get_ammo();
	void set_unit_id(uint);
	std::vector<Square>& get_reconned_squares();
};
#endif UNIT_H