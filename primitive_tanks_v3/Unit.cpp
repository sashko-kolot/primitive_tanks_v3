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
//setters
void Unit::set_unit_id(uint id)
{
	unit_id = id;
}
