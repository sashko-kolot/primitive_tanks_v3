#include "Unit.h"
//getters
Unit& Unit::get_unit()
{
	return *this;
}
const Unit& Unit::cget_unit() const
{
	return *this;
}
const uint& Unit::cget_unit_id() const
{
	return unit_id;
}
const uint& Unit::cget_ammo() const
{
	return ammo;
}
uint& Unit::get_ammo()
{
	return ammo;
}
std::vector<Square>& Unit::get_reconned_squares()
{
	return reconned_squares;
}
//setters
void Unit::set_unit_id(uint id)
{
	unit_id = id;
}
