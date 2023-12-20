#ifndef SQUARE_H
#define SQUARE_H
#include <bitset>
class Square
{
private:
	enum State
	{
		hidden,
		no_recon,
		locked,
		hit,
		kill,
		unit,
		mine,
		repair_kit,
		mask_kit,
		recon_kit,
		air_support,
		mine_clearing,
		extra_ammo
	};
	std::bitset<13> state;
protected:
	int x_pos, y_pos, cur_unit;
public:
	Square() : x_pos(0), y_pos(0), cur_unit(0) {state.set(hidden);}
	Square(int x_pos, int y_pos) : x_pos(0), y_pos(0), cur_unit(0) {state.set(hidden);}
	Square& get_square();
	const Square& cget_square() const;
	const int& cget_x_pos() const;
	int& get_x_pos();
	const int& cget_y_pos() const;
	int& get_y_pos();
	bool is_locked() const;
	bool is_hit() const;
	bool is_unit() const;
	bool is_hidden() const;
	bool is_no_recon() const;
	bool is_mine() const;
	bool is_kill() const;
	bool is_repair_kit() const;
	bool is_mask_kit() const;
	bool is_recon_kit() const;
	bool is_air_support() const;
	bool is_mine_clearing() const;
	bool is_extra_ammo() const;
	bool is_loot() const;
	void lock_square();
	void unlock_square();
	void unhide_square();
	void hide_square();
	void set_no_recon();
	void remove_no_recon();
	void set_mine();
	void remove_mine();
	void set_unit();
	void remove_unit();
	void set_repair_kit();
	void remove_repair_kit();
	void set_mask_kit();
	void remove_mask_kit();
	void set_recon_kit();
	void remove_recon_kit();
	void set_air_support();
	void remove_air_support();
	void set_mine_clearing();
	void remove_mine_clearing();
	void set_extra_ammo();
	void remove_extra_ammo();
	void set_kill();
	void assign_unit_id(int);
	void set_hit();
	int cget_cur_unit_id() const;
};
#endif SQUARE_H