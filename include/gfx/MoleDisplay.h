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
#include "../../chem/Concentration_VM.h"
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
	//void	open();
	void	setcol(int red, int green, int blue){ 	colr = red; colg = green; colb = blue; gfx.color(colr, colg, colb); };
	void	grid(){ grid(colr, colg, colb); }
	void	grid(int red, int green, int blue);
	void	clearatt();
	void	draw_pep(Peptide *pep);
//	void	draw_pep(Peptide *pep, Peptide *previous);
	void	draw_mole(Molecule *mole);
	void	draw_match(MoleculeMatchPos *matchpos);

	void	draw_vm(Concentration_VM *vm);

};
//--------------


#endif /* MOLEDISPLAY_H_ */
