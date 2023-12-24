#ifndef UNIT_H
#define UNIT_H
#include <vector>
#include <memory>
#include "Square.h"
class Unit : public Square
{
private:
	int unit_id;
	int ammo;
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
public:
	Unit() : unit_id(0), Square(x_pos, y_pos), ammo(18) {state.set(invalid);}
	Unit& get_unit();
	const Unit& cget_unit() const;
	const int& cget_unit_id() const;
	const int& cget_ammo() const;
	int& get_ammo();
	void set_unit_id(int);
	~Unit() {}
};
#endif UNIT_H