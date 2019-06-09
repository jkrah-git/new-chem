/*
 * ChemDisplayAttrib.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#include <stdlib.h>
#include <math.h>
#include "ChemDisplayAttrib.h"
#include "../include/debug.h"
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
ChemDisplayAttrib::ChemDisplayAttrib(){
	scalex = 10;
	scaley = 10;
//	gfx	= NULL;
//	pos = NULL;
	init();
}
//--------------------------
ChemDisplayAttrib::ChemDisplayAttrib(ChemDisplayAttrib *src) {
	scalex = 10;
	scaley = 10;
//	gfx	= NULL;
//	pos = NULL;
	init();
	// -----
	if (src !=NULL)
		cp(src);
}
//--------------------------
ChemDisplayAttrib::~ChemDisplayAttrib() {
	// if (pos!=NULL)		free(pos);

}
//--------------------------
void ChemDisplayAttrib::init() {
	offsetx = 0;
	offsety = 0;
	//if (pos == NULL) {	pos = (PepPosVecType*) malloc(sizeof(PepPosVecType) *PepPosVecMax);	}
	//if (pos!=NULL) {		pos[PEPPOS_X] = 0;		pos[PEPPOS_Y] = 0;	}
	pos.init();

}
//--------------------------
void ChemDisplayAttrib::dump(void) {
	printf("ChemDisplayAttrib[0x%zX]:",	(long unsigned int) this);
	/*
	printf("gfx[0x%zX]:",	(long unsigned int) gfx);
	if (gfx!=NULL) {
		printf("([%d]x[%d]):", gfx->width, gfx->height);
	}
	*/
	printf(".offset[%d,%d].pos", offsetx, offsety);
	if (pos.dim==NULL) {		printf("[NULL]");	}
	else {						printf("[%d,%d]", pos.dim[PEPPOS_X], pos.dim[PEPPOS_Y]);	}
	printf(".scale[%d,%d]", scalex, scaley);
	//printf(".getxy[%d,%d]", screenx(), screeny());

}
//--------------------------
void ChemDisplayAttrib::setoffset(int _offsetx, int _offsety){	offsetx = _offsetx;	offsety = _offsety;}
void ChemDisplayAttrib::setpos(PepPosVecType *_pos){
	//if ((pos!=NULL) && (_pos!=NULL))		*pos = *_pos;
	if ((_pos==NULL)) pos.init();
	else pos = _pos;

}
void ChemDisplayAttrib::addpos(PepPosVecType *_pos){	if (_pos!=NULL)		pos = pos + _pos;}
void ChemDisplayAttrib::setscale(int sx, int sy){	scalex = sx; scaley = sy;	}
//--------------------------
void ChemDisplayAttrib::set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scalex, int _scaley){
	offsetx = _offsetx;
	offsety = _offsety;
	if (pos.dim !=NULL) pos = _pos;
	scalex = _scalex;
	scaley = _scaley;
}
// TODO normalise or protect offsets..
//--------------------------
int ChemDisplayAttrib::getx(void){
	int px = offsetx;
	if (pos.dim !=NULL)	{
		px += (pos.dim[PEPPOS_X] * scalex);
	}
	return px;
}
//--------------------------
int ChemDisplayAttrib::gety(void){
	int py = offsety;
	if (pos.dim !=NULL)	{
		py += (pos.dim[PEPPOS_Y] * scaley);
	}
	return py;
}
//--------------------------
int ChemDisplayAttrib::getx(int offx, int posx){
	return  offx + (posx *scalex);
}

//--------------------------
int ChemDisplayAttrib::gety(int offy, int posy){
	return  offy + (posy *scaley);
}


//--------------------------
int ChemDisplayAttrib::getxcell(GFX_Base *gfx, int screenx){
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
int ChemDisplayAttrib::getycell(GFX_Base *gfx, int screeny){
	if (gfx==NULL) return 0;

	int y = screeny - (gfx->height/2) -offsety;
	//PRINT("1. x=[%d]\n", x);
	float yf = y / (float)scaley;
	//PRINT("xf=[%f]\n", xf);
	y = - round(yf);
	//PRINT("x=[%d]\n", x);
	return y;


}
//--------------------------
int ChemDisplayAttrib::screenx(GFX_Base *gfx){
	if (gfx==NULL) return 0;
	return (gfx-> width/2) + getx();
}
//--------------------------
int ChemDisplayAttrib::screeny(GFX_Base *gfx){
	if (gfx==NULL) return 0;
	return (gfx-> height-((gfx-> height/2) + gety()));
}
//--------------------------
int ChemDisplayAttrib::screenx(GFX_Base *gfx, int offx, int posx){
	if (gfx==NULL) return 0;
	return (gfx-> width/2) + getx(offx,posx);
}
//--------------------------
int ChemDisplayAttrib::screeny(GFX_Base *gfx, int offy, int posy){
	if (gfx==NULL) return 0;
	return (gfx-> height-((gfx-> height/2) + gety(offy, posy)));
}
//--------------------------

