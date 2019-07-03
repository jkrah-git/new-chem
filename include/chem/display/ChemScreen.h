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

//#include "ChemDisplay.h"
//#include "ChemMenu.h"
#include "ChemPepDisplay.h"
#include "ChemMoleDisplay.h"
#include "ChemConcDisplay.h"
//#include "ListDisplay.h"
#include "ChemPeplistDisplay.h"
#include "ChemMolelistDisplay.h"
#include "ChemConclistDisplay.h"

class ChemDisplay;
#include "../../MyString.h"
enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
enum SCREEN_GRID_MODE { GRID_OFF, GRID_ON };

//-----------------------------------------
class ChemScreen {
public:
	MyString				name;
	ChemDisplayCoords		coords;


	mylist<ChemPepDisplay>	pep_list;
	mylist<ChemMoleDisplay>	mole_list;
	mylist<ChemConcDisplay>	conc_list;

	//ListDisplay<ChemMoleDisplay>	new_mole_list;

 mylist<ChemPeplistDisplay>		peplist_list;
 mylist<ChemMolelistDisplay>	molelist_list;
 mylist<ChemConclistDisplay>	conclist_list;

//	mylist<ChemMenu> 		menu_list;
//	ChemMenu				*current_menu;

	//PeptidePos				curs_pos;
	ChemDisplayColor 		title_col;

	bool					waiting;
	SCREEN_WAIT_MODE		waitmode;
	SCREEN_GRID_MODE		gridmode;
	int						(*renderCB)(ChemDisplay *, ChemScreen *screen, bool mouseclick);
	int						(*waitCB)(ChemDisplay *, ChemScreen *screen);
	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
//	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);
//	ChemMenu				*find_menu(const char *_title);

//	ChemMenuButton			*test_menus(ChemDisplay *display);
	int						wait(Concentration_CLI *cli, ChemDisplay *display) { return wait(cli, display, false); };
	int						wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump);
	//mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *get_peplost_head(void){ return peplist_list.gethead(); };

	ChemPepDisplay			*add_pep(const char *_title);
	ChemPepDisplay			*find_pep(const char *_title);
	int						del_pep(const char *_title);

	ChemMoleDisplay			*find_mole(const char *_title);
	ChemMoleDisplay			*add_mole(const char *_title);
	int						del_mole(const char *_title);

	ChemConcDisplay			*add_conc(const char *_title);
	ChemConcDisplay			*find_conc(const char *_title);
	int						del_conc(const char *_title);


	ChemPeplistDisplay		*add_peplist(const char *_title);
	ChemPeplistDisplay		*find_peplist(const char *_title);
	int						del_peplist(const char *_title);

	ChemMolelistDisplay		*add_molelist(const char *_title);
	ChemMolelistDisplay		*find_molelist(const char *_title);
	int						del_molelist(const char *_title);

	ChemConclistDisplay		*add_conclist(const char *_title);
	ChemConclistDisplay		*find_conclist(const char *_title);
	int						del_conclist(const char *_title);



};
//-----------------------------------------


//-----------------------------------------//-----------------------------------------
#endif /* CHEMSCREEN_H_ */
