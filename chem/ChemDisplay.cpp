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
//	int		screenx(void);
//	int		screeny(void);
	void	getcol(void) { gfx.color(colr, colg, colb); };
//	int		line_pos;
public:
	GFX_Base	gfx;
ChemDisplayAttrib	attrib;
//	int 		offsetx;
//	int 		offsety;
//  PepPosVecType	*peppos;
//	int 		scale;
	// ------
	int 		colr;
	int 		colg;
	int 		colb;
	// ------

    // selected objects
	Concentration_VM			*core;
	Peptide						*pep;
	Molecule					*mole;
	Concentration				*conc;
	ConcentrationVolume 		*concvol;
	MoleculeMatchPos 			*matchpos;
	ChemMenuList				*menu_list;


  	//-------------------
	ChemDisplay();
	virtual ~ChemDisplay();
	void	dump();
	void	gdump();

	void	setcol(int red, int green, int blue){ 	colr = red; colg = green; colb = blue; gfx.color(colr, colg, colb); };
	void	grid(){ grid(colr, colg, colb); }
	void	grid(int red, int green, int blue);
	void	clearatt();

	void	draw_pep(Peptide *pep);
	void	draw_mole(Molecule *mole);
	void	draw_match(MoleculeMatchPos *matchpos);
	//---- new
	void	draw_regs(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	void	draw_pep(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	void	draw_mole(Peptide *mole, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue);
	//---
	void	draw_vm(Concentration_VM *vm);
	void	main(void);

};
// ----------------
 */
//-------------------------------
//---- new
/*
void ChemDisplay::draw_regs(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue){}
void ChemDisplay::draw_pep(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue){}
void ChemDisplay::draw_mole(Peptide *mole, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue){}
//-------------------------------
*/

ChemDisplay::ChemDisplay() {
	//line_pos = DISPLAY_FONT_HEIGHT;
	gfx.title = "NewChem";
	gfx.width = 1000;
	gfx.height = 800;

//	attrib.scalex = 30;
//	attrib.scaley = 20;

	current_screen = NULL;
	core = NULL;
	pep = NULL;
	mole = NULL;
	conc = NULL;
	concvol = NULL;
	matchpos = NULL;
//	menu_list = NULL;
	screen_list = NULL;


	// TODO: fix attrib.pos !! LEAK !!!
	//TODO: POS // attrib.pos = (PepPosVecType*) malloc(sizeof(PepPosVecType)*3);

	//	mylist<ChemScreen> 		*screen_list;

	screen_list = (mylist<ChemScreen>*) malloc(sizeof(mylist<ChemScreen>));
	if (screen_list!=NULL) {
		screen_list->init();
	}

//	attrib.gfx = &gfx;
	//clearatt();
}
//-------------------------------
ChemDisplay::~ChemDisplay() {
	if (screen_list!=NULL) free(screen_list);
	screen_list = NULL;
}
//-------------------------------
void ChemDisplay::dump() {
/*
	PepPosVecType *apos = attrib.getpos();

	printf("ChemDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d].scale[%d,%d].off[%d,%d].pos[0x%zX]\n",
			gfx.width, gfx.height, attrib.scalex, attrib.scaley, attrib.offsetx, attrib.offsety, (long unsigned int)  apos);
			//gfx.width, gfx.height, attrib.scale, col.r, col.g, col.b, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos);
	if (apos !=NULL) {
		printf(".. pos[%d,%d,%d]\n", apos[0], apos[1], apos[2]);
	}
*/
	printf("ChemDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d]\n",	gfx.width, gfx.height);

	printf("screen_list=>");
	screen_list->dump();
}
//-------------------------------
void ChemDisplay::gdump() {
	char msg[256];

	/*
	PepPosVecType *apos = attrib.getpos();

	char	pos_msg[32];
	if (apos ==NULL)	sprintf(pos_msg, "[NULL]");
	else				sprintf(pos_msg, "[%d,%d]", apos[PEPPOS_X], apos[PEPPOS_Y]);

	sprintf(msg, "ChemDisplay[0x%zX][%s].Screen[0x%zX].size[%d,%d].scale[%d, %d].off[%d,%d].pos[%s]",
			(long unsigned int) this,
			gfx.title,
			(long unsigned int) current_screen,
			gfx.width, gfx.height, attrib.scalex, attrib.scaley, attrib.offsetx, attrib.offsety, pos_msg);
			//(long unsigned int)  attrib.getpos());
			//curs_pos.dim[PEPPOS_X], curs_pos.dim[PEPPOS_Y] );
	*/

	sprintf(msg, "ChemDisplay[0x%zX][%s].Screen[0x%zX].size[%d,%d]",	(long unsigned int) this,
			gfx.title,
			(long unsigned int) current_screen,
			gfx.width, gfx.height);

	gfx.printg(msg);



}
//-------------------------------
//void ChemDisplay::open(){ gfx.open(width,height,"ChemDisplay");	gfx.clear();}
//-------------------------------
/*
int	ChemDisplay::screenx(void){
	int px = (gfx.width/2) + offsetx;
	if (peppos !=NULL)	{
		px += (peppos[PEPPOS_X] * scale);
	}
	return px;
}
//-------------------------------
int	ChemDisplay::screeny(void){
	int py = (gfx.height/2) + offsety;
	if (peppos !=NULL)	{
		py += (peppos[PEPPOS_Y] * scale);
	}
	return (gfx.height-py);
}
*/
//-------------------------------
void ChemDisplay::XXcurs(int red, int green, int blue){

//	PRINT("curs=[%d,%d]\n", curs_pos.dim[0], curs_pos.dim[1]);
//	draw_box(curs_pos.dim[0], curs_pos.dim[1], curs_pos.dim[0], curs_pos.dim[1]);
}
//-------------------------------
void ChemDisplay::grid(ChemDisplayAttrib *screen_attrib, int red, int green, int blue){
	if (screen_attrib==NULL) return;

//	PepPosVecType	*oldpos = attrib.getpos();
	PepPosVecType	*oldpos = screen_attrib-> getpos();
	if (oldpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return;	}


//	ChemDisplayAttrib display_attrib(&attrib);
	ChemDisplayAttrib display_attrib(screen_attrib);
	PepPosVecType	*display_pos = display_attrib.getpos();

	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}
	//PRINT("display_attrib =>");	display_attrib.dump();
	// --------------
	/*
	PepPosVecType	*oldpos = attrib.pos;
	PeptidePos pos;

	int oldposx = 0;
	int oldposy = 0;

	if (attrib.pos!=NULL) {
		oldposx = attrib.pos[PEPPOS_X];
		oldposy = attrib.pos[PEPPOS_Y];
	} else {
		attrib.pos = pos.dim;
	}
	*/
//	int x_steps = (gfx.width / attrib.scalex)/2;
//	int y_steps = (gfx.height / attrib.scaley)/2;
	int x_steps = (gfx.width / screen_attrib-> scalex)/2;
	int y_steps = (gfx.height / screen_attrib-> scaley)/2;
	//PRINT("Grid <BREAK>\n"); return;

	for (int x=(-x_steps - oldpos[PEPPOS_X]); x < (x_steps - oldpos[PEPPOS_X]); x++) {
		display_pos[PEPPOS_X] = x + oldpos[PEPPOS_X];
		int px = display_attrib.screenx(&gfx);
		if (x==0)	gfx.color(red, green, blue);
		else		gfx.color(red/2, green/2, blue/2);

		gfx.line(px ,0, px, gfx.height);
	}

	for (int y=(-y_steps - oldpos[PEPPOS_Y]); y< (y_steps - oldpos[PEPPOS_Y]); y++) {
		display_pos[PEPPOS_Y] = y + oldpos[PEPPOS_Y];
		int py = display_attrib.screeny(&gfx);
		//---
		if (y==0)	gfx.color(red, green, blue);
		else		gfx.color(red/2, green/2, blue/2);

		gfx.line(0, py, gfx.width, py);

	}

	gfx.flush();

}
//-------------------------------
void ChemDisplay::draw_pep(ChemDisplayAttrib *screen_attrib, Peptide *pep){
	if ((screen_attrib==NULL)||(pep==NULL)) return;

	PepPosVecType  	*pep_pos = pep->getpos();
	if (pep_pos==NULL) return;


	// --------------
//	PepPosVecType	*oldpos = attrib.getpos();
	PepPosVecType	*oldpos = screen_attrib-> getpos();
	if (oldpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return;	}

	// create a new attrib to store (screen_pos + peptide_pos)
//	ChemDisplayAttrib display_attrib(&attrib);
	ChemDisplayAttrib display_attrib(screen_attrib);

	//PRINT("display_attrib =>");	display_attrib.dump();
	PepPosVecType	*display_pos = display_attrib.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}
	// --------------

	display_pos[PEPPOS_X] += pep_pos[PEPPOS_X];
	display_pos[PEPPOS_Y] += pep_pos[PEPPOS_Y];

	//int x = display_attrib.screenx();
	//int y = display_attrib.screeny();
	int x = display_attrib.screenx(&gfx);
	int y = display_attrib.screeny(&gfx);

