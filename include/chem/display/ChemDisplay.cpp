/*
 * VMDisplay.cpp
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#include "ChemDisplay.h"
#include "callbacks/screen_callbacks.h"
//#include "ChemMenuList.h"
//#define  DISPLAY_FONT_HEIGHT 10
/*
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
 */
//-------------------------------
ChemDisplay::ChemDisplay(Concentration_CLI *_cli) {

	cli = _cli;
	gfx.title = "NewChem";
	gfx.width = 1000;
	gfx.height = 800;
	callback = cli_redraw;


	selected_screen = NULL;
	//display_screen = NULL;
	selected_mole = NULL;
	selected_pep = NULL;



}
//-------------------------------
ChemDisplay::~ChemDisplay() {}
//-------------------------------
void ChemDisplay::dump() {

	printf("ChemDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d]\n",	gfx.width, gfx.height);
	printf("screen_list=>");
	screen_list.dump();
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


//---------------------------------//---------------------------------//---------------------------------
int	ChemDisplay::addcmd(mylist<Display_Command> *cmd_list, int 	(*op)(ChemDisplay*, int, char**), char *name){
	if ((cmd_list==NULL)||(op==NULL)||(name==NULL)) return -1;

	mylist<Display_Command>::mylist_item<Display_Command> *cmd = cmd_list-> add();
	if (cmd==NULL) return -10;
	if (cmd-> item ==NULL) return -11;

	cmd-> item-> operation = op;
	sprintf(cmd-> item-> name, "%s", name);
	return 0;
}

//---------------------------------//---------------------------------//---------------------------------
//-------------------------------
void ChemDisplay::load_commands(void){

	if (cli!=NULL) cli-> load_commands();

	cli_load_screen(this, 0, NULL);

	cli_load_pepdisp(this,0, NULL);
	cli_load_moledisp(this,0, NULL);
	cli_load_concdisp(this,0, NULL);

	cli_load_peplist(this,0, NULL);
	cli_load_molelist(this,0, NULL);
	cli_load_conclist(this,0, NULL);

//	cli_load_menu(this,0, NULL);
//	cli_load_button(this,0, NULL);
}

//-----------------------------------
Display_Command *search_display_cmd_list(mylist<Display_Command> *cmd_list, const char *name) {
	Display_Command  *cmd = NULL;
	mylist<Display_Command>::mylist_item<Display_Command>  *next_item = cmd_list-> gethead();
	while ((next_item!=NULL) && (next_item-> item != NULL)) {
		int r = strcmp(name, next_item-> item->name);
		if (r==0) {
			cmd = next_item-> item;
			break;
		}
		// ---
		next_item = next_item->next;
	}
	return cmd;
}

//---------------------------------
int	ChemDisplay::run(mylist<Display_Command> *cmd_list, int argc, char **argv){
	//if ((cmd_list==NULL) || (argc<1) || (argv==NULL)) return -100;

	int	last_result = 0;

	//-------------------
	if ((cmd_list!=NULL) && (argc>0) && (argv!=NULL)) {
		if (argv[0][0] != '#') {
			Display_Command  *cmd = search_display_cmd_list(&display_cmdlist, argv[0]);

			//PRINT("search ===\n");		DUMP(cmd); NL

			if (cmd==NULL) {
				printf("[%s].Command Not Found\n", argv[0]);
				last_result =  -110;
			} else
				if (cmd-> operation==NULL) {
					printf("[%s].Command.operation NULL\n", argv[0]);
					last_result =  -111;
			}

			if (last_result>=0)  {
				last_result = cmd-> operation(this, argc-1, &argv[1]);
				LOG("[%s].[%d]\n", argv[0], last_result);
				if (cmd->callback !=NULL) {
					//cmd->callback(last_result);
					cmd->callback(this, 0, NULL);
				}
			}
		}// end '#'
	} // else argc ==0
	// ---------------------------------

	if (callback!=NULL) {
		//PRINT("---\n");
		callback(this, argc-1, &argv[1]);
	}

	return last_result;
}
//---------------------------------







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

	int x_steps = (gfx.width / grid_coords-> scalex)/2;
	int y_steps = (gfx.height / grid_coords-> scaley)/2;
	//PRINT("Grid <BREAK>\n"); return;
	int xinc = x_steps/20; if (xinc<1) xinc=1;
	int yinc = y_steps/20; if (yinc<1) yinc=1;

	for (int x=(-x_steps - grid_coords-> posx); x < (x_steps -grid_coords-> posx); x+= xinc) {
		grid_axis(grid_coords, red, green, blue, x, 0, 0, true);
	}

	for (int y=(-y_steps - grid_coords-> posy); y< (y_steps - grid_coords-> posy); y+= yinc) {
		grid_axis(grid_coords, red, green, blue, 0, y, 1, true);
	}
	gfx.flush();

}
//-------------------------------
Peptide *ChemDisplay::draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick, int red, int green, int blue){
	gfx.color(red, green, blue);
	return draw_pep(screen, coords, pep, mouseclick);
};
Peptide *ChemDisplay::draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick, ChemDisplayColor *col){
	gfx.color(col);
	return draw_pep(screen, coords, pep, mouseclick);
};

