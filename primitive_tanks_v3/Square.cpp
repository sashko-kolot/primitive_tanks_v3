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
 //remove mine
 void Square::remove_mine()
 {
	 state.reset(mine);
 }
 //set unit
 void Square::set_unit()
 {
	 state.set(unit);
 }
 //remove unit
 void Square::remove_unit()
 {
	 state.reset(unit);
 }
 //loot states
 //loot - repair kit
 void Square::set_repair_kit()
 {
	 state.set(repair_kit);
 }
 void Square::remove_repair_kit()
 {
	 state.reset(repair_kit);
 }
 bool Square::is_repair_kit() const
 {
	 if (state.test(repair_kit))
		 return true;
	 else
		 return false;
 }
 //loot - mask kit
 void Square::set_mask_kit()
 {
	 state.set(mask_kit);
 }
 void Square::remove_mask_kit()
 {
	 state.reset(mask_kit);
 }
 bool Square::is_mask_kit() const
 {
	 if (state.test(mask_kit))
		 return true;
	 else
		 return false;
 }
 //loot - recon kit
 void Square::set_recon_kit()
 {
	 state.set(recon_kit);
 }
 void Square::remove_recon_kit()
 {
	 state.reset(recon_kit);
 }
 bool Square::is_recon_kit() const
 {
	 if (state.test(recon_kit))
		 return true;
	 else
		 return false;
 }
 //loot - air support
 void Square::set_air_support()
 {
	 state.set(air_support);
 }
 void Square::remove_air_support()
 {
	 state.reset(air_support);
 }
 bool Square::is_air_support() const
 {
	 if (state.test(air_support))
		 return true;
	 else
		 return false;
 }
 //loot - mine clearing
 void Square::set_mine_clearing()
 {
	 state.set(mine_clearing);
 }
 void Square::remove_mine_clearing()
 {
	 state.reset(mine_clearing);
 }
 bool Square::is_mine_clearing() const
 {
	 if (state.test(mine_clearing))
		 return true;
	 else
		 return false;
 }
 //loot - extra ammo
 void Square::set_extra_ammo()
 {
	 state.set(extra_ammo);
 }
 void Square::remove_extra_ammo()
 {
	 state.reset(extra_ammo);
 }
 void Square::set_kill()
 {
	 state.set(kill);
 }
 bool Square::is_extra_ammo() const
 {
	 if (state.test(extra_ammo))
		 return true;
	 else
		 return false;
 }
 // is loot checker
 bool Square::is_loot() const
 {
	 if (is_repair_kit() || is_mask_kit() || is_recon_kit() || is_air_support() || is_mine_clearing() || is_extra_ammo())
		 return true;
	 else
		 return false;
 }
 //assign current unit id to square
 void Square::assign_unit_id(uint id)
 {
	 cur_unit = id;
 }