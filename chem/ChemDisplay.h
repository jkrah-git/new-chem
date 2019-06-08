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

#define DISPLAY_EVENT_MOUSE1 1
#define DISPLAY_EVENT_MOUSE2 3
#define DISPLAY_EVENT_MOUSE3 2
#define DISPLAY_EVENT_MOUSEUP 4
#define DISPLAY_EVENT_MOUSEDOWN 5

#define DISPLAY_EVENT_LEFT 	81
#define DISPLAY_EVENT_RIGHT 82
#define DISPLAY_EVENT_UP	83
#define DISPLAY_EVENT_DOWN	84
#define DISPLAY_EVENT_ESC 	27

/*
	// ARROWS
	case 81:	curs_pos.dim[PEPPOS_X] --;	break;
	case 82:	curs_pos.dim[PEPPOS_Y] ++;	break;
	case 83:	curs_pos.dim[PEPPOS_X] ++;	break;
	case 84:	curs_pos.dim[PEPPOS_Y] --;	break;
	}
*/

//====================================
// ----------------
class ChemDisplay {
private:
	// does this make a screen
	ChemMenu				*add_menu(const char *_title);
	void					draw_menus(void);
	int						test_menus(int posx, int posy);
	//PeptidePos				curs_pos;
	ChemDisplayAttrib			attrib;

public:
	GFX_Base				gfx;

    // selected objects
	Concentration_VM		*core;
	// selection pointers
	Peptide					*pep;
	Molecule				*mole;
	Concentration			*conc;
	ConcentrationVolume 	*concvol;
	MoleculeMatchPos 		*matchpos;

	mylist<ChemScreen> 		*screen_list;
	ChemScreen				*current_screen;
	ChemDisplayAttrib		*getattrib(void){ return &attrib; };

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
	void	clearatt();

	void	draw_pep(Peptide *pep);
	void	draw_pep(Peptide *pep, int red, int green, int blue) { gfx.color(red, green, blue); draw_pep(pep); };
	void	draw_pep(Peptide *pep, ChemDisplayColor *col) { gfx.color(col); draw_pep(pep); };

	void	draw_mole(Molecule *mole, int r, int g, int b); // { gfx.color(red, green, blue); draw_mole(mole); };
	void	draw_mole(Molecule *mole, ChemDisplayColor *col); // { gfx.color(col); draw_mole(mole); };

	void	draw_match(MoleculeMatchPos *matchpos);
	//---- new
//	void	draw_regs(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
//	void	draw_pep(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
//	void	draw_mole(Peptide *mole, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	//---
	void	draw_vm(Concentration_VM *vm);
	void	draw_cellbox(int minx, int miny, int maxx,int maxy, const char *_title);
	void	draw_box(int minx, int miny, int maxx,int maxy){ draw_cellbox(minx, miny, maxx, maxy, NULL); };

	void 	draw_screen(ChemScreen *screen, Concentration_CLI *cli);
	int		test_screen(ChemScreen *screen, int posx, int posy);
	void 	draw_menu_border(ChemMenu *menu);
	void 	draw_menu(ChemMenu *menu);
	void 	draw_button(ChemMenuButton *button, ChemDisplayColor *col);
	//--------------
	ChemScreen *add_screen(const char* screen_title);
	ChemScreen *search_screen(const char* screen_title);



	int		XXmain(int argc, char **argv);
	int		XXwait(ChemScreen *screen);
	void	XXcurs(int red, int green, int blue);

};



#endif /* CHEMDISPLAY_H_ */
