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
#include "../Concentration_VM.h"
//#include "../include/gfx/GFX_Base.h"
#include "ChemDisplayAttrib.h"
#include "ChemMenu.h"
#include "ChemPeplistDisplay.h"

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
//	ChemDisplayAttrib		attrib;

public:
	GFX_Base				gfx;

    // main VM
	Concentration_VM		*core;
	// selection pointers
	Peptide					*pep;
	Molecule				*mole;
	Concentration			*conc;
	ConcentrationVolume 	*concvol;
	MoleculeMatchPos 		*matchpos;

	mylist<ChemScreen> 		*screen_list;
	ChemScreen				*current_screen;
	// display selected displays..
	ChemScreen				*display_screen;


	//	ChemDisplayAttrib		*getattrib(void){ return &attrib; };

  	//-------------------
	ChemDisplay();
	virtual ~ChemDisplay();
	void	dump();
	void	gdump(ChemDisplayColor *col){  gfx.color(col); gdump(); };
	void	gdump();

	void	grid_axis(ChemDisplayAttrib *grid_attrib, int red, int green, int blue);
	void	grid_axis(ChemDisplayAttrib *grid_attrib, int red, int green, int blue, int xpos, int ypos);
	void	grid_axis(ChemDisplayAttrib *grid_attrib, int red, int green, int blue, int xpos, int ypos, int axis, bool txt);

	void	grid(ChemDisplayAttrib *screen_attrib){ grid(screen_attrib, 100,100,100); }
	void	grid(ChemDisplayAttrib *screen_attrib, int red, int green, int blue);

	Peptide 	*draw_pep(ChemDisplayAttrib *screen_attrib, Peptide *pep);
	Molecule	*draw_mole(ChemDisplayAttrib *screen_attrib, Molecule *mole, int r, int g, int b);
	Molecule	*draw_mole(ChemDisplayAttrib *screen_attrib, Molecule *mole, ChemDisplayColor *col);
	Molecule	*draw_match(ChemDisplayAttrib *screen_attrib, MoleculeMatchPos *matchpos);
	//---
	void	draw_vm(ChemDisplayAttrib *screen_attrib, ChemScreen *screen, Concentration_VM *vm);
	void 	draw_menu_border(ChemMenu *menu);
	void 	draw_menu(ChemMenu *menu);
	void 	draw_button(ChemDisplayAttrib *menu_attrib, ChemMenuButton *button, ChemDisplayColor *col);
	void	draw_peplist(ChemPeplistDisplay *peplist, ChemDisplayColor *col);

	void	draw_title_bar(ChemScreen *screen);
	void 	draw_screen(ChemScreen *screen, Concentration_CLI *cli);
	//--------------
	ChemScreen *add_screen(const char* screen_title);
	ChemScreen *search_screen(const char* screen_title);
	int			del_screen(ChemScreen *screen);

	//---- header defined
	Peptide *draw_pep(ChemDisplayAttrib *screen_attrib, Peptide *pep, int red, int green, int blue)	{ 		gfx.color(red, green, blue); return draw_pep(screen_attrib, pep); };
	Peptide *draw_pep(ChemDisplayAttrib *screen_attrib, Peptide *pep, ChemDisplayColor *col)		{		 gfx.color(col); return draw_pep(screen_attrib, pep); };

	void	draw_box(ChemDisplayAttrib *screen_attrib, int minx, int miny, int maxx,int maxy)
	{ draw_box(screen_attrib, minx, miny, maxx, maxy, NULL);	};
	void	draw_box(ChemDisplayAttrib *screen_attrib, int minx, int miny, int maxx,int maxy, const char *_title)
	{ draw_box(screen_attrib, minx, miny, maxx, maxy, _title, NULL);	};

	void	draw_box(ChemDisplayAttrib *screen_attrib, int minx, int miny, int maxx,int maxy, const char *_title, ChemDisplayColor *txtCol);




};



#endif /* CHEMDISPLAY_H_ */
