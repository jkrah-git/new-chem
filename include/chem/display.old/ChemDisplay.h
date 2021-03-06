/*
 * VMDisplay.h
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#ifndef CHEMDISPLAY_H_
#define CHEMDISPLAY_H_
// ----------------
#include "chem/Concentration_CLI.h"
//#include "chem/Concentration_CLI.h"
#include "ChemScreen.h"
#include "Display_Command.h"
//class Display_Command;
#include "gfx/GFX_Base.h"
//#include "ListDisplay.h"

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


// template <class U> class mylist_item {
template <class T>
class NamedList {

	//		mylist_item<U>		*prev;
			mylist<T>		list;
			T				*selected_item;
};

//====================================
//class ChemDisplay;
// ----------------
class ChemDisplay {
	Concentration_CLI 		*cli;
public:
	GFX_Base				gfx;
	mylist<ChemScreen> 		screen_list;
	ChemScreen				*selected_screen;
	// user by mouseclick
	Molecule				*selected_mole;
	Peptide					*selected_pep;
	int		(*callback)(ChemDisplay *, int, char**);


	mylist<Display_Command>			display_cmdlist;

	// display_screen overrides current_screen - use to wait on non selected screen
//	ChemScreen				*display_screen;

  	//-------------------
	ChemDisplay(Concentration_CLI *_cli);
	virtual ~ChemDisplay();
	void	dump();
	void	gdump(ChemDisplayColor *col){  gfx.color(col); gdump(); };
	void	gdump();


	int		addcmd(mylist<Display_Command> *cmd_list, int 	(*op)(ChemDisplay *, int, char**), char *name);
	Concentration_CLI		*get_cli(void) { return cli; };
	void					load_commands(void);
	int		run(mylist<Display_Command> *cmd_list, int argc, char **argv);


	void	grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue);
	void	grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue, int xpos, int ypos);
	void	grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue, int xpos, int ypos, int axis, bool txt);
	void	grid(ChemDisplayCoords *screen_coords){ grid(screen_coords, 100,100,100); }
	void	grid(ChemDisplayCoords *screen_coords, int red, int green, int blue);

	//Peptide 	*draw_pep(ChemScreen *screen, Peptide *pep);
	Peptide 	*draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick, int red, int green, int blue);
	Peptide 	*draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick, ChemDisplayColor *col);
	Peptide		*draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick);

	Molecule	*draw_mole(ChemScreen *screen, ChemDisplayCoords *coords, Molecule *mole, bool mouseclick, int r, int g, int b);
	Molecule	*draw_mole(ChemScreen *screen, ChemDisplayCoords *coords, Molecule *mole, bool mouseclick, ChemDisplayColor *col);

	//int 		keyval_set_col(char *keyname, ChemDisplayColor *col);
	Molecule	*draw_match(ChemScreen *screen, ChemDisplayCoords *coords, MoleculeMatch *matchpos,  bool mouseclick);
	//---
	void		draw_vm(ChemScreen *screen, Concentration_VM *vm);
	void		draw_enz(ChemScreen *screen, ChemEnzyme *enz);
	void		draw_conc_displ(ChemScreen *screen, ChemConcDisplay *conc_display);

//	void 	draw_menu_border(ChemMenu *menu);
//	void 	draw_menu(ChemMenu *menu);
//	void 	draw_button(ChemDisplayCoords *menu_coords, ChemMenuButton *button, ChemDisplayColor *col);

	void	draw_pepdisp(ChemScreen *screen, ChemPepDisplay *pepdis, bool mouseclick);
	void	draw_moledisp(ChemScreen *screen, ChemMoleDisplay *moledis, bool mouseclick);

//	template <class T> void	draw_list(ChemScreen *screen, ListDisplay<T> *list_display, bool mouseclick);

	void	draw_peplist(ChemScreen *screen, Concentration_CLI *cli, ChemPeplistDisplay *peplist, bool mouseclick);
	void	draw_molelist(ChemScreen *screen, Concentration_CLI *cli, ChemMolelistDisplay *molelist, bool mouseclick);
	void	draw_conclist(ChemScreen *screen, Concentration_CLI *cli, ChemConclistDisplay *conclistDisplay, bool mouseclick);
	//--------------
	void	draw_title_bar(ChemScreen *screen, Concentration_CLI *cli);

	void 	draw_screen(ChemScreen *screen, Concentration_CLI *cli){ draw_screen(screen, cli, false); };
	void 	draw_screen(ChemScreen *screen, Concentration_CLI *cli, bool mouseclick);
	//--------------
	ChemScreen *add_screen(const char* screen_title);
	ChemScreen *search_screen(const char* screen_title);
	int			del_screen(ChemScreen *screen);

	void	draw_box(ChemDisplayCoords *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos);
	void	draw_box(ChemDisplayCoords *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title);
	void	draw_box(ChemDisplayCoords *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title, ChemDisplayColor *boxcol, ChemDisplayColor *txtcol);

};
// ----------------


#endif /* CHEMDISPLAY_H_ */
