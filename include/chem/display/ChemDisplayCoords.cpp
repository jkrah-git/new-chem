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
class ChemDisplayAttrib {

public:
	int 		offsetx;
	int 		offsety;
  PepPosVecType	*pos;
	float 		scale;
	GFX_Base	*gfx;
	// ------
 	//----------------
  	ChemDisplayAttrib();
  	virtual ~ChemDisplayAttrib();
  	void	dump(void);
  	//------
  	void	set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scale);
  	void	setoffset(int _offsetx, int _offsety);
  	void	setpos(PepPosVecType *_pos);
  	void	setscale(int _scale);


  	int		getx(void);
  	int		gety(void);

};
//--------------------------


 */
ChemDisplayCoords::ChemDisplayCoords(){
	scalex = 10;
	scaley = 10;
//	gfx	= NULL;
//	pos = NULL;
	init();
}
//--------------------------
ChemDisplayCoords::ChemDisplayCoords(ChemDisplayCoords *src) {
	scalex = 10;
	scaley = 10;
//	gfx	= NULL;
//	pos = NULL;
	init();
	// -----
	//if (src !=NULL)	cp(src);
	if (src !=NULL)	*this = *src;
}
//--------------------------
ChemDisplayCoords::~ChemDisplayCoords() {
	// if (pos!=NULL)		free(pos);

}
//--------------------------
void ChemDisplayCoords::init() {
	posx = 0;
	posy = 0;
	offsetx = 0;
	offsety = 0;

	//if (pos == NULL) {	pos = (PepPosVecType*) malloc(sizeof(PepPosVecType) *PepPosVecMax);	}
	//if (pos!=NULL) {		pos[PEPPOS_X] = 0;		pos[PEPPOS_Y] = 0;	}
	//pos.init();

}
//--------------------------
void ChemDisplayCoords::dump(void) {
	printf("ChemDisplayCoords[0x%zX]:",	(long unsigned int) this);
	/*
	printf("gfx[0x%zX]:",	(long unsigned int) gfx);
	if (gfx!=NULL) {
		printf("([%d]x[%d]):", gfx->width, gfx->height);
	}
	*/
	printf(".offset[%d,%d].pos", offsetx, offsety);
	//if (pos.dim==NULL) {		printf("[NULL]");	}
	//else {						printf("[%d,%d]", pos.dim[PEPPOS_X], pos.dim[PEPPOS_Y]);	}
	printf(".pos[%d,%d]", posx, posy);
	printf(".scale[%d,%d]", scalex, scaley);
	//printf(".getxy[%d,%d]", screenx(), screeny());

}
//--------------------------
/*
void ChemDisplayCoords::setoffset(int _offsetx, int _offsety){	offsetx = _offsetx;	offsety = _offsety;}
void ChemDisplayCoords::setpos(PepPosVecType *_pos){
	//if ((pos!=NULL) && (_pos!=NULL))		*pos = *_pos;
	if ((_pos==NULL)) pos.init();
	else pos = _pos;

}
void ChemDisplayCoords::setscale(int sx, int sy){	scalex = sx; scaley = sy;	}
//--------------------------
void ChemDisplayCoords::addpos(PepPosVecType *_pos){	if (_pos!=NULL)		pos = pos + _pos;}
//--------------------------
void ChemDisplayCoords::set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scalex, int _scaley){
	offsetx = _offsetx;
	offsety = _offsety;
	//if (pos.dim !=NULL) pos = _pos;
	scalex = _scalex;
	scaley = _scaley;
}
*/
// TODO normalise or protect offsets..
//--------------------------
int ChemDisplayCoords::getx(void){
	int px = offsetx + (posx *scalex);
	//if (pos.dim !=NULL)	{	px += (pos.dim[PEPPOS_X] * scalex);	}

	return px;
}
//--------------------------
int ChemDisplayCoords::gety(void){
	int py = offsety + (posy * scaley);
	//if (pos.dim !=NULL)	{		py += (pos.dim[PEPPOS_Y] * scaley);	}
	return py;
}
//--------------------------
int ChemDisplayCoords::getx(int offx, int posx){
	return  offx + (posx *scalex);
}

//--------------------------
int ChemDisplayCoords::gety(int offy, int posy){
	return  offy + (posy *scaley);
}


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

