#include "Square.h"
//get square
Square& Square::get_square()
{
	return *this;
}
const Square& Square::cget_square() const
{
	return *this;
}
//get x coordinate
uint& Square::get_x_pos()
{
	return x_pos;
}
const uint& Square::cget_x_pos() const
{
	return x_pos;
}
//get y coordinate
uint& Square::get_y_pos()
{
	return y_pos;
}
const uint& Square::cget_y_pos() const
{
	return y_pos;
}
//get current unit id
uint Square::cget_cur_unit_id() const
{
	return cur_unit;
}

 //check states
 bool Square::is_locked() const
 {
	 if (state.test(locked))
		 return true;
	 else
		 return false;
 }
 bool Square::is_hit() const 
 {
	 if (state.test(hit))
		 return true;
	 else
		 return false;
 }
 bool Square::is_unit() const
 {
	 if (state.test(unit))
		 return true;
	 else
		 return false;
 }
 bool Square::is_mine() const
 {
	 if (state.test(mine))
		 return true;
	 else
		 return false;
 }
 bool Square::is_hidden() const
 {
	 if (state.test(hidden))
		 return true;
	 else
		 return false;
 }
 bool Square::is_kill() const
 {
	 if (state.test(kill))
		 return true;
	 else
		 return false;
 }
 //lock square
 void Square::lock_square()
 {
	 state.set(locked);
 }
 //unlock square
 void Square::unlock_square()
 {
	 state.reset(locked);
 }
//unhide square
 void Square::unhide_square()
 {
	 state.reset(hidden);
 }
//set mine
 void Square::set_mine()
 {
	 state.set(mine);
 }
 //set unit
 void Square::set_unit()
 {
	 state.set(unit);
 }
 //assign current unit id to square
 void Square::assign_unit_id(uint id)
 {
	 cur_unit = id;
 }