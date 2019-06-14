/*
 * VMDisplay.cpp
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#include "ChemDisplay.h"
//#include "ChemMenuList.h"
//#define  DISPLAY_FONT_HEIGHT 10
/*
// ----------------
class ChemDisplay {
private:
	ChemMenu				*add_menu(const char *_title);
	void					draw_menus(void);
	int						test_menus(int posx, int posy);

public:
	GFX_Base				gfx;
	mylist<ChemScreen> 		*screen_list;
	ChemScreen				*current_screen;
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

	void	draw_title_bar(ChemScreen *screen);
	void 	draw_screen(ChemScreen *screen, Concentration_CLI *cli);
	//--------------
	ChemScreen *add_screen(const char* screen_title);
	ChemScreen *search_screen(const char* screen_title);
	int			del_screen(ChemScreen *screen);
	void		draw_box(ChemDisplayCoords *screen_coords, int minx, int miny, int maxx,int maxy, const char *_title, ChemDisplayColor *txtCol);
};
// ----------------
 */
//-------------------------------
ChemDisplay::ChemDisplay() {

	gfx.title = "NewChem";
	gfx.width = 1000;
	gfx.height = 800;

	selected_screen = NULL;
	display_screen = NULL;

	screen_list = (mylist<ChemScreen>*) malloc(sizeof(mylist<ChemScreen>));
	if (screen_list!=NULL) {
		screen_list->init();
	}

}
//-------------------------------
ChemDisplay::~ChemDisplay() {
	if (screen_list!=NULL) free(screen_list);
	screen_list = NULL;
}
//-------------------------------
void ChemDisplay::dump() {

	printf("ChemDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d]\n",	gfx.width, gfx.height);

	printf("screen_list=>");
	screen_list->dump();
}
//-------------------------------
void ChemDisplay::gdump() {
	char msg[256];

	sprintf(msg, "ChemDisplay[0x%zX][%s].Screen[0x%zX].size[%d,%d]",	(long unsigned int) this,
			gfx.title,
			(long unsigned int) selected_screen,
			gfx.width, gfx.height);

	gfx.printg(msg);



}
//-------------------------------
//void ChemDisplay::XXcurs(int red, int green, int blue){
//	PRINT("curs=[%d,%d]\n", curs_pos.dim[0], curs_pos.dim[1]);
//	draw_box(curs_pos.dim[0], curs_pos.dim[1], curs_pos.dim[0], curs_pos.dim[1]);}
//-------------------------------
void ChemDisplay::grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue) {
	grid_axis(grid_coords, red, green, blue, 0, 0, 3, false);
};
//-------------------------------
void ChemDisplay::grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue, int xpos, int ypos) {
	grid_axis(grid_coords, red, green, blue, xpos, ypos, 3, false);
};
void ChemDisplay::grid_axis(ChemDisplayCoords *grid_coords, int red, int green, int blue, int xpos, int ypos, int axis, bool txt){


	//PRINT("== pos[%d,%d]axis[%d] ==\n", xpos, ypos, axis);
	if (grid_coords==NULL) return;
	/*
	PepPosVecType	*gridpos = grid_coords-> getpos();
	if (gridpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return;	}

	ChemDisplayCoords display_coords(grid_coords);
	PepPosVecType	*display_pos = display_coords.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}

	display_pos[PEPPOS_X] = gridpos[PEPPOS_X] + xpos;
	display_pos[PEPPOS_Y] = gridpos[PEPPOS_Y] + ypos;
	*/

	ChemDisplayCoords display_coords(grid_coords);

	display_coords.posx = grid_coords->posx + xpos;
	display_coords.posy = grid_coords->posy + ypos;


	int px = display_coords.screenx(&gfx);
	int py = display_coords.screeny(&gfx);

	gfx.color(red, green, blue);
	if ((axis==0) || (axis>1)) {
		gfx.color(red, green, blue);
		gfx.line(px ,0, px, gfx.height);

		if (txt) {
			char num[16];
			sprintf(num, "%d", xpos);
			gfx.color(100, 100, 10);
			gfx.text(num, px, gfx.height -10);
		}

	}
	if ((axis==1) || (axis>1)) {
		gfx.color(red, green, blue);
		gfx.line(0, py, gfx.width, py);

		if (txt) {
			char num[16];
			sprintf(num, "%d", ypos);
			gfx.color(100, 100, 10);
			gfx.text(num, gfx.width - 10, py);
		}
	}


}
//-------------------------------
void ChemDisplay::grid(ChemDisplayCoords *grid_coords, int red, int green, int blue){

	if (grid_coords==NULL) return;
//	PepPosVecType	*gridpos = grid_coords-> getpos();
//	if (gridpos==NULL) {		PRINT("ERR: grid_coords NULL pos\n");		return;	}

//	ChemDisplayCoords display_coords(grid_coords);
//	PepPosVecType	*display_pos = display_coords.getpos();
//	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}


	int x_steps = (gfx.width / grid_coords-> scalex)/2;
	int y_steps = (gfx.height / grid_coords-> scaley)/2;
	//PRINT("Grid <BREAK>\n"); return;
	int xinc = x_steps/20; if (xinc<1) xinc=1;
	int yinc = y_steps/20; if (yinc<1) yinc=1;

	/*
	for (int x=(-x_steps - gridpos[PEPPOS_X]); x < (x_steps - gridpos[PEPPOS_X]); x+= xinc) {
		grid_axis(grid_coords, red, green, blue, x, 0, 0, true);
	}

	for (int y=(-y_steps - gridpos[PEPPOS_Y]); y< (y_steps - gridpos[PEPPOS_Y]); y+= yinc) {
		grid_axis(grid_coords, red, green, blue, 0, y, 1, true);
	}
	*/
	for (int x=(-x_steps - grid_coords-> posx); x < (x_steps -grid_coords-> posx); x+= xinc) {
		grid_axis(grid_coords, red, green, blue, x, 0, 0, true);
	}

	for (int y=(-y_steps - grid_coords-> posy); y< (y_steps - grid_coords-> posy); y+= yinc) {
		grid_axis(grid_coords, red, green, blue, 0, y, 1, true);
	}



	gfx.flush();

}
//-------------------------------
Peptide *ChemDisplay::draw_pep(ChemDisplayCoords *screen_coords, Peptide *pep){
	if ((screen_coords==NULL)||(pep==NULL)) return NULL;

	PepPosVecType  	*pep_pos = pep->getpos();
	if (pep_pos==NULL) return NULL;

	/*
	// --------------
	PepPosVecType	*oldpos = screen_coords-> getpos();
	if (oldpos==NULL) {		PRINT("ERR: screen_coords NULL pos\n");		return NULL;	}

	ChemDisplayCoords display_coords(screen_coords);

	//PRINT("display_coords =>");	display_coords.dump();
	PepPosVecType	*display_pos = display_coords.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return NULL;	}
	// --------------

	display_pos[PEPPOS_X] += pep_pos[PEPPOS_X];
	display_pos[PEPPOS_Y] += pep_pos[PEPPOS_Y];
	*/

	ChemDisplayCoords display_coords(screen_coords);
	//-------------------
	display_coords.posx += pep_pos[PEPPOS_X];
	display_coords.posy += pep_pos[PEPPOS_Y];

	int x = display_coords.screenx(&gfx);
	int y = display_coords.screeny(&gfx);

	int sx = display_coords.scalex/2;
	int sy = display_coords.scaley/2;

	gfx.box(x,y,sx, sy, NULL);

	int tx = sx/2;
	int ty = sy/2;
	switch (pep-> getrot()) {
	case 0:
		gfx.line(x-tx, y+sy, x, y+ty);
		gfx.line(x+tx, y+sy, x, y+ty);
		break;
	case 1:
		gfx.line(x-sx, y-ty, x-tx, y);
		gfx.line(x-sx, y+ty, x-tx, y);
		break;
	case 2:
		gfx.line(x-tx, y-sy, x, y-ty);
		gfx.line(x+tx, y-sy, x, y-ty);
		break;
	case 3:
		gfx.line(x+sx, y-ty, x+tx, y);
		gfx.line(x+sx, y+ty, x+tx, y);
		break;
	}


	char str[64];
	sprintf(str, "0x%x", pep-> get());
	gfx.color(200,200,200);
	gfx.text(str,x-gfx.line_height/2,y+gfx.line_height/2);

	// list pep deails also
	sprintf(str, "sig[0x%x].pos[%d,%d].rot[%d]", pep-> get(), pep->pos.dim[PEPPOS_X], pep->pos.dim[PEPPOS_Y], pep->rot);
	gfx.printg(str);

	//-------------
	// (restore pos)
	//attrib.pos = saved_pos;
	gfx.flush();
	//-------------------
	// test cursor pos...
	Peptide *hit = NULL;

	if ((display_screen!=NULL) &&
		(display_screen->mouse_clicked) &&
//		(display_pos[PEPPOS_X] == current_screen->curs_pos.dim[PEPPOS_X]) &&
//		(display_pos[PEPPOS_Y] == current_screen->curs_pos.dim[PEPPOS_Y])) {
		(display_coords.posx == display_screen->curs_pos.dim[PEPPOS_X]) &&
		(display_coords.posy == display_screen->curs_pos.dim[PEPPOS_Y])) {


		hit = pep;
		if (display_screen->selected_pep==NULL) {
			display_screen->selected_pep = hit;
		}
	}

	return hit;
}
//-------------------------------
Molecule *ChemDisplay::draw_mole(ChemDisplayCoords *screen_coords, Molecule *mole, int r, int g, int b){
	if (screen_coords==NULL) return NULL;
	ChemDisplayColor col(r,g,b);
	return draw_mole(screen_coords, mole, &col);
}
//-------------------------------
/*
//-------------------
	// test cursor pos...
	Peptide *hit = NULL;
	if ((current_screen!=NULL) &&
		(display_pos[PEPPOS_X] == current_screen->curs_pos.dim[PEPPOS_X]) &&
		(display_pos[PEPPOS_Y] == current_screen->curs_pos.dim[PEPPOS_Y])) {
		hit = pep;
		if (current_screen->selected_pep==NULL) {
			current_screen->selected_pep = hit;
		}
	}
	//-------------------

 */

