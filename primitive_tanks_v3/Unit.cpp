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
//setters
void Unit::set_unit_id(uint id)
{
	unit_id = id;
}
