/*
 * VMDisplay.h
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#ifndef CHEMDISPLAY_H_
#define CHEMDISPLAY_H_
// ----------------
#include "chem/Concentration_VM.h"
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


//====================================
// ----------------
class ChemDisplay {

public:
	GFX_Base				gfx;
	mylist<ChemScreen> 		screen_list;

	ChemScreen				*selected_screen;
	// display_screen overrides current_screen - use to wait on non selected screen
	ChemScreen				*display_screen;

  	//-------------------
	ChemDisplay();
	virtual ~ChemDisplay();
	void	dump();
	void	gdump(ChemDisplayColor *col){  gfx.color(col); gdump(); };
	void	gdump();

	void	grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue);
	void	grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue, int xpos, int ypos);
	void	grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue, int xpos, int ypos, int axis, bool txt);
	void	grid(ChemDisplayCoords *screen_coords){ grid(screen_coords, 100,100,100); }
	void	grid(ChemDisplayCoords *screen_coords, int red, int green, int blue);

	Peptide 	*draw_pep(ChemDisplayCoords *screen_coords, Peptide *pep);
	Molecule	*draw_mole(ChemDisplayCoords *screen_coords, Molecule *mole, int r, int g, int b);
	Molecule	*draw_mole(ChemDisplayCoords *screen_coords, Molecule *mole, ChemDisplayColor *col);
	Molecule	*draw_match(ChemDisplayCoords *screen_coords, MoleculeMatchPos *matchpos);
	//---
	void	draw_vm(ChemDisplayCoords *screen_coords, ChemScreen *screen, Concentration_VM *vm);

	void 	draw_menu_border(ChemMenu *menu);
	void 	draw_menu(ChemMenu *menu);
	void 	draw_button(ChemDisplayCoords *menu_coords, ChemMenuButton *button, ChemDisplayColor *col);
	void	draw_peplist(ChemPeplistDisplay *peplist, ChemDisplayColor *col);
	void	draw_molelist(ChemMolelistDisplay *molelist, ChemDisplayColor *col);
	//--------------
	void	draw_title_bar(ChemScreen *screen);
	void 	draw_screen(ChemScreen *screen, Concentration_CLI *cli);
	//--------------
	ChemScreen *add_screen(const char* screen_title);
	ChemScreen *search_screen(const char* screen_title);
	int			del_screen(ChemScreen *screen);

	Peptide *draw_pep(ChemDisplayCoords *screen_coords, Peptide *pep, int red, int green, int blue)	{ 		gfx.color(red, green, blue); return draw_pep(screen_coords, pep); };
	Peptide *draw_pep(ChemDisplayCoords *screen_coords, Peptide *pep, ChemDisplayColor *col)		{		 gfx.color(col); return draw_pep(screen_coords, pep); };
	void	draw_box(ChemDisplayCoords *screen_coords, int minx, int miny, int maxx,int maxy)		{ draw_box(screen_coords, minx, miny, maxx, maxy, NULL);	};
	void	draw_box(ChemDisplayCoords *screen_coords, int minx, int miny, int maxx,int maxy, const char *_title)	{ draw_box(screen_coords, minx, miny, maxx, maxy, _title, NULL);	};

	void	draw_box(ChemDisplayCoords *screen_coords, int minx, int miny, int maxx,int maxy, const char *_title, ChemDisplayColor *txtCol);
};
// ----------------


#endif /* CHEMDISPLAY_H_ */
