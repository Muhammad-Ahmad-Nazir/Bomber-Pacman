/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
/*
* Board.cpp
*
*  Created on: May 2, 2014
*      Author: Sibt ul Hussain
*/

#include "Board.h"
#include <cstdio>
const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
//here's Bomberman's crazy board

bool leftbrickdestroyed = false;
bool rightbrickdestroyed = false;
bool upperbrickdestroyed = false;
bool lowerbrickdestroyed = false;

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK, BOMB
};
// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = { "solid.png", "brick.png", "brick-green.png" };
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
* files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
			wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
			GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
	float fheight)
	/*Draws a specfic brick at given position coordinate
	* sx = position of x-axis from left-bottom
	* sy = position of y-axis from left-bottom
	* cwidth= width of displayed brick in pixels
	* cheight= height of displayed brick in pixels.
	* */
{

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
	//	glTranslatef(0, 0, 0);
	//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
				(GetRandInRange(0, 10)) < 8 ? NILL :
				(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}
}
//Constructor
Board::Board(int xsize, int ysize) 
{
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	newBomberPosition(78, 90);
	newPinkyPosition(60, 660);
	newDinkyPosition(198, 630);
	//set up board
}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
			case G_BRICK:
			case R_BRICK:
				float fwidth = (float)(xcellsize) / width * 2, fheight =
					(float)ycellsize / height * 2;
				float fx = (float)(x - 10) / width * 2 - 1, fy = (float)y
					/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				fheight);*/
				Drawbrick((BoardParts)board_array[i][j], (float)x / width - 1, (float)y / height - 1, fwidth,
					fheight);
				break;
			}
		}
	}
#else
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
					colors[SLATE_GRAY]);
				//DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
					colors[LIGHT_GREEN]);
				break;
			case R_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[RED]);
				break;
			}
		}
	}
#endif
	glPopMatrix();
}

void Board::newPinkyPosition(int x, int y)
{
	int c, d;
	int a = x;
	int b = y;

	GetInitPinkyPosition(c, d);

	c = c + a;
	d = d + b;
	c /= xcellsize;
	d /= ycellsize;
	if ((board_array[BOARD_Y - 2 - d][c]))
	{
		return;
	}
	Ghosts::changeCoordinates(a, b);
}

void Board::newDinkyPosition(int x, int y)
{
	int c, d;
	int a = x;
	int b = y;

	GetInitDinkyPosition(c, d);

	c = c + a;
	d = d + b;

	if ((board_array[BOARD_Y - 2 - d][c]))
	{
		return;
	}
	Ghosts::changeCoordinates(a, b);
}

void Board::MoveGhosts()
{
	int n1;
	int n2;

	n1 = (rand() % 4);
	n2 = (rand() % 4) + 4;

	switch (n1)
	{
	case 0:newPinkyPosition(60, 0);
		break;
	case 1:newPinkyPosition(0, 60);
		break;
	case 2:newPinkyPosition(-60, 0);
		break;
	case 3:newPinkyPosition(0, -60);
		break;
	default:
		break;
	}

	switch (n2)
	{
	case 4:newDinkyPosition(60, 0);
		break;
	case 5:newDinkyPosition(0, 60);
		break;
	case 6:newDinkyPosition(60, 0);
		break;
	case 7:newDinkyPosition(0, 60);
		break;
	default:
		break;
	}
}

void Board::newBomberPosition(int x, int y)
{
	int c, d;
	int a = x;
	int b = y;

	GetInitBombermanPosition(c, d);

	c = c + a;
	d = d + b;
	c /= xcellsize;
	d /= ycellsize;
	if ((board_array[BOARD_Y - 2 - d][c]))
	{
		return;
	}
	Bomber::changeCoordinates(a, b);
}


void Board::BombPlacement(bool placed)
{
	int x, y;
	if (placed)
	{
		for (int i = BOARD_Y - 2; i >= 0; --i)
		{
			for (int j = 0; j < BOARD_X; j++)
			{
				if (board_array[i][j] == BOMB)
				{
					return;
				}
			}
		}
		
		GetInitBombermanPosition(x, y);
		DrawCircle( x, y, 15, colors[WHITE_SMOKE]);
		if (x != 0)
		{
			y /= 60;
			x /= 60;
			board_array[BOARD_Y - 2 - y][x] = BOMB;
			return;
		}

	}
	if (!placed) {
		for (int k = BOARD_Y - 2; k > 0; --k)
		{
			for (int l = 1; l < BOARD_X; l++)
			{
				if (board_array[k][l] == BOMB) 
				{
					board_array[k][l] = NILL;
					if (board_array[k + 1][l] != S_BRICK)
					{
						board_array[k + 1][l] = NILL;
						leftbrickdestroyed = true;
					}
					if (board_array[k - 1][l] != S_BRICK)
					{
						board_array[k - 1][l] = NILL;
						rightbrickdestroyed = true;
					}
					if (board_array[k][l + 1] != S_BRICK)
					{
						board_array[k][l + 1] = NILL;
						upperbrickdestroyed = true;
					}
					if (board_array[k][l - 1] != S_BRICK)
					{
						board_array[k][l - 1] = NILL;
						lowerbrickdestroyed = true;
					}
				}
			}
		}
	}
	UpdateScore();
	cout << Score << endl;
}

void Board::UpdateScore()
{
	if (leftbrickdestroyed)
	{
		Score += 100;
		leftbrickdestroyed = false;
	}
	if (rightbrickdestroyed)
	{
		Score += 100;
		rightbrickdestroyed = false;
	}
	if (upperbrickdestroyed)
	{
		Score += 100;
		upperbrickdestroyed = false;
	}
	if (lowerbrickdestroyed)
	{
		Score += 100;
		lowerbrickdestroyed = false;
	}
}

int Board::GetScore()
{
	return Score;
}

void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

