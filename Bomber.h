#ifndef BOMBER_H
#define BOMBER_H

#include "Coordinates.h"
using namespace std;

class Bomber : public Coordinates
{
public:
	Bomber();
	void GetInitBombermanPosition(int& x, int& y);
	void MoveBomberman(int x, int y);

};

#endif