#include "Player.h"
//get units
std::vector<Unit>& Player::get_my_units()
{
	return my_units;
}
//build units
void Player::build_units()
{
	for (uint i = 0; i < number_of_units; ++i)
	{
		Unit unit;
		unit.set_unit_id(i + 1);
		get_my_units().push_back(unit);
	}
}