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
const int& Unit::cget_unit_id() const
{
	return unit_id;
}
const int& Unit::cget_ammo() const
{
	return ammo;
}
int& Unit::get_ammo()
{
	return ammo;
}
//setters
void Unit::set_unit_id(int id)
{
	unit_id = id;
}