//-------------------------------
Peptide *ChemDisplay::draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick){
	if ((screen==NULL)||(pep==NULL)) return NULL;

	PepPosVecType  	*pep_pos = pep->getpos();
	if (pep_pos==NULL) return NULL;

	if (coords ==NULL)
		coords = &screen-> coords;
	ChemDisplayCoords display_coords(coords);
	//-------------------
	display_coords.posx += pep_pos[PEPPOS_X];
	display_coords.posy += pep_pos[PEPPOS_Y];

	//-------------------
	// test mouseclick
	Peptide *hit = NULL;
	if ((mouseclick)&&display_coords.hit(&gfx)) {
		hit = pep;
		if (hit!=NULL) { selected_pep = hit; }
	}

	// draw pep
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
	gfx.flush();


	/*
	if ((screen!=NULL) &&
		(screen->mouse_clicked)){ // &&
		//(display_coords.posx == screen->curs_pos.dim[PEPPOS_X]) &&
		//(display_coords.posy == screen->curs_pos.dim[PEPPOS_Y])) {
		if (display_coords.hit(&gfx))
		{	hit = pep;
			if (hit!=NULL) { selected_pep = hit; }
		}
	}
	*/

	return hit;
}

//-------------------------------
Molecule *ChemDisplay::draw_mole(ChemScreen *screen, ChemDisplayCoords *coords, Molecule *mole, bool mouseclick, int r, int g, int b){
	if (screen==NULL) return NULL;
	ChemDisplayColor col(r,g,b);
	return draw_mole(screen, coords, mole, mouseclick, &col);
}
//-------------------------------
Molecule *ChemDisplay::draw_mole(ChemScreen *screen, ChemDisplayCoords *coords, Molecule *mole, bool mouseclick, ChemDisplayColor *col){
	if (screen==NULL) return NULL;

	char msg[128];
	sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) mole);
	gfx.printg(msg);
	if (mole==NULL) return NULL;


	Molecule *hit = NULL;
	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){

		Peptide *pep = draw_pep(screen, coords, current_item-> item, mouseclick, col);
		if (pep!=NULL) { hit = mole; }
		//---
		current_item = current_item-> next;
	}

	if ((mouseclick) &&	(hit!=NULL)) {
			selected_mole = hit;
	}
	return hit;
}

