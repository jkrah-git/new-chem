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
//#include "../include/gfx/GFX_Base.h"
#include "ChemDisplayAttrib.h"
#include "ChemMenu.h"

//class ChemScreen;
#include "ChemScreen.h"
//====================================
// ----------------
class ChemDisplay {
private:
	// does this make a screen
	ChemMenu				*add_menu(const char *_title);
	void					draw_menus(void);
	int						test_menus(int posx, int posy);
	PeptidePos				curs_pos;

public:
	GFX_Base				gfx;
ChemDisplayAttrib			attrib;

    // selected objects
	Concentration_VM		*core;
	// selection pointers
	Peptide					*pep;
	Molecule				*mole;
	Concentration			*conc;
	ConcentrationVolume 	*concvol;
	MoleculeMatchPos 		*matchpos;
	//mylist<ChemMenu> 		*menu_list;
	mylist<ChemScreen> 		*screen_list;


  	//-------------------
	ChemDisplay();
	virtual ~ChemDisplay();
	void	dump();
	void	gdump(ChemDisplayColor *col){  gfx.color(col); gdump(); };
	void	gdump();

	//void	setcol(int red, int green, int blue){ 	colr = red; colg = green; colb = blue; gfx.color(colr, colg, colb); };
//	void	grid(){ grid(col.r, col.g, col.b); }
	void	grid(){ grid(100,100,100); }
	void	grid(int red, int green, int blue);
	void	curs(int red, int green, int blue);
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
	void	draw_cellbox(int minx, int miny, int maxx,int maxy, const char *_title);
	void	draw_box(int minx, int miny, int maxx,int maxy){ draw_cellbox(minx, miny, maxx, maxy, NULL); };

	//--------------
	int		main(int argc, char **argv);

};



#endif /* CHEMDISPLAY_H_ */
