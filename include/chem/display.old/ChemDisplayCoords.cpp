/*
 * ChemDisplayAttrib.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#include <stdlib.h>
#include <math.h>
#include "ChemDisplayCoords.h"
#include "debug.h"
class ChemDisplay;

/*
// ---------------------------------------
class ChemDisplayCoords {
public:
	int			posx;
	int			posy;
	int 		scalex;
	int 		scaley;
	int 		offsetx;
	int 		offsety;
 	//----------------
  	ChemDisplayCoords();
  	ChemDisplayCoords(ChemDisplayCoords *src);
  	virtual ~ChemDisplayCoords();
  	void	dump(void);
  	//------
  	int		getx(void);
  	int		gety(void);
  	int		getx(int offx, int posx);
  	int		gety(int offy, int posy);
  	int		getxcell(GFX_Base *gfx, int screenx);
  	int		getycell(GFX_Base *gfx, int screeny);
  	bool 	hit(GFX_Base *gfx);
  	bool 	hit(GFX_Base *gfx, int posx, int posy);

  	// get final screen(x,y)
  	int		screenx(GFX_Base *gfx);
  	int		screeny(GFX_Base *gfx);
  	int		screenx(GFX_Base *gfx, int offx, int posx);
  	int		screeny(GFX_Base *gfx, int offy, int posy);
};
//--------------------------
*/
ChemDisplayCoords::ChemDisplayCoords(){
	posx = 0;
	posy = 0;
	offsetx = 0;
	offsety = 0;
	scalex = 10;
	scaley = 10;
}
//--------------------------
ChemDisplayCoords::ChemDisplayCoords(ChemDisplayCoords *src) {
	posx = 0;
	posy = 0;
	offsetx = 0;
	offsety = 0;
	scalex = 10;
	scaley = 10;
	// -----
	//if (src !=NULL)	cp(src);
	if (src !=NULL)	*this = *src;
}
//--------------------------
ChemDisplayCoords::~ChemDisplayCoords() {}
//--------------------------
void ChemDisplayCoords::dump(void) {
	printf("ChemDisplayCoords[0x%zX]:",	(long unsigned int) this);
	printf(".offset[%d,%d].pos", offsetx, offsety);
	printf(".pos[%d,%d]", posx, posy);
	printf(".scale[%d,%d]", scalex, scaley);
}
//--------------------------
//--------------------------
int ChemDisplayCoords::getx(void)				{ return offsetx + (posx *scalex);	}
int ChemDisplayCoords::gety(void)				{ return offsety + (posy * scaley);	}
int ChemDisplayCoords::getx(int offx, int posx)	{ return offx + (posx *scalex);	}
int ChemDisplayCoords::gety(int offy, int posy)	{ return offy + (posy *scaley); }

//--------------------------
int ChemDisplayCoords::getxcell(GFX_Base *gfx, int screenx){
	if (gfx==NULL) return 0;

	int x = screenx - (gfx-> width/2) -offsetx;
	//PRINT("1. x=[%d]\n", x);
	float xf = x / (float)scalex;
	//PRINT("xf=[%f]\n", xf);
	x = round(xf);
	//PRINT("x=[%d]\n", x);
	return x;
}
//--------------------------
int ChemDisplayCoords::getycell(GFX_Base *gfx, int screeny){
	if (gfx==NULL) return 0;

	int y = screeny - (gfx->height/2) -offsety;
	//PRINT("1. x=[%d]\n", x);
	float yf = y / (float)scaley;
	//PRINT("xf=[%f]\n", xf);
	y = - round(yf);
	//PRINT("y=[%d]\n", y);
	return y;
}
//--------------------------
bool ChemDisplayCoords::hit(GFX_Base *gfx) {
	if (gfx==NULL) return false;
	return ( (getxcell(gfx, gfx-> xpos())==posx) &&
			 (getycell(gfx, gfx-> ypos())==posy));
}
//--------------------------

bool ChemDisplayCoords::hit(GFX_Base *gfx, int x, int y) {
	if (gfx==NULL) return false;
	return ( (getxcell(gfx, gfx-> xpos())==posx+x) &&
			 (getycell(gfx, gfx-> ypos())==posy+y));
}
//--------------------------
int ChemDisplayCoords::screenx(GFX_Base *gfx){
	if (gfx==NULL) return 0;
	return (gfx-> width/2) + getx();
}
//--------------------------
int ChemDisplayCoords::screeny(GFX_Base *gfx){
	if (gfx==NULL) return 0;
	return (gfx-> height-((gfx-> height/2) + gety()));
}
//--------------------------
int ChemDisplayCoords::screenx(GFX_Base *gfx, int offx, int posx){
	if (gfx==NULL) return 0;
	return (gfx-> width/2) + getx(offx,posx);
}
//--------------------------
int ChemDisplayCoords::screeny(GFX_Base *gfx, int offy, int posy){
	if (gfx==NULL) return 0;
	return (gfx-> height-((gfx-> height/2) + gety(offy, posy)));
}
//--------------------------

