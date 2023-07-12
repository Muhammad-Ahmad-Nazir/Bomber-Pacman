#ifndef GHOSTS_H
#define GHOSTS_H

#include <iostream>
//#include "util.h"
//#include "Board.h"
#include "Coordinates.h"

using namespace std;

class Ghosts : public Coordinates
{
public:
	Ghosts();
	void GetInitPinkyPosition(int& x, int& y);
	void newPinkyPosition(int& x, int& y);
	void GetInitDinkyPosition(int &x, int &y);
	void newDinkyPosition(int& x, int& y);
	void MoveGhosts();
};

#endif