//	int sx = attrib.scalex/2;
//	int sy = attrib.scaley/2;
	int sx = display_attrib.scalex/2;
	int sy = display_attrib.scaley/2;

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

}
//-------------------------------
void ChemDisplay::draw_mole(ChemDisplayAttrib *screen_attrib, Molecule *mole, int r, int g, int b){
	if (screen_attrib==NULL) return;
	ChemDisplayColor col(r,g,b);
	draw_mole(screen_attrib, mole, &col);
}
//-------------------------------
void ChemDisplay::draw_mole(ChemDisplayAttrib *screen_attrib, Molecule *mole, ChemDisplayColor *col){
	if (screen_attrib==NULL) return;


	char msg[128];
	sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) mole);
	gfx.printg(msg);

	if (mole==NULL) return;
	//PepPosVecType *globalpos = pos;

	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		draw_pep(screen_attrib, current_item-> item, col);
		//---
		current_item = current_item-> next;
	}

}

//-------------------------------
void ChemDisplay::draw_match(ChemDisplayAttrib *screen_attrib, MoleculeMatchPos *matchpos){
	if ((screen_attrib==NULL) || (matchpos==NULL)) return;
	// --------------

//	PepPosVecType	*oldpos = attrib.getpos();
//	if (oldpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return;	}
//	ChemDisplayAttrib display_attrib(&attrib);
	ChemDisplayAttrib display_attrib(screen_attrib);

	PRINT("display_attrib =>");	display_attrib.dump();
	PepPosVecType	*display_pos = display_attrib.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}
	// --------------


	ChemDisplayColor m1_col(0, 100, 0);
	ChemDisplayColor rot_col(100, 0, 0);
	ChemDisplayColor item_col(0, 0, 200);


	char str[128];
	sprintf(str, "Match: Pos=[%d,%d] Box=[%d,%d][%d,%d] Rot=[%d]",
			matchpos-> current_pos.dim[PEPPOS_X],
			matchpos-> current_pos.dim[PEPPOS_Y],

			matchpos-> start_pos.dim[PEPPOS_X],
			matchpos-> start_pos.dim[PEPPOS_Y],

			matchpos-> end_pos.dim[PEPPOS_X],
			matchpos-> end_pos.dim[PEPPOS_Y],

			matchpos-> rotation);
	gfx.printg(str);

	if (matchpos-> getM1()!=NULL) {
		gfx.color(&m1_col);
		gfx.cprintg((const char*) "M1");
//		draw_mole(matchpos-> getM1(), &m1_col);
		draw_mole(screen_attrib, matchpos-> getM1(), &m1_col);
	}

	/*
	if ((matchpos-> rotmole != NULL) && (matchpos-> rotmole-> pep_list.gethead() !=NULL)) {
		//printf("########### ROTMOLE ############\n");
		//matchpos-> rotmole-> dump();
		//printf("########### ROTMOLE ############\n");
		attrib.pos = matchpos-> current_pos.dim;

		gfx.color(&rot_col);
		gfx.cprintg("rotemole");
		attrib.pos = matchpos-> current_pos.dim;
		draw_mole(matchpos-> rotmole, &rot_col);
	}

	if (matchpos-> get_test_item()!=NULL) {
		gfx.color(&item_col);
		gfx.cprintg("test_item");
		attrib.pos = matchpos-> current_pos.dim;
		draw_pep(matchpos-> get_test_item()-> item);
	}
	*/
	//---------------
	gfx.flush();
}

