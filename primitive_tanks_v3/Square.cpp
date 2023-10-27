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