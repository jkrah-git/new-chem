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
#include "ChemPeplistDisplay.h"
#include "ChemMolelistDisplay.h"
class ChemDisplay;
#include "../../MyString.h"
enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
enum SCREEN_GRID_MODE { GRID_OFF, GRID_MOLE, GRID_MENU };

//-----------------------------------------
class ChemScreen {
public:
	MyString				name;
	ChemDisplayCoords		coords;

 mylist<ChemPeplistDisplay>	peplist_list;
 mylist<ChemMolelistDisplay>	molelist_list;
	mylist<ChemMenu> 		menu_list;

	PeptidePos				curs_pos;
	ChemDisplayColor 		title_col;

	ChemMenu				*current_menu;
	Molecule				*selected_mole;
	Peptide					*selected_pep;
	bool					mouse_clicked;

	bool					waiting;
	SCREEN_WAIT_MODE		waitmode;
	SCREEN_GRID_MODE		gridmode;
	int						(*renderCB)(Concentration_CLI*, int, char**);
	int						(*waitCB)(ChemScreen*, Concentration_CLI*, ChemDisplay*);
	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);
	ChemMenu				*find_menu(const char *_title);

	ChemMenuButton			*test_menus(ChemDisplay *display);
	int						wait(Concentration_CLI *cli, ChemDisplay *display) { return wait(cli, display, false); };
	int						wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump);
	//mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *get_peplost_head(void){ return peplist_list.gethead(); };

	ChemPeplistDisplay		*add_peplist(const char *_title);
	ChemPeplistDisplay		*find_peplist(const char *_title);
	int						del_peplist(const char *_title);

	ChemMolelistDisplay		*add_molelist(const char *_title);
	ChemMolelistDisplay		*find_molelist(const char *_title);
	int						del_molelist(const char *_title);



};
//-----------------------------------------


//-----------------------------------------//-----------------------------------------
#endif /* CHEMSCREEN_H_ */