//-------------------------------
void ChemDisplay::draw_vm(Concentration_VM *vm){
	if (vm==NULL) return;
	gfx.color(100, 100, 100);
	gfx.cprintg("VM..");

	char str[128];
	sprintf(str, "REGS: PEP[0x%zX] MOLE[0x%zX] CONC[0x%zX] VOL[0x%zX]",
			(long unsigned int) vm->pep,
			(long unsigned int) vm->mole,
			(long unsigned int) vm->conc,
			(long unsigned int) vm->concvol);
	gfx.printg(str);
	//---------------
	gfx.flush();
}
// ############################################################
/*
//-------------------------------//-------------------------------
ChemMenu	*ChemDisplay::add_menu(const char *_title){
	mylist<ChemMenu>::mylist_item<ChemMenu> *new_menu_item = menu_list->add();
	if((new_menu_item!=NULL) && (new_menu_item-> item !=NULL)) {
		new_menu_item-> item-> display = this;
		new_menu_item-> item-> attrib.gfx = &gfx;
		new_menu_item-> item-> attrib.scalex = attrib.scalex;
		new_menu_item-> item-> attrib.scaley = attrib.scaley;
		//new_menu_item-> item-> attrib.offsetx = attrib.scalex/2;
		//new_menu_item-> item-> attrib.offsety = attrib.scaley/2;
		new_menu_item-> item-> button_sizex = attrib.scalex-1;
		new_menu_item-> item-> button_sizey = attrib.scaley-1;
//		new_menu_item-> item-> stepx = attrib.scale;
		new_menu_item-> item-> title = _title;
		return new_menu_item-> item;
	}
	return NULL;
}
//-------------------------------
 */


