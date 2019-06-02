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

  	// get local(x,y) (ie 0,0 = centre)
  	int		getx(void);
  	int		gety(void);
  	// get final screen(x,y)
  	int		screenx(void);
  	int		screeny(void);

};
//--------------------------

#endif /* CHEMDISPLAYATTRIB_H_ */
