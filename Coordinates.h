#ifndef COORDINATES_H
#define COORDINATES_H

using namespace std;

class Coordinates
{
private:
	int x_cord;
	int y_cord;

public:
	Coordinates();
	void getCoordinates(int &a, int &b);
	void changeCoordinates(int a, int b);
};

#endif