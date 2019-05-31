/*
 * VMDisplay.h
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#ifndef CHEMDISPLAY_H_
#define CHEMDISPLAY_H_
// ----------------

//#include "../mylist.h"
#include "Concentration_VM.h"
#include "../include/gfx/GFX_Base.h"

// ----------------


class ChemDisplay {
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

  	//-------------------
	ChemDisplay();
	virtual ~ChemDisplay();
	void	dump();
	void	gdump();

	void	setcol(int red, int green, int blue){ 	colr = red; colg = green; colb = blue; gfx.color(colr, colg, colb); };
	void	grid(){ grid(colr, colg, colb); }
	void	grid(int red, int green, int blue);
	void	clearatt();

	void	draw_pep(Peptide *pep);
	void	draw_mole(Molecule *mole);
	void	draw_match(MoleculeMatchPos *matchpos);
	void	draw_vm(Concentration_VM *vm);



};

#endif /* CHEMDISPLAY_H_ */