Molecule *ChemDisplay::draw_mole(ChemDisplayCoords *screen_coords, Molecule *mole, ChemDisplayColor *col){
	if (screen_coords==NULL) return NULL;

	char msg[128];
	sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) mole);
	gfx.printg(msg);
	if (mole==NULL) return NULL;

	//PRINT("======== screen_coords :"); 	screen_coords-> dump(); NL
	//-------------------
	// test cursor pos...

	Molecule *hit = NULL;
	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){

		Peptide *pep = draw_pep(screen_coords, current_item-> item, col);
		if (pep!=NULL) { hit = mole; }
		//---
		current_item = current_item-> next;
	}

	if ((display_screen!=NULL) &&
		(display_screen->mouse_clicked) &&
		(hit!=NULL)) {
		if (display_screen->selected_mole==NULL) {
			display_screen->selected_mole = hit;
		}
		return hit;
	}
	return NULL;


}

//-------------------------------
Molecule *ChemDisplay::draw_match(ChemDisplayCoords *screen_coords, MoleculeMatchPos *matchpos){
	if (screen_coords==NULL) return NULL;
	// --------------
/*
	char msg[128];
	sprintf(msg, "Match[0x%zX]",	(long unsigned int) mole);
	gfx.printg(msg);
	*/
	if (matchpos==NULL) return NULL;


	ChemDisplayColor m1_col(0, 100, 0);
	ChemDisplayColor rot_col(100, 0, 0);
	ChemDisplayColor item_col(0, 0, 200);


	char str[128];
	sprintf(str, "Match[0x%zX], M1[0x%zX]->M2[0x%zX], Pos[%d,%d],Rot=[%d]. Box[%d,%d][%d,%d]",
			(long unsigned int) matchpos,
			(long unsigned int) matchpos->getM1(),
			(long unsigned int) matchpos->getM2(),

			matchpos-> current_pos.dim[PEPPOS_X],
			matchpos-> current_pos.dim[PEPPOS_Y],
			matchpos-> rotation,

			matchpos-> start_pos.dim[PEPPOS_X],
			matchpos-> start_pos.dim[PEPPOS_Y],
			matchpos-> end_pos.dim[PEPPOS_X],
			matchpos-> end_pos.dim[PEPPOS_Y]);
	gfx.printg(str);

	Molecule *hit = NULL;
	Molecule *mole = NULL;


	// -------------- M1
	if (matchpos-> getM1()!=NULL) {
		gfx.color(&m1_col);
		gfx.cprintg((const char*) "M1");

		mole = draw_mole(screen_coords, matchpos-> getM1(), &m1_col);
		if ((mole!=NULL) && (hit==NULL)) { hit = mole; }
	}

	// ------------------- ROTMOLE
	if ((matchpos-> rotmole != NULL) && (matchpos-> rotmole-> pep_list.gethead() !=NULL)) {
		gfx.color(&rot_col);
		gfx.cprintg("rotemole");
//		attrib.pos = matchpos-> current_pos.dim;
//		draw_mole(matchpos-> rotmole, &rot_col);

		ChemDisplayCoords display_coords(screen_coords);
	//	display_coords.addpos(matchpos-> current_pos.dim);
		display_coords.posx += matchpos-> current_pos.dim[PEPPOS_X];
		display_coords.posy += matchpos-> current_pos.dim[PEPPOS_Y];
		// PRINT("screen_coords = "); screen_coords-> dump(); NL
		// PRINT("display_coords = "); display_coords.dump(); NL


		mole = draw_mole(&display_coords, matchpos-> rotmole, &rot_col);
		if ((mole!=NULL) && (hit==NULL)) { hit = mole; }
	}

	if (matchpos-> get_test_item()!=NULL) {
		gfx.color(&item_col);
		gfx.cprintg("test_item");
		//attrib.pos = matchpos-> current_pos.dim;
		//draw_pep(matchpos-> get_test_item()-> item);
		//display_coords.setpos(matchpos-> current_pos.dim);

		ChemDisplayCoords display_coords(screen_coords);
//		display_coords.addpos(matchpos-> current_pos.dim);
		display_coords.posx += matchpos-> current_pos.dim[PEPPOS_X];
		display_coords.posy += matchpos-> current_pos.dim[PEPPOS_Y];

		draw_pep(&display_coords, matchpos-> get_test_item()-> item);

	}
	//---------------
	gfx.flush();
	return hit;
}
//void draw_pepstack_row(mylist<Peptide>  *pep_list, int index, int width, int posx, posy){}
//-------------------------------
void ChemDisplay::draw_vm(ChemDisplayCoords *screen_coords, ChemScreen *screen, Concentration_VM *vm){
	if (screen_coords==NULL) return;
	if (screen==NULL) return;
	if (vm==NULL) return;

	char str[128];
	sprintf(str, "REGS: Pep[0x%zX] Mole[0x%zX] Conc[0x%zX] Vol[0x%zX]",
			(long unsigned int) vm->pep,
			(long unsigned int) vm->mole,
			(long unsigned int) vm->conc,
			(long unsigned int) vm->concvol);
	gfx.printg(str);

	sprintf(str, "STACKS: Pep[%d] Mole[%d] Conc[%d]", vm->peptide_stack.count(), vm->molecule_stack.count(), vm->concentration_stack.count());
	gfx.printg(str);


	// mylist<ChemPeplistDisplay>	peplist_list;

	/*
	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = screen-> peplist_list.gethead();
	while ((peplist_item!=NULL)&&(peplist_item-> item !=NULL)) {

		PRINT("peplist_item found..\n");
		peplist_item-> dump(); NL
		//------------
		peplist_item = peplist_item->next;
	}
	*/



	/*
	if (peplist_item==NULL) {
		PRINT("creating new peplist..\n");
		peplist_item =  screen-> peplist_list.add();
		if (peplist_item==NULL) {
			PRINT("creating new peplist failed..\n"); return;
		}
		PRINT("create new peplist ok..\n");
		peplist_item->item =
	}
	PRINT("peplist_item :\n"); 	peplist_item-> dump(); NL
*/

/*
	// 10 x 5 cells (top left)
	int colums = 4;
	int rows = 5;
	int posx = -1;
	int posy = 6;
	Peptide 	*hit = NULL;


	mylist<Peptide>::mylist_item<Peptide>  *pep_item;
	pep_item = vm-> peptide_stack.offset(screen-> pep_index);
	if (pep_item==NULL) {
		screen-> pep_index = 0;
		pep_item = vm-> peptide_stack.gethead();
	}

	for (int y=0; y<rows; y++) {
		for (int x=0; x<colums; x++) {
			int px = posx + x;
			int py = posy - y;

			PeptidePos p;
			p.dim[PEPPOS_X] = px;
			p.dim[PEPPOS_X] = px;
			ChemDisplayAttrib display_coords(screen_coords);
			display_coords.addpos(p.dim);


			char sig[16];
			//-----------------------------
			if ((pep_item==NULL)||(pep_item-> item==NULL)) {
				// draw NULL - void	draw_box(ChemDisplayAttrib *screen_coords, int minx, int miny, int maxx,int maxy, const char *_title);
				sprintf(sig, "-");
				draw_box(&display_coords, px, py, px, py, sig);
			} else {
				//sprintf(sig, "%d", pep_item->item->get());
				hit = draw_pep(&display_coords, pep_item-> item);
				pep_item = pep_item->next;
			}

		} // --next x
	} // -- next y
*/
	//---------------
	gfx.flush();
}
//###############################################################################
//void ChemDisplay::draw_box(int min_xpos, int min_ypos, int max_xpos,int max_ypos) {
// draw
//void ChemDisplay::draw_box(ChemDisplayAttrib *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title){

