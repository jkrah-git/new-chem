/*
 * MoleDisplay.h
 *
 *  Created on: May 20, 2019
 *      Author: jkrah
 */

#ifndef MOLEDISPLAY_H_
#define MOLEDISPLAY_H_

#include "../mylist.h"
#include "../../chem/Peptide.h"
#include "../../chem/MoleculeMatchPos.h"
#include "../../chem/Molecule.h"

// todo:  fully encapsulate gfx.h
//#include "gfx.h"
#include "GFX_Base.h"

//-----------------
class MoleDisplay {
private:
	int		screenx(void);
	int		screeny(void);
	void	getcol(void) { gfx.color(colr, colg, colb); };
//	int		line_pos;

public:
	GFX_Base	gfx;
	int 		scale;
	// ------
	int 		colr;
	int 		colg;
	int 		colb;
	// ------
	int 		offsetx;
	int 		offsety;
  PepPosVecType	*pos;

	MoleDisplay();
	virtual ~MoleDisplay();
	void	dump();
	void	gdump();
	//-----------
	void	open();
	void	setcol(int red, int green, int blue) { colr = red; colg = green; colb = blue; };
	void	grid();
	void	clearatt();
//	void	cls();
	void	draw_pep(Peptide *pep);
	void	draw_mole(Molecule *mole);
	void	draw_match(MoleculeMatchPos *matchpos);

};
//--------------


#endif /* MOLEDISPLAY_H_ */
