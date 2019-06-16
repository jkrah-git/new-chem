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
	//PeptidePos		pos;
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
  	void	init(void);
  	void	dump(void);
  	//------
/*
  	PepPosVecType	*getpos(void){ return pos.dim; };
	void	setpos(PepPosVecType *_pos);
	void	addpos(PepPosVecType *_pos);
	void	setpos(PepPosVecType px, PepPosVecType py){
		if (pos.dim!=NULL) {
			pos.dim[PEPPOS_X]=px;
			pos.dim[PEPPOS_Y]=py;
		}
	}

	PepPosVecType	getposx(void){ 	if (pos.dim!=NULL) { return pos.dim[PEPPOS_X]; } return 0; }
	PepPosVecType	getposy(void){ 	if (pos.dim!=NULL) { return pos.dim[PEPPOS_Y]; } return 0; }
*/

  	void	set(int _offsetx, int _offsety, PepPosVecType *_pos, int _scalex, int _scaley);
  	void	setoffset(int _offsetx, int _offsety);
  	void	setscale(int sx, int sy);
/*
  	void	cp(ChemDisplayCoords *src) {
  		if (src!=NULL) {
  			offsetx = src-> offsetx;
  			offsety = src-> offsety;
  			scalex = src-> scalex;
  			scaley = src-> scaley;
  			pos = src-> pos;

  		}
  	}
*/
  	// get local(x,y) (ie 0,0 = centre)
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