//###############################################################################
//void ChemDisplay::draw_box(int min_xpos, int min_ypos, int max_xpos,int max_ypos) {
// draw
void ChemDisplay::draw_cellbox(ChemDisplayAttrib *screen_attrib, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title){
	if (screen_attrib==NULL) return;
/*
	//PRINT("start: [%d,%d]->[%d,%d]\n", min_xpos, min_ypos, max_xpos, max_ypos);
	int minx = attrib.screenx(attrib.offsetx, min_xpos);// - attrib.scalex/2;
	int maxx = attrib.screenx(attrib.offsetx, max_xpos);// + attrib.scalex/2;
	// screen y cords inverted
	int maxy = attrib.screeny(attrib.offsety, min_ypos);// - attrib.scaley/2;
	int miny = attrib.screeny(attrib.offsety, max_ypos);// + attrib.scaley/2;
	//PRINT("screen.min[%d,%d]screen.max[%d,%d]\n", minx, miny, maxx, maxy);
*/
	int minx = screen_attrib-> screenx(&gfx, screen_attrib-> offsetx, min_xpos);// - attrib.scalex/2;
	int maxx = screen_attrib-> screenx(&gfx, screen_attrib-> offsetx, max_xpos);// + attrib.scalex/2;
	// screen y cords inverted
	int maxy = screen_attrib-> screeny(&gfx, screen_attrib-> offsety, min_ypos);// - attrib.scaley/2;
	int miny = screen_attrib-> screeny(&gfx, screen_attrib-> offsety, max_ypos);// + attrib.scaley/2;

	//PRINT("==: [%d,%d]->[%d,%d]\n", minx, miny, maxx, maxy);


	int px = minx+((maxx-minx)/2);
	int py = miny+((maxy-miny)/2);
	//PRINT("scale[%d,%d]\n", attrib.scalex, attrib.scaley);

//	int sx = (maxx-minx)/2 + (attrib.scalex/2);
//	int sy = (maxy-miny)/2 + (attrib.scaley/2);
	int sx = (maxx-minx)/2 + (screen_attrib-> scalex/2);
	int sy = (maxy-miny)/2 + (screen_attrib-> scaley/2);
	//int sy = (max_posy - min_posy) * attrib.scaley/2;

	gfx.box(px,py, sx , sy , _title);
	//PRINT("offset[%d,%d] size[%d,%d]\n",  px,  py, sx, sy);
}
//----------------------------------------------------------
//------------------------------
void ChemDisplay::draw_menu_border(ChemDisplayAttrib *screen_attrib, ChemMenu *menu){
	if (screen_attrib==NULL) return;
	if (menu==NULL) return;
	gfx.color(0,0,100);
	draw_box(screen_attrib, menu-> min_posx, menu-> min_posy, menu-> max_posx, menu-> max_posy);
}
//------------------------------
void ChemDisplay::draw_menu(ChemDisplayAttrib *screen_attrib, ChemMenu *menu){
	if (screen_attrib==NULL) return;
	if (menu==NULL) return;

	//PRINT("======\n");	menu-> dump();	PRINT("======\n");
//	if (menu-> display==NULL) return;
	ChemDisplayColor *c = &menu-> col;

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = menu-> button_list.gethead();
	//DUMP(current_item)  NL
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		if (current_item-> item->_selected)		c = &menu-> selcol;
		else 									c = &menu-> col;


		//PRINT("== > draw button\n");
		//draw_button(screen_attrib, current_item-> item, c);
		draw_button(screen_attrib, current_item-> item, c);
		//-----
		current_item = current_item-> next;
	}
	//draw_menu_border(screen_attrib, menu);
	draw_menu_border(&menu-> attrib, menu);
	//PRINT("==== end = >\n");
};


