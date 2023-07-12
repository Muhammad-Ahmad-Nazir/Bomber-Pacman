/*
* Board.h
*
*  Created on: May 2, 2014
*      Author: Sibt ul Hussain
*/
#ifndef _BOARD_H_
#define _BOARD_H_

//#include <GL/glut.h>
#include <iostream>
#include "util.h"
#include "Bomber.h"
#include "Ghosts.h"

using namespace std;
class Board : public Bomber, public Ghosts{
private:

	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;
	int Score = 0;

public:

	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 8, int ysize = 8);

	~Board(void);
	void InitalizeBoard(int, int);
	//draw the board
	void Draw();

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	
	void GetInitTextPosition(int &x, int &y);

	void newPinkyPosition(int x, int y);
	void newDinkyPosition(int x, int y);
	void MoveGhosts();
	
	void newBomberPosition(int x, int y);

	void BombPlacement(bool placed);

	void UpdateScore();
	int GetScore();
	//	int GetMidx
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
