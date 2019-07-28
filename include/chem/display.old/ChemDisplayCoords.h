/*
 * ChemDisplayAttrib.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#ifndef CHEMDISPLAYATTRIB_H_
#define CHEMDISPLAYATTRIB_H_
#include "../PeptidePos.h"
#include "../../gfx/GFX_Base.h"
// ---------------------------------------



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

#endif /* CHEMDISPLAYATTRIB_H_ */