// void ChemMenuButton::draw(ChemDisplay *display, ChemDisplayColor *col) {
void ChemDisplay::draw_button(ChemDisplayAttrib *screen_attrib, ChemMenuButton *button, ChemDisplayColor *col) {
	if (screen_attrib==NULL) return;
	if (button==NULL) return;
	//button-> dump();
	if (col==NULL) return;
	int x = button-> attrib.screenx(&gfx);
	int y = button-> attrib.screeny(&gfx);

	gfx.color(col-> r, col-> g, col-> b);
	gfx.box(x,y,button-> sizex/2, button-> sizey/2, button-> gettext());
	if (button-> gettext()!=NULL)	gfx.text(button-> gettext(), x, y);
}

//------------
void ChemDisplay::draw_screen(ChemScreen *screen, Concentration_CLI *cli){
	if (screen==NULL) return;
	if (screen-> menu_list==NULL) return;

	//attrib.cp(&screen-> attrib);	// PRINT("display attribs :"); attrib.dump();

	gfx.open();

	while(true) {
		//=======================
		gfx.clear();
		grid(&screen-> attrib, 100,100,100);
		gdump();


		{ // do title =========================
			char wait_msg[32];
			// ---------------
			sprintf(wait_msg, "()");
			if (screen->waiting) {
				//enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
				switch(screen->waitmode) {
				case WAIT_CURS:
					sprintf(wait_msg, "(curs)");
					break;
					//--------------
				case WAIT_SCREEN:
					sprintf(wait_msg, "(screen)");
					break;
					//--------------
				case WAIT_OBJECT:
					sprintf(wait_msg, "(object)");
					break;
					//--------------
				}
			}


			char menu_msg[64];
			if (screen->current_menu ==NULL) {
				sprintf(menu_msg, "[]");
			} else {
				sprintf(menu_msg, "[%s]", screen->current_menu-> gettitle());
			}

			char msg[128];
			sprintf(msg, "== [%s]%s%s ==", screen-> get_title(), menu_msg, wait_msg);		gfx.printg(msg);
		} // end title =========================

		// ---------------
		// screen (render) callback
		if (screen-> renderCB !=NULL) { screen-> renderCB (cli, 0, NULL);	}

		//----------------------
		// get all menus
		mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = screen-> menu_list-> gethead();
		while ((current_item != NULL) && (current_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			draw_menu(&screen-> attrib, current_item-> item);
			//-------
			current_item = current_item->next;
		}

		// -------------------------------------------
		gfx.printg("== End Screen ==");
		//-------- wait / loop
		gfx.flush();
		if (screen-> waiting) {
			int r = screen-> wait(this);
			// allow escape out
			if (r <0) {
				gfx.close();
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
int	ChemDisplay::test_screen(ChemScreen *screen, int posx, int posy){
	if (screen==NULL) return -1;
	if (screen-> menu_list==NULL) return -2;

	mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = screen-> menu_list-> gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		//-->		current_item-> item-> draw();
		ChemMenuButton *button = current_item-> item->test_menu(posx, posy);
		if (button !=NULL) { return 1; };
		//-------
		current_item = current_item->next;
	}
	return 0;
}

//void ChemDisplay::select_screen(ChemScreen *_screen){	current_screen = _screen;}
/*
int ChemDisplay::XXwait(ChemScreen *screen) {
	//curs(200,200,0);
//		draw_menus();
	int x=0;
	int y=0;

	PRINT("# waiting ...\n");
	int w = gfx.wait();
	PRINT("# waiting.. recieved[%d]\n", w);

	//		if ((w>31)&&(w<127)) {	PRINT("# recieved[%c][%d][0x%x] [%d][%d] ...\n", w, w, w, gfx.xpos(), gfx.ypos());		}
	//		else {					PRINT("# recieved[][%d][0x%x] [%d][%d] ...\n", w, w, gfx.xpos(), gfx.ypos());		}
	if (w==27) {			PRINT("# [ESC][%d]##\n", w);	return -110;	}

	switch(w) {
	// TODO : MOUSE CLICK =====
	//
//	case 01:
	case DISPLAY_EVENT_MOUSE0:

		if (screen-> waitmode==WAIT_CURS) {
			x = attrib.getxcell(gfx.xpos());
			y = attrib.getycell(gfx.ypos());

	//		curs_pos.dim[PEPPOS_X]=x;
	//		curs_pos.dim[PEPPOS_Y]=y;
			//TODO - scan menus
		}

		break;
	// ARROWS
//	case DISPLAY_EVENT_LEFT:	curs_pos.dim[PEPPOS_X] --;	break;
//	case DISPLAY_EVENT_RIGHT:	curs_pos.dim[PEPPOS_Y] ++;	break;
//	case DISPLAY_EVENT_UP:		curs_pos.dim[PEPPOS_X] ++;	break;
//	case DISPLAY_EVENT_DOWN:	curs_pos.dim[PEPPOS_Y] --;	break;
	}

	return 0;

}
*/
//-------------------------------
ChemScreen *ChemDisplay::add_screen(const char* screen_title){

	//PRINT("ADD[%s]..\n", screen_title);
	if (screen_title==NULL) {
		PRINT("NULL screen_title");
		return NULL;
	}

	if (strlen(screen_title)==0) {
		PRINT("Empty screen_title");
		return NULL;
	}


	ChemScreen *found_screen = search_screen(screen_title);
	if (found_screen!=NULL) {
		return NULL;
	}

	mylist<ChemScreen>::mylist_item<ChemScreen> *new_item = screen_list->add();
	if ((new_item==NULL)||(new_item-> item ==NULL)) {
		return NULL;
	}
//	new_item-> item->attrib.gfx = &gfx;
	/*
	int len = strlen(screen_title)+1;
	if (len>0) {
		char *buf = (char*) malloc(sizeof(char)*len);
		if (buf==NULL) {
			PRINT("Failled to malloc title..\n");
		} else {
			strncpy(buf, screen_title, len);
			new_item-> item-> title = buf;
		}
	}
//	new_item-> item-> title = screen_title;
 */
	new_item-> item-> set_title(screen_title);
	//new_item-> item-> attrib.cp(&attrib);
	//--------------
	return new_item-> item;
}
//-------------------------------
ChemScreen *ChemDisplay::search_screen(const char* screen_title){
	ChemScreen *found_screen = NULL;
	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = screen_list->gethead();
	while ((screen_item!=NULL)&&(screen_item-> item!=NULL)) {
		if (screen_item-> item->istitle(screen_title)==0) {
			found_screen = screen_item-> item;
			break;
		}
		//---------------------
		screen_item = screen_item->next;
	}
	//------
	return found_screen;
}

//-------------------------------//-------------------------------
//-------------------------------//-------------------------------