void ChemDisplay::draw_box(ChemDisplayCoords *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title, ChemDisplayColor *txtCol){
	if (screen_coords==NULL) return;



	ChemDisplayCoords draw_coords(screen_coords);
	draw_coords.offsetx = screen_coords->getx();
	draw_coords.offsety = screen_coords->gety();

	int minx = draw_coords. screenx(&gfx, draw_coords. offsetx, min_xpos);// - attrib.scalex/2;
	int maxx = draw_coords. screenx(&gfx, draw_coords. offsetx, max_xpos);// + attrib.scalex/2;
	// screen y cords inverted
	int maxy = draw_coords. screeny(&gfx, draw_coords. offsety, min_ypos);// - attrib.scaley/2;
	int miny = draw_coords. screeny(&gfx, draw_coords. offsety, max_ypos);// + attrib.scaley/2;
	//PRINT("==: [%d,%d]->[%d,%d]\n", minx, miny, maxx, maxy);


	int px = minx+((maxx-minx)/2);
	int py = miny+((maxy-miny)/2);
	//PRINT("scale[%d,%d]\n", attrib.scalex, attrib.scaley);

	int sx = (maxx-minx)/2 + (draw_coords. scalex/2);
	int sy = (maxy-miny)/2 + (draw_coords. scaley/2);
	//if (txtCol!=NULL) gfx.color(txtCol);
	gfx.box(px,py, sx , sy , _title, txtCol, false);
	//PRINT("offset[%d,%d] size[%d,%d]\n",  px,  py, sx, sy);
}
//----------------------------------------------------------
//------------------------------
//void ChemDisplay::draw_menu_border(ChemDisplayAttrib *screen_coords, ChemMenu *menu){
void ChemDisplay::draw_menu_border(ChemMenu *menu){
	if (menu==NULL) return;
	gfx.color(200,200,200);
//	draw_box(&menu->coords, menu-> min_posx, menu-> min_posy, menu-> max_posx, menu-> max_posy, menu-> gettitle());
	draw_box(&menu->coords, menu-> min_posx, menu-> min_posy, menu-> max_posx, menu-> max_posy, menu-> title.get());
}
//------------------------------
void ChemDisplay::draw_menu(ChemMenu *menu){
	if (menu==NULL) return;


	draw_menu_border(menu);

	ChemDisplayColor *c = &menu-> col;

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = menu-> button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		if (current_item-> item->_selected)		c = &menu-> selcol;
		else 									c = &menu-> col;
		//PRINT("== > draw button\n");
		draw_button(&menu-> coords, current_item-> item, c);
		//-----
		current_item = current_item-> next;
	}

};
//------------------------------

