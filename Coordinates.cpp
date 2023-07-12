#include "Coordinates.h"
#include <iostream>

Coordinates::Coordinates()
{
	x_cord = 0;
	y_cord = 0;
}

void Coordinates::getCoordinates(int &a, int &b)
{
	a = x_cord;
	b = y_cord;
}

void Coordinates::changeCoordinates(int a, int b)
{
	

	x_cord += a;
	y_cord += b;
}