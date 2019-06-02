/*
 * ChemDisplayAttrib.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#include <stdlib.h>
#include "ChemDisplayAttrib.h"

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
	gfx	= NULL;
	init();
}
//--------------------------
ChemDisplayAttrib::~ChemDisplayAttrib() {}
//--------------------------
void ChemDisplayAttrib::init() {
	offsetx = 0;
	offsety = 0;
	pos = NULL;
}
//--------------------------
void ChemDisplayAttrib::dump(void) {
	printf("ChemDisplayAttrib[0x%zX]:",	(long unsigned int) this);
	printf("gfx[0x%zX]:",	(long unsigned int) gfx);
	printf(".offset[%d,%d].pos", offsetx, offsety);
	if (pos==NULL) {
		printf("[NULL]");
	} else {
		printf("[%d,%d]", pos[PEPPOS_X], pos[PEPPOS_Y]);
	}
	printf(".scale[%d,%d]", scalex, scaley);
	printf(".getxy[%d,%d]", screenx(), screeny());

}
//--------------------------
void ChemDisplayAttrib::setoffset(int _offsetx, int _offsety){	offsetx = _offsetx;	offsety = _offsety;}
void ChemDisplayAttrib::setpos(PepPosVecType *_pos){	pos = _pos;	}
void ChemDisplayAttrib::setscale(int sx, int sy){	scalex = sx; scaley = sy;	}
//--------------------------
void ChemDisplayAttrib::set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scalex, int _scaley){
	offsetx = _offsetx;
	offsety = _offsety;
	pos = _pos;
	scalex = _scalex;
	scaley = _scaley;
}
//--------------------------
int ChemDisplayAttrib::getx(void){
	int px = offsetx;
	if (pos !=NULL)	{
		px += (pos[PEPPOS_X] * scalex);
	}
	return px;
}
//--------------------------
int ChemDisplayAttrib::gety(void){
	int py = offsety;
	if (pos !=NULL)	{
		py += (pos[PEPPOS_Y] * scaley);
	}
	return py;
}
//--------------------------
int ChemDisplayAttrib::getxcell(int screenx){
	return (screenx-(gfx-> width/2))/scalex;
}
//--------------------------
int ChemDisplayAttrib::getycell(int screeny){
	return -(screeny-(gfx-> height/2))/scaley;
}
//--------------------------
int ChemDisplayAttrib::screenx(void){
	if (gfx==NULL) return 0;
	/*
	int px = (gfx-> width/2) + offsetx;
	if (pos !=NULL)	{
		px += (pos[PEPPOS_X] * scale);
	}*/

	return (gfx-> width/2) + getx();
}
//--------------------------
int ChemDisplayAttrib::screeny(void){
	if (gfx==NULL) return 0;
	/*
	int py = (gfx-> height/2) + offsety;
	if (pos !=NULL)	{
		py += (pos[PEPPOS_Y] * scale);
	}
	return (gfx-> height-py);
	*/
	return (gfx-> height-((gfx-> height/2) + gety()));

}
//--------------------------