void ChemDisplay::draw_button(ChemDisplayCoords *menu_coords, ChemMenuButton *button, ChemDisplayColor *col) {

	if (button==NULL) return;
	if (col==NULL) return;

	int x = button-> coords.screenx(&gfx);
	int y = button-> coords.screeny(&gfx);

	gfx.color(col-> r, col-> g, col-> b);
//	gfx.box(x,y, button-> sizex/2, button-> sizey/2, button-> gettext(), true);
	gfx.box(x,y, button-> sizex/2, button-> sizey/2, button-> text.get(), true);



	//gfx.box(x,y,button-> sizex/2, button-> sizey/2, button-> gettext(), true);
	//if (button-> gettext()!=NULL)	gfx.text(button-> gettext(), x, y);
};
//------------------------------

void ChemDisplay::draw_peplist(ChemPeplistDisplay *peplistDisplay, ChemDisplayColor *col) {
	if (peplistDisplay==NULL) return;

	//PRINT("======== \n");
	int c = peplistDisplay-> index;
	int x = 0;
	int y = 0;
	//PRINT("====== peplist ===\n");	DUMP(peplistDisplay)	PRINT("======\n");

	if (col==NULL)	col = &peplistDisplay->col;
	ChemDisplayColor txtcol;
	//gfx.color(col-> r, col-> g, col-> b);


	int max_items = peplistDisplay-> count();
	int num_pages = max_items / (peplistDisplay-> width * peplistDisplay-> height);
	int current_page = c / ( peplistDisplay-> width * peplistDisplay-> height );


	// Draw CElls -----------------------------------
	while (true) {

		char 	label[16];
		// try to get next peptide
		mylist<Peptide>::mylist_item<Peptide>  *pep_item = peplistDisplay-> get(c);
		txtcol.set(col-> r, col-> g, col-> b);

		if ((pep_item!=NULL) && (pep_item->item !=NULL)) {
			//gfx.color(col-> r, col-> g, col-> b);
			//txtcol.set(col-> r, col-> g, col-> b);
			sprintf(label, "[0x%X]", pep_item-> item->get());
			c++;
			pep_item = pep_item-> next;
		} else {
			//gfx.color(col-> r/2, col-> g/2, col-> b/2);
			txtcol.set(col-> r/2, col-> g/2, col-> b/2);
			sprintf(label, "[]");
		}
		gfx.color(col-> r, col-> g, col-> b);
		draw_box(&peplistDisplay-> coords, x,y,x,y, label, &txtcol);

		if ((x==0)||(y==0)) {
			gfx.color(col);

			if (x==0) {
				ChemDisplayCoords display_coords(&peplistDisplay-> coords);
				display_coords.offsetx -= 2;
				sprintf(label, "0x%x", (x*y) );
				draw_box(&display_coords, x-1,y,x-1,y, label);
			}

			if (y==0) {
				ChemDisplayCoords display_coords(&peplistDisplay-> coords);
				display_coords.offsety -= 2;
				sprintf(label, "0x%x", x);
				//gfx.color(col-> r, col-> g, col-> b);
				draw_box(&display_coords, x,y+1,x,y+1, label);
			}

			if ((x==0)&&(y==0)) {
				ChemDisplayCoords display_coords(&peplistDisplay-> coords);
				display_coords.offsetx -= 2;
				display_coords.offsety -= 2;
				sprintf(label, "Pg %d/%d", current_page+1, num_pages+1);
				//gfx.color(col-> r, col-> g, col-> b);
				draw_box(&display_coords, x-1,y+1,x-1,y+1, label);
			}
		}

		/// next cell
		// horizont
		if (++x >= peplistDisplay-> width) {
			x=0;
			if (--y <= - peplistDisplay-> height)
				return;
		} //--------------
		// ---- end while
	}
	//-------------------------------------------------

	return ;

}
//-------------------------------------------
void	ChemDisplay::draw_title_bar(ChemScreen *screen) {
	if (screen==NULL) return;

	// point text to next line
	gfx.line_pos = gfx.line_height*2;

	char msg[256];
	int px = PRINT_INDENT;
	int py = FONT_HEIGHT;


	ChemDisplayColor txtcol(255,255,255);
	ChemDisplayColor red(255,0,0);

	// -- backing box  ----------
	gfx.color(&screen-> title_col);
	//gfx.box(gfx.width/2, gfx.line_height/2, gfx.width/2, gfx.line_height/2, NULL, true);
	gfx.box(gfx.width/2, gfx.line_height/2, gfx.width/2, gfx.line_height/2, NULL, &screen-> title_col, true);

	// -- title ----------
	//gfx.color(255,255,255);
	gfx.color(&txtcol);
	sprintf(msg, "Screen[%s]",	screen-> name.get());
	gfx.text(msg, px, py);	px += (FONT_WIDTH * (strlen(msg)+1));

	// -- attribs ----------
	sprintf(msg, "Pos[%d,%d] Scale[%d,%d] Offs[%d,%d]",
			screen-> coords.posx,	screen-> coords.posy,
			screen-> coords.scalex,	screen-> coords.scaley,
			screen-> coords.offsetx, screen-> coords.offsety);
	gfx.text(msg, px, py);	px += (FONT_WIDTH * (strlen(msg)+1));

	// --- Selected Pep/Mole -----
	px += (FONT_WIDTH * 3);
	sprintf(msg, "SelectedPep[0x%zX] SelectedMole[0x%zX]",
				(long unsigned int) screen-> selected_pep,
				(long unsigned int) screen-> selected_mole);
	gfx.text(msg, px, py);	px += (FONT_WIDTH * (strlen(msg)+1));


	// ==============================================
	// now do some from R-> L  (ie <--)
	int px2 = gfx.width;

	// -- render ----------
	if (screen-> renderCB ==NULL){ sprintf(msg, "NoRender[0x%zX]", (long unsigned int) screen-> renderCB);	}
	else 						 { sprintf(msg, "Render[0x%zX]", (long unsigned int) screen-> renderCB);	}
	px2 -= ((strlen(msg))*FONT_WIDTH); 	gfx.text(msg, px2, py);


	// --- waiting -----
	if (screen->waiting) {
		//enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
		switch(screen->waitmode) {
		case WAIT_CURS:		sprintf(msg, "Waiting(curs)");		break;
		case WAIT_SCREEN:	sprintf(msg, "Waiting(screen)");	break;
		case WAIT_OBJECT:	sprintf(msg, "Waiting(object?)");	break;
		} // end switch
	} else { sprintf(msg, "%s", "NotWait[]");	}
	px2 -= ((strlen(msg)+1)*FONT_WIDTH); 	gfx.text(msg, px2, py);



	// --- Selected Menu -----
	if (screen->current_menu ==NULL) {
		sprintf(msg, "()");
		px2 -= ((strlen(msg))*FONT_WIDTH); 	gfx.text(msg, px2, py);
	}
	else {
		gfx.color(&red);
//		sprintf(msg, "(menu[%s])", screen->current_menu-> gettitle());
		sprintf(msg, "(menu[%s])", screen->current_menu-> title.get());
		px2 -= ((strlen(msg)+1)*FONT_WIDTH); 	gfx.text(msg, px2, py);
		gfx.color(&txtcol);

	}
	//px2 -= ((strlen(msg)+1)*FONT_WIDTH); 	gfx.text(msg, px2, py);


	return;
}
//-------------------------------------------
void ChemDisplay::draw_screen(ChemScreen *screen, Concentration_CLI *cli){
	if (cli==NULL) return;
	if (screen==NULL) return;

	//attrib.cp(&screen-> attrib);	// PRINT("display attribs :"); attrib.dump();

	gfx.open();
	display_screen = screen;
	while(true) {
		//=======================
		gfx.clear();

		//-----------
		// grid first (most back layer)
		switch(screen-> gridmode) {
		case GRID_OFF: break;
		case GRID_MOLE:
			grid(&screen-> coords, 50,50,50);
			grid_axis(&screen-> coords, 150,150,150);
			break;
		case GRID_MENU:
			if (screen-> current_menu!=NULL) {
				ChemDisplayCoords display_coords(&screen-> current_menu-> coords);
				//display_coords.setpos(0,0);
				display_coords.posx = 0; display_coords.posy = 0;
				grid(&display_coords, 50,0,0);
				grid_axis(&display_coords, 100,0,0);
			}
			break;

		}

		//-----------
		// title bar
		draw_title_bar(screen);

		// ---------------
		// screen (render) callback
		if (screen-> renderCB !=NULL) screen-> renderCB (cli, 0, NULL);

		//----- draw all menus
//		if (screen-> menu_list2!=NULL) {
//			mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = screen-> menu_list2-> gethead();
			mylist<ChemMenu>::mylist_item<ChemMenu> *current_menu_item = screen-> menu_list.gethead();
			while ((current_menu_item != NULL) && (current_menu_item-> item != NULL)) {
			//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
				draw_menu(current_menu_item-> item);
				//-------
				current_menu_item = current_menu_item->next;
			}
//		} // end menus


		// ------------------
		//
		mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *current_peplist_item = screen-> peplist_list.gethead();
		while ((current_peplist_item != NULL) && (current_peplist_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_peplist(current_peplist_item-> item, NULL);
			//-------
			current_peplist_item = current_peplist_item->next;
		}




		// -------------------------------------------
		//gfx.printg((const char*) "End(screen).");
		//-------- wait / loop
		gfx.flush();
		if (screen-> waiting) {
			int r = screen-> wait(cli, this);
			// allow escape out
			if (r <0) {
				// gfx.close();
				screen-> waiting = false;
				break;
			}
			//PRINT("r=[%d]\n", r);
		} else {
			break;
		}
	}

}
//-------------------------------
ChemScreen *ChemDisplay::add_screen(const char* screen_title){
	//PRINT("ADD[%s]..\n", screen_title);
	if (screen_title==NULL) 		{ PRINT("NULL screen_title");		return NULL;	}
	if (strlen(screen_title)==0) 	{ PRINT("Empty screen_title");		return NULL;	}

	ChemScreen *found_screen = search_screen(screen_title);
	if (found_screen!=NULL) { return NULL;	}

	mylist<ChemScreen>::mylist_item<ChemScreen> *new_item = screen_list->add();
	if ((new_item==NULL)||(new_item-> item ==NULL)) {	return NULL;	}

	new_item-> item-> name.set(screen_title);
	//--------------
	return new_item-> item;
}
//-------------------------------
ChemScreen *ChemDisplay::search_screen(const char* screen_title){
	//ChemScreen *found_screen = NULL;

	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = screen_list->gethead();
	while ((screen_item!=NULL)&&(screen_item-> item!=NULL)) {

//		if (screen_item-> item->istitle(screen_title)==0) {
		if (screen_item-> item->name == screen_title) {
			return screen_item-> item;
		}
		//---------------------
		screen_item = screen_item->next;
	}
	//------
	return NULL;
}

//-------------------------------//-------------------------------
int	ChemDisplay::del_screen(ChemScreen *screen){
	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = screen_list->search(screen);
	if (screen_item==NULL) return -1;

	// if current screen
	if (selected_screen == screen) {	selected_screen = NULL;	gfx.close(); }

	screen_list-> del(screen_item);

	return 0;
}


//-------------------------------//-------------------------------


