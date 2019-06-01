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

#define CHEM_DEF_COLR 100
#define CHEM_DEF_COLG 100
#define CHEM_DEF_COLB 100

// ---------------------------------------
class ChemDisplayColor {
public:
	int r;
	int g;
	int b;
	//----
	ChemDisplayColor(void){ r=CHEM_DEF_COLR; g=CHEM_DEF_COLG; b=CHEM_DEF_COLB; };
	ChemDisplayColor(int red, int green, int blue){ r=red; g=green; b=blue; };
	void	set(int red, int green, int blue){ r=red; g=green; b=blue; };
};
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
  	//------
  	void	set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scale);
  	void	setoffset(int _offsetx, int _offsety);
  	void	setpos(PepPosVecType *_pos);
  	void	setscale(int _scale);


  	int		getx(void);
  	int		gety(void);

};
//--------------------------

#endif /* CHEMDISPLAYATTRIB_H_ */
