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
//class ChemMenuList;
#include "Concentration_VM.h"
#include "../include/gfx/GFX_Base.h"
#include "ChemDisplayAttrib.h"
#include "ChemMenu.h"


// ----------------
class ChemDisplay {
private:
	//void	getcol(void) { gfx.color(colr, colg, colb); };
	//void	draw_mole(Molecule *mole);

public:
	GFX_Base		gfx;
ChemDisplayAttrib	attrib;
//ChemDisplayColor	_col;
	// ------
//	int 			colr;
//	int 			colg;
//	int 			colb;
	// ------

    // selected objects
	Concentration_VM			*core;
	Peptide						*pep;
	Molecule					*mole;
	Concentration				*conc;
	ConcentrationVolume 		*concvol;
	MoleculeMatchPos 			*matchpos;
	mylist<ChemMenu> 			*menu_list;


  	//-------------------
	ChemDisplay();
	virtual ~ChemDisplay();
	void	dump();
	void	gdump();

	//void	setcol(int red, int green, int blue){ 	colr = red; colg = green; colb = blue; gfx.color(colr, colg, colb); };
//	void	grid(){ grid(col.r, col.g, col.b); }
	void	grid(){ grid(100,100,100); }
	void	grid(int red, int green, int blue);
	void	clearatt();

	void	draw_pep(Peptide *pep);
	void	draw_pep(Peptide *pep, int red, int green, int blue) { gfx.color(red, green, blue); draw_pep(pep); };
	void	draw_pep(Peptide *pep, ChemDisplayColor *col) { gfx.color(col); draw_pep(pep); };

	void	draw_mole(Molecule *mole, int r, int g, int b); // { gfx.color(red, green, blue); draw_mole(mole); };
	void	draw_mole(Molecule *mole, ChemDisplayColor *col); // { gfx.color(col); draw_mole(mole); };

	void	draw_match(MoleculeMatchPos *matchpos);
	//---- new
	void	draw_regs(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	void	draw_pep(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	void	draw_mole(Peptide *mole, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	//---
	void	draw_vm(Concentration_VM *vm);
	ChemMenu	*add_menu(const char *_title);
	void	main(void);

};
// ----------------



#endif /* CHEMDISPLAY_H_ */
