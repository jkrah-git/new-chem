/*
 * ChemScreen.h
 *
 *  Created on: Jun 3, 2019
 *      Author: jkrah
 */
#ifndef CHEMSCREEN_H_
#define CHEMSCREEN_H_

//#include "Concentration_VM.h"
//#include "../include/gfx/GFX_Base.h"
//#include "ChemDisplayAttrib.h"

#include "ChemMenu.h"
#include "ChemDisplay.h"
//class ChemDisplay;

enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
enum SCREEN_GRID_MODE { GRID_OFF, GRID_MOLE, GRID_MENU };

//-----------------------------------------
class ChemScreen {
	// does this make a screen
	//----------
	// TODO:fix to local
	char					*title;
public:
	ChemDisplayAttrib		attrib;
	mylist<ChemMenu> 		*menu_list;
	ChemMenu				*current_menu;
	PeptidePos				curs_pos;


	// stack indexs.. (we dont store pointers here just the count)
	int						pep_index;
	int 					moles_index;
	int						conc_index;


	// if NULL then at test (curs_pos) at redraw
	Molecule				*selected_mole;
	Peptide					*selected_pep;
	bool					mouse_clicked;

	bool					waiting;
	SCREEN_WAIT_MODE		waitmode;
	SCREEN_GRID_MODE		gridmode;
	int					(*renderCB)(Concentration_CLI*, int, char**);
	int						(*waitCB)(ChemScreen*, Concentration_CLI*, ChemDisplay*);
	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);
	ChemMenu				*find_menu(const char *_title);

	const char 				*get_title(void){ return title; };
	int						set_title(const char* newtitle);
	int						istitle(const char* _title);
	//ChemMenuButton			*test_menus(PepPosVecType *screen_pos);
	ChemMenuButton			*test_menus(ChemDisplay *display);

	int						wait(Concentration_CLI *cli, ChemDisplay *display) { return wait(cli, display, false); };
	int						wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump);


	int						button_click(Concentration_CLI *cli, ChemDisplay *display);

};
//-----------------------------------------


//-----------------------------------------//-----------------------------------------
#endif /* CHEMSCREEN_H_ */
