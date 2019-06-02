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
//--------------------------
ChemDisplayAttrib::ChemDisplayAttrib() {
	offsetx = 0;
	offsety = 0;
	pos = NULL;
	scale = 30;
	gfx	= NULL;
}
//--------------------------
ChemDisplayAttrib::~ChemDisplayAttrib() {}
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
	printf(".scale[%f]", scale);
	printf(".getxy[%d,%d]", screenx(), screeny());

}
//--------------------------
void ChemDisplayAttrib::setoffset(int _offsetx, int _offsety){	offsetx = _offsetx;	offsety = _offsety;}
void ChemDisplayAttrib::setpos(PepPosVecType *_pos){	pos = _pos;	}
void ChemDisplayAttrib::setscale(int _scale){	scale = _scale;		}
//--------------------------
void ChemDisplayAttrib::set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scale){
	offsetx = _offsetx;
	offsety = _offsety;
	pos = _pos;
	scale = _scale;
}
//--------------------------
int ChemDisplayAttrib::getx(void){
	int px = offsetx;
	if (pos !=NULL)	{
		px += (pos[PEPPOS_X] * scale);
	}
	return px;
}
//--------------------------
int ChemDisplayAttrib::gety(void){
	int py = offsety;
	if (pos !=NULL)	{
		py += (pos[PEPPOS_Y] * scale);
	}
	return py;
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

