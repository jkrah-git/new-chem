/*
 * ChemDisplayAttrib.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#ifndef CHEMDISPLAYATTRIB_H_
#define CHEMDISPLAYATTRIB_H_
#include "PeptidePos.h"
#include "../include/gfx/GFX_Base.h"
// ---------------------------------------



// ---------------------------------------
class ChemDisplayAttrib {
	PepPosVecType	*pos;

public:
	GFX_Base	*gfx;
	int 		offsetx;
	int 		offsety;
	int 		scalex;
	int 		scaley;

	// ------
 	//----------------
  	ChemDisplayAttrib();
  	ChemDisplayAttrib(ChemDisplayAttrib *src);
  	virtual ~ChemDisplayAttrib();
  	void	init(void);
  	void	dump(void);
  	//------
	PepPosVecType	*getpos(void){ return pos; };
	void	setpos(PepPosVecType *_pos);

  	void	set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scalex, int _scaley);
  	void	setoffset(int _offsetx, int _offsety);
  	void	setscale(int sx, int sy);
  	void	cp(ChemDisplayAttrib *src) {
  		if (src!=NULL) {
  			gfx = 	  src-> gfx;
  			offsetx = src-> offsetx;
  			offsety = src-> offsety;
  			scalex = src-> scalex;
  			scaley = src-> scaley;
  			if ((pos!=NULL) &&(src-> pos!=NULL)) {
  				pos[PEPPOS_X] = src-> pos[PEPPOS_X];
  				pos[PEPPOS_Y] = src-> pos[PEPPOS_Y];
  			}
  		}
  	}

  	// get local(x,y) (ie 0,0 = centre)
  	int		getx(void);
  	int		gety(void);
  	int		getx(int offx, int posx);
  	int		gety(int offy, int posy);
  	int		getxcell(int screenx);
  	int		getycell(int screeny);
  	// get final screen(x,y)
  	int		screenx(void);
  	int		screeny(void);
  	int		screenx(int offx, int posx);
  	int		screeny(int offy, int posy);

};
//--------------------------

#endif /* CHEMDISPLAYATTRIB_H_ */