//-------------------------------
//int ChemDisplay::keyval_set_col(char *keyname, ChemDisplayColor *col){	if ((keyname==NULL) ||(col==NULL)) return -1;	return -1;}
//-------------------------------
Molecule *ChemDisplay::draw_match(ChemScreen *screen, ChemDisplayCoords *coords, MoleculeMatchPos *matchpos,  bool mouseclick){
	if (screen==NULL) return NULL;
	if (matchpos==NULL) return NULL;

	// todo: system-colors - maybe use var_list ??
	ChemDisplayColor m1_col(0, 100, 0);
	ChemDisplayColor rot_col(100, 0, 0);
	ChemDisplayColor item_col(0, 0, 200);
	ChemDisplayColor matched_col(100, 0, 200);

	char str[128];
	sprintf(str, "Match[0x%zX], M1[0x%zX]->M2[0x%zX], Pos[%d,%d],Rot=[%d]. Box[%d,%d][%d,%d]",
			(long unsigned int) matchpos,
			(long unsigned int) matchpos->getM1(),
			(long unsigned int) matchpos->getM2(),

			matchpos-> get_current_pos()-> dim[PEPPOS_X],
			matchpos-> get_current_pos()-> dim[PEPPOS_Y],
			matchpos-> get_rotation(),

			matchpos-> get_start_pos()-> dim[PEPPOS_X],
			matchpos-> get_start_pos()-> dim[PEPPOS_Y],
			matchpos-> get_end_pos()-> dim[PEPPOS_X],
			matchpos-> get_end_pos()-> dim[PEPPOS_Y]);
	gfx.printg(str);

	Molecule *hit = NULL;
	Molecule *mole = NULL;


	// -------------- M1
	if (matchpos-> getM1()!=NULL) {
		gfx.color(&m1_col);
		gfx.cprintg((const char*) "M1");

		mole = draw_mole(screen, coords, matchpos-> getM1(), mouseclick, &m1_col);
		if ((mole!=NULL) && (hit==NULL)) { hit = mole; }
	}

	// ------------------- ROTMOLE
	if ((matchpos-> get_rotmole() != NULL) && (matchpos-> get_rotmole()-> pep_list.gethead() !=NULL)) {
		gfx.color(&rot_col);
		gfx.cprintg("rotemole");

		ChemDisplayCoords display_coords(screen-> coords);
		display_coords.posx += matchpos-> get_current_pos()-> dim[PEPPOS_X];
		display_coords.posy += matchpos-> get_current_pos()-> dim[PEPPOS_Y];

		mole = draw_mole(screen, &display_coords, matchpos-> get_rotmole(), mouseclick, &rot_col);
		if ((mole!=NULL) && (hit==NULL)) { hit = mole; }
	}

	// -------------- test item
	if (matchpos-> get_test_item()!=NULL) {
		gfx.color(&item_col);
		gfx.cprintg("test_item");

		ChemDisplayCoords display_coords(screen-> coords);
		display_coords.posx += matchpos-> get_current_pos()-> dim[PEPPOS_X];
		display_coords.posy += matchpos-> get_current_pos()-> dim[PEPPOS_Y];

		draw_pep(screen, &display_coords, matchpos-> get_test_item()-> item, mouseclick, &item_col);

	}
	//---------------

	// -------------- matched item
	if (matchpos-> get_matched_item()!=NULL) {
		gfx.color(&matched_col);
		gfx.cprintg("matched_item");

		ChemDisplayCoords display_coords(screen-> coords);
		display_coords.posx += matchpos-> get_current_pos()-> dim[PEPPOS_X];
		display_coords.posy += matchpos-> get_current_pos()-> dim[PEPPOS_Y];

		draw_pep(screen, &display_coords, matchpos-> get_matched_item()-> item, mouseclick, &matched_col);

	}
	//---------------





	//---------------
	gfx.flush();
	return hit;
}
//void draw_pepstack_row(mylist<Peptide>  *pep_list, int index, int width, int posx, posy){}
//-------------------------------
void ChemDisplay::draw_vm(ChemScreen *screen, Concentration_VM *vm){
	if (screen==NULL) return;
	char str[128];
	if (vm==NULL) {
		sprintf(str, "No VM's");
	} else {
		sprintf(str, "VM[0x%zX]: REGS: Pep[0x%zX] Mole[0x%zX] Conc[0x%zX] Vol[0x%zX]",
				(long unsigned int) vm,
				(long unsigned int) vm->pep,
				(long unsigned int) vm->mole,
				(long unsigned int) vm->conc,
				(long unsigned int) vm->concvol);
	}

	gfx.printg(str);

	if (vm!=NULL) {
		sprintf(str, "STACKS: Pep[%d] Mole[%d] Conc[%d]", vm->peptide_stack.count(), vm->molecule_stack.count(), vm->concentration_stack.count());
		gfx.printg(str);
	}

	//---------------
	gfx.flush();
}

//-------------------------------
void ChemDisplay::draw_conc_displ(ChemScreen *screen, ChemConcDisplay *conc_display){
	if (screen==NULL) return;
	if (conc_display==NULL) return;

	// draw pep
	int x = conc_display-> coords.screenx(&gfx);
	int y = conc_display-> coords.screeny(&gfx);

	int sx = conc_display-> coords.scalex/2;
	int sy = conc_display-> coords.scaley/2;

	gfx.box(x,y,sx, sy, NULL);
	int c = conc_display->buf.count();
	float min = conc_display-> buf.get_min();
	float max = conc_display-> buf.get_max();

	//PRINT("c=[%d] min=[%.3f] max=[%.3f]\n", c, min, max);
	if (c<=1) return;

	float scalex = conc_display->coords.scalex / (c-1);
	float scaley =  - conc_display->coords.scaley / (max-min);

	int old_posx = 0;
	int old_posy = 0;
	int posx =0;
	int posy =0;
	bool first = true;

	for (int i=0; i<c; i++) {
		float v;
		int r = conc_display->buf.get(i, &v);
		if (r<0) break;

		posx = (i * scalex) + x - sx;
		posy = ((v-min) * scaley) + y + sy;

		// PRINT("i=[%d] v[%.3f] posx=[%d] posy=[%d]\n", i, v, posx, posy);
		if (!first) { gfx.line(old_posx, old_posy, posx, posy);	}

		first = false;
		old_posx = posx;
		old_posy = posy;
	}
	Concentration *cp = conc_display->get_conc();
	Molecule *m = NULL;
	if (cp!=NULL) m = cp->getmole();

	char 	msg[128];
	sprintf(msg, "Conc[0x%zX]/Mole[0x%zX]", (long unsigned int) cp, (long unsigned int) m);
	gfx.text(msg,  x-sx, y-sy);
	sprintf(msg, "Min: %.3f", min);		gfx.text(msg,  x+sx, y+sy);
	sprintf(msg, "Max: %.3f", max);		gfx.text(msg,  x+sx, y-sy);
}

//###############################################################################
//void ChemDisplay::draw_box(int min_xpos, int min_ypos, int max_xpos,int max_ypos) {
// draw
//void ChemDisplay::draw_box(ChemDisplayAttrib *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title){

void ChemDisplay::draw_box(ChemDisplayCoords *screen_coords, int minx, int miny, int maxx,int maxy){
	draw_box(screen_coords, minx, miny, maxx, maxy, NULL, NULL, NULL);
};
void ChemDisplay::draw_box(ChemDisplayCoords *screen_coords, int minx, int miny, int maxx,int maxy, const char *_title){
	draw_box(screen_coords, minx, miny, maxx, maxy, _title, NULL, NULL);
};
//---------------------------------------

void ChemDisplay::draw_box(ChemDisplayCoords *screen_coords, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title, ChemDisplayColor *boxcol, ChemDisplayColor *txtcol){
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
	gfx.box(px,py, sx , sy , _title, boxcol, txtcol, false);
	//PRINT("offset[%d,%d] size[%d,%d]\n",  px,  py, sx, sy);
}
//----------------------------------------------------------
/***************
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
	gfx.box(x,y, button-> sizex/2, button-> sizey/2, button-> text.get(), NULL, NULL, true);



	//gfx.box(x,y,button-> sizex/2, button-> sizey/2, button-> gettext(), true);
	//if (button-> gettext()!=NULL)	gfx.text(button-> gettext(), x, y);
};
*******************/
//------------------------------
void ChemDisplay::draw_pepdisp(ChemScreen *screen, ChemPepDisplay *pepdis, bool mouseclick){
	if (screen==NULL) return;
	if (pepdis==NULL) return;
	if (pepdis-> pep == NULL) return;
	if (*pepdis->pep==NULL) return;
	//Peptide 	*draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick, int red, int green, int blue);
	//Peptide		*draw_pep(ChemScreen *screen, ChemDisplayCoords *coords, Peptide *pep, bool mouseclick);
	draw_pep(screen, &pepdis->coords, *pepdis->pep, mouseclick);

};
//------------------------------
//------------------------------
void ChemDisplay::draw_moledisp(ChemScreen *screen, ChemMoleDisplay *moledis, bool mouseclick){
	if (screen==NULL) return;
	if (moledis==NULL) return;
	//if (moledis-> mole == NULL) return;
	//if (*moledis->mole==NULL) return;
	//Molecule	*draw_mole(ChemScreen *screen, ChemDisplayCoords *coords, Molecule *mole, bool mouseclick, ChemDisplayColor *col);
	// ----
	// todo: draw_moledisp
	if (moledis->mole!=NULL)
		draw_mole(screen, &moledis->coords, *moledis->mole, mouseclick, &moledis->col );
};
//------------------------------
/***************************************************************
template <class T> void	ChemDisplay::draw_list(ChemScreen *screen, ListDisplay<T> *list_display, bool mouseclick){

	if (screen==NULL) return;
	if (list_display==NULL) return;

	int c = list_display-> index;
	int x = 0;
	int y = 0;

	int max_items = list_display-> count();
	int num_pages = max_items / (list_display-> width * list_display-> height);
	int current_page = c / ( list_display-> width * list_display-> height );

	ChemDisplayColor txtcol;
	// Draw CElls -----------------------------------
	while (true) {

		char 	label[16];
		// try to get next peptide
		mylist<Peptide>::mylist_item<Peptide>  *pep_item = list_display-> get(c);

		if ((pep_item!=NULL) && (pep_item->item !=NULL)) {

			//-------------------
			// test mouseclick
			Peptide *hit = NULL;
			if ((mouseclick)&& (list_display-> coords.hit(&gfx, x, y))) {
				hit = pep_item->item;
				if (hit!=NULL) { selected_pep = hit; }
			}

			// sel color
			if (selected_pep ==pep_item->item)	txtcol = list_display->selcol;
			else txtcol = list_display->col;

		//	if ((cli!=NULL) && (cli->is_selected(pep_item->item)))
		//		txtcol = list_display->selcol;
		//	else txtcol = list_display->col;

			//txtcol.set(col-> r, col-> g, col-> b);
			sprintf(label, "[0x%X]", pep_item-> item->get());
			c++;
			pep_item = pep_item-> next;
		} else {
			txtcol.set(list_display->col.r/2, list_display->col.g/2, list_display->col.b/2);
			//txtcol.set(col-> r/2, col-> g/2, col-> b/2);
			sprintf(label, "[]");
		}
		//------------------------------
		//col.dump();
		draw_box(&list_display-> coords, x,y,x,y, label, &list_display->col, &txtcol);


		// side cells
		if ((x==0)||(y==0)) {
			gfx.color(&list_display->col);

			if (x==0) {
				ChemDisplayCoords display_coords(&list_display-> coords);
				display_coords.offsetx -= 2;
				sprintf(label, "0x%x", (-y*list_display-> width) );
				draw_box(&display_coords, x-1,y,x-1,y, label);
			}

			if (y==0) {
				ChemDisplayCoords display_coords(&list_display-> coords);
				display_coords.offsety -= 2;
				sprintf(label, "0x%x", x);
				draw_box(&display_coords, x,y+1,x,y+1, label);
			}

			if ((x==0)&&(y==0)) {
				ChemDisplayCoords display_coords(&list_display-> coords);
				display_coords.offsetx -= 2;
				display_coords.offsety -= 2;
				sprintf(label, "Pg %d/%d", current_page+1, num_pages+1);
				draw_box(&display_coords, x-1,y+1,x-1,y+1, label);
			}
		}

		/// next cell
		// horizont
		if (++x >= list_display-> width) {
			x=0;
			if (--y <= - list_display-> height)
				return;
		} //--------------
		// ---- end while
	}
	//-------------------------------------------------

	return ;

}
***************************************************************/
//=======================================================
void ChemDisplay::draw_peplist(ChemScreen *screen, Concentration_CLI *cli, ChemPeplistDisplay *peplistDisplay, bool mouseclick) {
	if (screen==NULL) return;
	if (peplistDisplay==NULL) return;

	int c = peplistDisplay-> index;
	int x = 0;
	int y = 0;

	int max_items = peplistDisplay-> count();
	int num_pages = max_items / (peplistDisplay-> width * peplistDisplay-> height);
	int current_page = c / ( peplistDisplay-> width * peplistDisplay-> height );

	ChemDisplayColor txtcol;
	// Draw CElls -----------------------------------
	while (true) {

		char 	label[16];
		// try to get next peptide
		mylist<Peptide>::mylist_item<Peptide>  *pep_item = peplistDisplay-> get(c);

		if ((pep_item!=NULL) && (pep_item->item !=NULL)) {

			//-------------------
			// test mouseclick
			Peptide *hit = NULL;
			if ((mouseclick)&& (peplistDisplay-> coords.hit(&gfx, x, y))) {
				hit = pep_item->item;
				if (hit!=NULL) { selected_pep = hit; }
			}

			Concentration_VM  *vm = cli-> chem_engine.get_selected_vm();
			Peptide *selected_pep = NULL;
			if (vm!=NULL) selected_pep = vm->pep;


			// sel color
			if (selected_pep ==pep_item->item)	txtcol = peplistDisplay->selcol;
			else txtcol = peplistDisplay->col;

		//	if ((cli!=NULL) && (cli->is_selected(pep_item->item)))
		//		txtcol = peplistDisplay->selcol;
		//	else txtcol = peplistDisplay->col;

			//txtcol.set(col-> r, col-> g, col-> b);
			sprintf(label, "[0x%X]", pep_item-> item->get());
			c++;
			pep_item = pep_item-> next;
		} else {
			txtcol.set(peplistDisplay->col.r/2, peplistDisplay->col.g/2, peplistDisplay->col.b/2);
			//txtcol.set(col-> r/2, col-> g/2, col-> b/2);
			sprintf(label, "[]");
		}
		//------------------------------
		//col.dump();
		draw_box(&peplistDisplay-> coords, x,y,x,y, label, &peplistDisplay->col, &txtcol);


		// side cells
		if ((x==0)||(y==0)) {
			gfx.color(&peplistDisplay->col);

			if (x==0) {
				ChemDisplayCoords display_coords(&peplistDisplay-> coords);
				display_coords.offsetx -= 2;
				sprintf(label, "0x%x", (-y*peplistDisplay-> width) );
				draw_box(&display_coords, x-1,y,x-1,y, label);
			}

			if (y==0) {
				ChemDisplayCoords display_coords(&peplistDisplay-> coords);
				display_coords.offsety -= 2;
				sprintf(label, "0x%x", x);
				draw_box(&display_coords, x,y+1,x,y+1, label);
			}

			if ((x==0)&&(y==0)) {
				ChemDisplayCoords display_coords(&peplistDisplay-> coords);
				display_coords.offsetx -= 2;
				display_coords.offsety -= 2;
				sprintf(label, "Pg %d/%d", current_page+1, num_pages+1);
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
//=======================================================
//-------------------------------------------
void ChemDisplay::draw_molelist(ChemScreen *screen, Concentration_CLI *cli, ChemMolelistDisplay *molelistDisplay, bool mouseclick) {
	if (screen==NULL) return;
	if (molelistDisplay==NULL) return;

	//PRINT("======== \n");
	int start = molelistDisplay-> row * molelistDisplay-> width ;
	int x = 0;
	int y = 0;
	//PRINT("====== peplist ===\n");	DUMP(peplistDisplay)	PRINT("======\n");

	//if (col==NULL)	col = &molelistDisplay->col;
	ChemDisplayColor txtcol;

	int max_items = molelistDisplay-> count();
	int num_pages = max_items / (molelistDisplay-> width * molelistDisplay-> height);
	int current_page = start / ( molelistDisplay-> width * molelistDisplay-> height );

	Concentration_VM  *vm = cli-> chem_engine.get_selected_vm();
	Molecule *selected_mole = NULL;
	if (vm!=NULL) selected_mole = vm-> mole;
	// Draw CElls -----------------------------------
	int c = start;
	while (true) {

		char 	label[16];
		// try to get next peptide
		mylist<Molecule>::mylist_item<Molecule>  *mole_item = molelistDisplay-> get(c);

		if ((mole_item!=NULL) && (mole_item->item !=NULL)) {

			//-------------------
			// test mouseclick
			Molecule *hit = NULL;
			if ((mouseclick)&& (molelistDisplay-> coords.hit(&gfx, x, y))) {
				hit = mole_item->item;
				if (hit!=NULL) { selected_mole = hit; }
			}


			if (selected_mole ==mole_item->item)	txtcol = molelistDisplay->selcol;
			else txtcol = molelistDisplay->col;


		//	txtcol.set(col-> r, col-> g, col-> b);
		//	sprintf(label, "[0x%X]", pep_item-> item->get());
			sprintf(label, "0x%zX\n[%d]", (long unsigned int) mole_item-> item, mole_item-> item->pep_list.count());

			//sprintf(label, "A\nBB", (long unsigned int) mole_item-> item, mole_item-> item->pep_list.count());

			//c++;
			mole_item = mole_item-> next;
		} else {
			//txtcol.set(col-> r/2, col-> g/2, col-> b/2);
			txtcol.set(molelistDisplay->col.r/2, molelistDisplay->col.g/2, molelistDisplay->col.b/2);

			sprintf(label, "[]");
		}

		//gfx.color(col-> r, col-> g, col-> b);
		draw_box(&molelistDisplay-> coords, x,y,x,y, label, &molelistDisplay->col, &txtcol);

		// side cells
		if ((x==0)||(y==0)) {
			gfx.color(&molelistDisplay->col);

			if (x==0) {
				ChemDisplayCoords display_coords(&molelistDisplay-> coords);
				display_coords.offsetx -= 2;
				sprintf(label, "0x%x", (-y*molelistDisplay-> width)+start); //+(c %  molelistDisplay-> width) );
				draw_box(&display_coords, x-1,y,x-1,y, label);
			}

			if (y==0) {
				ChemDisplayCoords display_coords(&molelistDisplay-> coords);
				display_coords.offsety -= 2;
				sprintf(label, "0x%x", x);
				draw_box(&display_coords, x,y+1,x,y+1, label);
			}

			if ((x==0)&&(y==0)) {
				ChemDisplayCoords display_coords(&molelistDisplay-> coords);
				display_coords.offsetx -= 2;
				display_coords.offsety -= 2;
				sprintf(label, "Pg %d/%d", current_page+1, num_pages+1);
				draw_box(&display_coords, x-1,y+1,x-1,y+1, label);
			}
		}
		/// next cell
		// horizont
		if (++x >= molelistDisplay-> width) {
			x=0;
			if (--y <= - molelistDisplay-> height)
				return;
		} //--------------
		c++;
		// ---- end while
	}
	//-------------------------------------------------

	return ;

}
//-------------------------------------------
void ChemDisplay::draw_conclist(ChemScreen *screen, Concentration_CLI *cli, ChemConclistDisplay *conclistDisplay, bool mouseclick) {
	if (screen==NULL) return;
	if (conclistDisplay==NULL) return;

	//PRINT("======== \n");
	int c = conclistDisplay-> index;
	int x = 0;
	int y = 0;
	//PRINT("====== peplist ===\n");	DUMP(peplistDisplay)	PRINT("======\n");

	//if (col==NULL)	col = &molelistDisplay->col;
	ChemDisplayColor txtcol;

	int max_items = conclistDisplay-> count();
	int num_pages = max_items / (conclistDisplay-> width * conclistDisplay-> height);
	int current_page = c / ( conclistDisplay-> width * conclistDisplay-> height );


	// Draw CElls -----------------------------------
	while (true) {

		char 	label[64];
		// try to get next peptide
		mylist<Concentration>::mylist_item<Concentration>  *conc_item = conclistDisplay-> get(c);

		if ((conc_item!=NULL) && (conc_item->item !=NULL)) {

			/*************
			//-------------------
			// test mouseclick
			Molecule *hit = NULL;
			if ((mouseclick)&& (conclistDisplay-> coords.hit(&gfx, x, y))) {
				hit = conc_item->item;
//				if (hit!=NULL) { selected_conc = hit; }
			}
			*************/

			txtcol = conclistDisplay->col;
			//sprintf(label, "0x%zX\n[%d]", (long unsigned int) conc_item-> item, conc_item-> item->pep_list.count());
			Molecule *m = conc_item->item->getmole();
			int n = 0;
			if (m!=NULL)  n=m->pep_list.count();

			sprintf(label, "[0x%zX][%d]\n(%.3f+%.3f)",  (long unsigned int) m, //conc_item-> item,
					n, conc_item->item->get(), conc_item->item->getdelta() );

			Concentration_VM  *vm = cli-> chem_engine.get_selected_vm();
			Molecule *selected_mole = NULL;
			if (vm!=NULL) selected_mole = vm->mole;
			if (m==selected_mole)
				txtcol = conclistDisplay->selcol;


			//-----------------
			c++;
			conc_item = conc_item-> next;
		} else {

			//txtcol.set(col-> r/2, col-> g/2, col-> b/2);
			txtcol.set(conclistDisplay->col.r/2, conclistDisplay->col.g/2, conclistDisplay->col.b/2);

			sprintf(label, "[]");
		}

		//gfx.color(col-> r, col-> g, col-> b);
		draw_box(&conclistDisplay-> coords, x,y,x,y, label, &conclistDisplay->col, &txtcol);

		// side cells
		if ((x==0)||(y==0)) {
			gfx.color(&conclistDisplay->col);

			if (x==0) {
				ChemDisplayCoords display_coords(&conclistDisplay-> coords);
				display_coords.offsetx -= 2;
				sprintf(label, "0x%x", (-y*conclistDisplay-> width) );
				draw_box(&display_coords, x-1,y,x-1,y, label);
			}

			if (y==0) {
				ChemDisplayCoords display_coords(&conclistDisplay-> coords);
				display_coords.offsety -= 2;
				sprintf(label, "0x%x", x);
				draw_box(&display_coords, x,y+1,x,y+1, label);
			}

			if ((x==0)&&(y==0)) {
				ChemDisplayCoords display_coords(&conclistDisplay-> coords);
				display_coords.offsetx -= 2;
				display_coords.offsety -= 2;
				sprintf(label, "Pg %d/%d", current_page+1, num_pages+1);
				draw_box(&display_coords, x-1,y+1,x-1,y+1, label);
			}
		}
		/// next cell
		// horizont
		if (++x >= conclistDisplay-> width) {
			x=0;
			if (--y <= - conclistDisplay-> height)
				return;
		} //--------------
		// ---- end while
	}
	//-------------------------------------------------

	return ;

}
//-------------------------------------------
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
	gfx.box(gfx.width/2, gfx.line_height/2, gfx.width/2, gfx.line_height/2, NULL, NULL, &screen-> title_col, true);

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
				(long unsigned int) selected_pep,
				(long unsigned int) selected_mole);
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


	/**********************

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
	*******************/

	return;
}
//-------------------------------------------
void ChemDisplay::draw_screen(ChemScreen *screen, Concentration_CLI *cli, bool mouseclick){
	if (cli==NULL) return;
	//Concentration_VM *vm = cli->get_selected_vm();
	if (screen==NULL) return;

	gfx.open();
	while(true) {
		//=======================
		gfx.clear();

		//-----------
		// grid first (most back layer)
		switch(screen-> gridmode) {
		case GRID_OFF: break;
		case GRID_ON:
			grid(&screen-> coords, 50,50,50);
			grid_axis(&screen-> coords, 150,150,150);
			break;
			/************
		case GRID_MENU:
			if (screen-> current_menu!=NULL) {
				ChemDisplayCoords display_coords(&screen-> current_menu-> coords);
				//display_coords.setpos(0,0);
				display_coords.posx = 0; display_coords.posy = 0;
				grid(&display_coords, 50,0,0);
				grid_axis(&display_coords, 100,0,0);
			}
			break;
			************/
		}

		//-----------
		// title bar
		draw_title_bar(screen);

		// ---------------
		//if (screen-> renderCB !=NULL) screen-> renderCB (cli, screen, mouseclick);
		if (screen-> renderCB !=NULL) screen-> renderCB (this, screen, mouseclick);

/*****************
	{
		//----- draw all menus
		mylist<ChemMenu>::mylist_item<ChemMenu> *current_menu_item = screen-> menu_list.gethead();
		while ((current_menu_item != NULL) && (current_menu_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_menu(current_menu_item-> item);
			//-------
			current_menu_item = current_menu_item->next;
		}
	}
*******************/
	{	// draw pep disp
		// ------------------
		mylist<ChemPepDisplay>::mylist_item<ChemPepDisplay> *current_pep_item = screen-> pep_list.gethead();
		while ((current_pep_item != NULL) && (current_pep_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_pepdisp(screen, current_pep_item-> item, mouseclick);
			//-------
			current_pep_item = current_pep_item->next;
		}
	}
	{	// draw mole disp
		// ------------------
		mylist<ChemMoleDisplay>::mylist_item<ChemMoleDisplay> *current_mole_item = screen-> mole_list.gethead();
		while ((current_mole_item != NULL) && (current_mole_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_moledisp(screen, current_mole_item-> item, mouseclick);
			//-------
			current_mole_item = current_mole_item->next;
		}
	}

	{
		// draw conc disp
		// ------------------
		mylist<ChemConcDisplay>::mylist_item<ChemConcDisplay> *current_conc = screen-> conc_list.gethead();
		while ((current_conc != NULL) && (current_conc-> item != NULL)) {
		//	PRINT("==== ChemMolelistDisplay = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_conc_displ(screen, current_conc-> item);
			//-------
			current_conc = current_conc->next;
		}
	}


	{	// draw pep lists
		// ------------------
		mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *current_peplist_item = screen-> peplist_list.gethead();
		while ((current_peplist_item != NULL) && (current_peplist_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_peplist(screen, cli, current_peplist_item-> item, mouseclick);
			//-------
			current_peplist_item = current_peplist_item->next;
		}
	}

	{	// draw mole lists
		// ------------------
		mylist<ChemMolelistDisplay>::mylist_item<ChemMolelistDisplay> *current_molelist_item = screen-> molelist_list.gethead();
		while ((current_molelist_item != NULL) && (current_molelist_item-> item != NULL)) {
		//	PRINT("==== ChemMolelistDisplay = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_molelist(screen, cli, current_molelist_item-> item, mouseclick);
			//-------
			current_molelist_item = current_molelist_item->next;
		}
	}

	{	// draw conc lists
		// ------------------
		mylist<ChemConclistDisplay>::mylist_item<ChemConclistDisplay> *current_conclist_item = screen-> conclist_list.gethead();
		while ((current_conclist_item != NULL) && (current_conclist_item-> item != NULL)) {
		//	PRINT("==== ChemConclistDisplay = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_conclist(screen, cli, current_conclist_item-> item, mouseclick);
			//-------
			current_conclist_item = current_conclist_item->next;
		}
	}

		// ------------
		gfx.flush();
		// -------------------------------------------
		//-------- wait / loop
		if ((screen-> waiting) &&(!mouseclick)) {
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

	mylist<ChemScreen>::mylist_item<ChemScreen> *new_item = screen_list.add();
	if ((new_item==NULL)||(new_item-> item ==NULL)) {	return NULL;	}

	new_item-> item-> name.set(screen_title);
	//--------------
	return new_item-> item;
}
//-------------------------------
ChemScreen *ChemDisplay::search_screen(const char* screen_title){
	//ChemScreen *found_screen = NULL;

	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = screen_list.gethead();
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
	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = screen_list.search(screen);
	if (screen_item==NULL) return -1;

	// if current screen
	if (selected_screen == screen) {	selected_screen = NULL;	gfx.close(); }

	screen_list.del(screen_item);

	return 0;
}


//-------------------------------//-------------------------------


