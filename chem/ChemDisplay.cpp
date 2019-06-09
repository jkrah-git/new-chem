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
//void ChemDisplay::XXcurs(int red, int green, int blue){
//	PRINT("curs=[%d,%d]\n", curs_pos.dim[0], curs_pos.dim[1]);
//	draw_box(curs_pos.dim[0], curs_pos.dim[1], curs_pos.dim[0], curs_pos.dim[1]);}
//-------------------------------
void ChemDisplay::grid_axis(ChemDisplayAttrib *grid_attrib, int red, int green, int blue) {
	grid_axis(grid_attrib, red, green, blue, 0, 0, 3, false);
};
//-------------------------------
void ChemDisplay::grid_axis(ChemDisplayAttrib *grid_attrib, int red, int green, int blue, int xpos, int ypos) {
	grid_axis(grid_attrib, red, green, blue, xpos, ypos, 3, false);
};
void ChemDisplay::grid_axis(ChemDisplayAttrib *grid_attrib, int red, int green, int blue, int xpos, int ypos, int axis, bool txt){


	//PRINT("== pos[%d,%d]axis[%d] ==\n", xpos, ypos, axis);
	if (grid_attrib==NULL) return;
	PepPosVecType	*gridpos = grid_attrib-> getpos();
	if (gridpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return;	}

	ChemDisplayAttrib display_attrib(grid_attrib);
	PepPosVecType	*display_pos = display_attrib.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}

	display_pos[PEPPOS_X] = gridpos[PEPPOS_X] + xpos;
	display_pos[PEPPOS_Y] = gridpos[PEPPOS_Y] + ypos;

	int px = display_attrib.screenx(&gfx);
	int py = display_attrib.screeny(&gfx);

	gfx.color(red, green, blue);
	if ((axis==PEPPOS_X) || (axis>PEPPOS_Y)) {
		gfx.color(red, green, blue);
		gfx.line(px ,0, px, gfx.height);

		if (txt) {
			char num[16];
			sprintf(num, "%d", xpos);
			gfx.color(100, 100, 10);
			gfx.text(num, px, gfx.height -10);
		}

	}
	if ((axis==PEPPOS_Y) || (axis>PEPPOS_Y)) {
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
void ChemDisplay::grid(ChemDisplayAttrib *grid_attrib, int red, int green, int blue){

	if (grid_attrib==NULL) return;
	PepPosVecType	*gridpos = grid_attrib-> getpos();
	if (gridpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return;	}

	ChemDisplayAttrib display_attrib(grid_attrib);
	PepPosVecType	*display_pos = display_attrib.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return;	}


	int x_steps = (gfx.width / grid_attrib-> scalex)/2;
	int y_steps = (gfx.height / grid_attrib-> scaley)/2;
	//PRINT("Grid <BREAK>\n"); return;
	int xinc = x_steps/20; if (xinc<1) xinc=1;
	int yinc = y_steps/20; if (yinc<1) yinc=1;

	for (int x=(-x_steps - gridpos[PEPPOS_X]); x < (x_steps - gridpos[PEPPOS_X]); x+= xinc) {
		grid_axis(grid_attrib, red, green, blue, x, 0, 0, true);
	}

	for (int y=(-y_steps - gridpos[PEPPOS_Y]); y< (y_steps - gridpos[PEPPOS_Y]); y+= yinc) {
		grid_axis(grid_attrib, red, green, blue, 0, y, 1, true);
	}

	gfx.flush();

}
//-------------------------------
Peptide *ChemDisplay::draw_pep(ChemDisplayAttrib *screen_attrib, Peptide *pep){
	if ((screen_attrib==NULL)||(pep==NULL)) return NULL;

	PepPosVecType  	*pep_pos = pep->getpos();
	if (pep_pos==NULL) return NULL;

	// --------------
	PepPosVecType	*oldpos = screen_attrib-> getpos();
	if (oldpos==NULL) {		PRINT("ERR: attrib NULL pos\n");		return NULL;	}

	ChemDisplayAttrib display_attrib(screen_attrib);

	//PRINT("display_attrib =>");	display_attrib.dump();
	PepPosVecType	*display_pos = display_attrib.getpos();
	if (display_pos==NULL) {		PRINT("ERR: display_pos NULL pos\n");		return NULL;	}
	// --------------

	display_pos[PEPPOS_X] += pep_pos[PEPPOS_X];
	display_pos[PEPPOS_Y] += pep_pos[PEPPOS_Y];

	//-------------------

	int x = display_attrib.screenx(&gfx);
	int y = display_attrib.screeny(&gfx);

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
	//-------------------
	// test cursor pos...
	Peptide *hit = NULL;
	if ((current_screen!=NULL) &&
		(current_screen->mouse_clicked) &&
		(display_pos[PEPPOS_X] == current_screen->curs_pos.dim[PEPPOS_X]) &&
		(display_pos[PEPPOS_Y] == current_screen->curs_pos.dim[PEPPOS_Y])) {
		hit = pep;
		if (current_screen->selected_pep==NULL) {
			current_screen->selected_pep = hit;
		}
	}

	return hit;
}
//-------------------------------
Molecule *ChemDisplay::draw_mole(ChemDisplayAttrib *screen_attrib, Molecule *mole, int r, int g, int b){
	if (screen_attrib==NULL) return NULL;
	ChemDisplayColor col(r,g,b);
	return draw_mole(screen_attrib, mole, &col);
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

Molecule *ChemDisplay::draw_mole(ChemDisplayAttrib *screen_attrib, Molecule *mole, ChemDisplayColor *col){
	if (screen_attrib==NULL) return NULL;

	char msg[128];
	sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) mole);
	gfx.printg(msg);
	if (mole==NULL) return NULL;

	//-------------------
	// test cursor pos...

	Molecule *hit = NULL;
	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		Peptide *pep = draw_pep(screen_attrib, current_item-> item, col);
		if (pep!=NULL) { hit = mole; }
		//---
		current_item = current_item-> next;
	}

	if ((current_screen!=NULL) &&
		(current_screen->mouse_clicked) &&
		(hit!=NULL)) {
		if (current_screen->selected_mole==NULL) {
			current_screen->selected_mole = hit;
		}
		return hit;
	}
	return NULL;


}

//-------------------------------
Molecule *ChemDisplay::draw_match(ChemDisplayAttrib *screen_attrib, MoleculeMatchPos *matchpos){
	if (screen_attrib==NULL) return NULL;
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

		mole = draw_mole(screen_attrib, matchpos-> getM1(), &m1_col);
		if ((mole!=NULL) && (hit==NULL)) { hit = mole; }
	}

	// ------------------- ROTMOLE
	if ((matchpos-> rotmole != NULL) && (matchpos-> rotmole-> pep_list.gethead() !=NULL)) {
		gfx.color(&rot_col);
		gfx.cprintg("rotemole");
//		attrib.pos = matchpos-> current_pos.dim;
//		draw_mole(matchpos-> rotmole, &rot_col);

		ChemDisplayAttrib display_attrib(screen_attrib);
		display_attrib.addpos(matchpos-> current_pos.dim);

		// PRINT("screen_attrib = "); screen_attrib-> dump(); NL
		// PRINT("display_attrib = "); display_attrib.dump(); NL


		mole = draw_mole(&display_attrib, matchpos-> rotmole, &rot_col);
		if ((mole!=NULL) && (hit==NULL)) { hit = mole; }
	}

	if (matchpos-> get_test_item()!=NULL) {
		gfx.color(&item_col);
		gfx.cprintg("test_item");
		//attrib.pos = matchpos-> current_pos.dim;
		//draw_pep(matchpos-> get_test_item()-> item);
		//display_attrib.setpos(matchpos-> current_pos.dim);

		ChemDisplayAttrib display_attrib(screen_attrib);
		display_attrib.addpos(matchpos-> current_pos.dim);

		draw_pep(&display_attrib, matchpos-> get_test_item()-> item);

	}
	//---------------
	gfx.flush();
	return hit;
}
//void draw_pepstack_row(mylist<Peptide>  *pep_list, int index, int width, int posx, posy){}
//-------------------------------
void ChemDisplay::draw_vm(ChemDisplayAttrib *screen_attrib, ChemScreen *screen, Concentration_VM *vm){
	if (screen_attrib==NULL) return;
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
			ChemDisplayAttrib display_attrib(screen_attrib);
			display_attrib.addpos(p.dim);


			char sig[16];
			//-----------------------------
			if ((pep_item==NULL)||(pep_item-> item==NULL)) {
				// draw NULL - void	draw_box(ChemDisplayAttrib *screen_attrib, int minx, int miny, int maxx,int maxy, const char *_title);
				sprintf(sig, "-");
				draw_box(&display_attrib, px, py, px, py, sig);
			} else {
				//sprintf(sig, "%d", pep_item->item->get());
				hit = draw_pep(&display_attrib, pep_item-> item);
				pep_item = pep_item->next;
			}

		} // --next x
	} // -- next y

	//---------------
	gfx.flush();
}
//###############################################################################
//void ChemDisplay::draw_box(int min_xpos, int min_ypos, int max_xpos,int max_ypos) {
// draw
void ChemDisplay::draw_box(ChemDisplayAttrib *screen_attrib, int min_xpos, int min_ypos, int max_xpos,int max_ypos, const char *_title){
	if (screen_attrib==NULL) return;

	int minx = screen_attrib-> screenx(&gfx, screen_attrib-> offsetx, min_xpos);// - attrib.scalex/2;
	int maxx = screen_attrib-> screenx(&gfx, screen_attrib-> offsetx, max_xpos);// + attrib.scalex/2;
	// screen y cords inverted
	int maxy = screen_attrib-> screeny(&gfx, screen_attrib-> offsety, min_ypos);// - attrib.scaley/2;
	int miny = screen_attrib-> screeny(&gfx, screen_attrib-> offsety, max_ypos);// + attrib.scaley/2;
	//PRINT("==: [%d,%d]->[%d,%d]\n", minx, miny, maxx, maxy);


	int px = minx+((maxx-minx)/2);
	int py = miny+((maxy-miny)/2);
	//PRINT("scale[%d,%d]\n", attrib.scalex, attrib.scaley);

	int sx = (maxx-minx)/2 + (screen_attrib-> scalex/2);
	int sy = (maxy-miny)/2 + (screen_attrib-> scaley/2);

	gfx.box(px,py, sx , sy , _title);
	//PRINT("offset[%d,%d] size[%d,%d]\n",  px,  py, sx, sy);
}
//----------------------------------------------------------
//------------------------------
//void ChemDisplay::draw_menu_border(ChemDisplayAttrib *screen_attrib, ChemMenu *menu){
void ChemDisplay::draw_menu_border(ChemMenu *menu){
	if (menu==NULL) return;
	gfx.color(200,200,200);
	draw_box(&menu->attrib, menu-> min_posx, menu-> min_posy, menu-> max_posx, menu-> max_posy, menu-> gettitle());
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
		draw_button(&menu-> attrib, current_item-> item, c);
		//-----
		current_item = current_item-> next;
	}

};
//------------------------------

void ChemDisplay::draw_button(ChemDisplayAttrib *menu_attrib, ChemMenuButton *button, ChemDisplayColor *col) {
//	if (menu_attrib==NULL) return;
	if (button==NULL) return;
	//button-> dump();
	if (col==NULL) return;

	int x = button-> attrib.screenx(&gfx);
	int y = button-> attrib.screeny(&gfx);

	gfx.color(col-> r, col-> g, col-> b);
	gfx.box(x,y,button-> sizex/2, button-> sizey/2, button-> gettext(), true);
	gfx.box(x,y,button-> sizex/2, button-> sizey/2, button-> gettext(), true);
	if (button-> gettext()!=NULL)	gfx.text(button-> gettext(), x, y);
}

//-------------------------------------------
void ChemDisplay::draw_screen(ChemScreen *screen, Concentration_CLI *cli){
	if (cli==NULL) return;
	if (screen==NULL) return;
	if (screen-> menu_list==NULL) return;

	//attrib.cp(&screen-> attrib);	// PRINT("display attribs :"); attrib.dump();

	gfx.open();

	while(true) {
		//=======================
		gfx.clear();
		//-----------

		// title ================
		//=======================
		// --- grid
		char grid_msg[32];
		sprintf(grid_msg, "%s", "");
		//if (screen-> gridmode==GRID_OFF) {	sprintf(grid_msg, "off");	}

		if (screen-> gridmode==GRID_MOLE) {
			//grid(&screen-> attrib, 50,50,50);
			//			screen-> attrib.getpos()[PEPPOS_X],
			grid(&screen-> attrib, 50,50,50);
			grid_axis(&screen-> attrib, 150,150,150);
			sprintf(grid_msg, "mole");
		}

		if (screen-> gridmode==GRID_MENU) {
			ChemDisplayAttrib display_attribs(&screen-> current_menu-> attrib);
			display_attribs.setpos(0,0);
			grid(&display_attribs, 50,0,0);
			grid_axis(&display_attribs, 100,0,0);

			grid_axis(&screen-> attrib, 50,50,50);
			sprintf(grid_msg, "menu");
		}

		char wait_msg[32];
		sprintf(wait_msg, "%s", "");
		if (screen->waiting) {
			//enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
			switch(screen->waitmode) {
			case WAIT_CURS:
				sprintf(wait_msg, "curs");
				break;
				//--------------
			case WAIT_SCREEN:
				sprintf(wait_msg, "screen");
				break;
				//--------------
			case WAIT_OBJECT:
				sprintf(wait_msg, "object");
				break;
				//--------------
			}
		}

		char menu_msg[64];
		if (screen->current_menu !=NULL) { sprintf(menu_msg, "%s", screen->current_menu-> gettitle()); }
		else 							 { sprintf(menu_msg, "%s", ""); }

		char msg[256];
		sprintf(msg, "Screen[%s] Menu[%s] Wait[%s] Grid[%s]",
				screen-> get_title(),
				menu_msg,
				wait_msg,
				grid_msg );

		gfx.color(255,255,255);
		gfx.cprintg(msg);

		sprintf(msg, "..Pos[%d,%d] Scale[%d,%d] Offs[%d,%d]",
				screen-> attrib.getposx(),	screen-> attrib.getposy(),
				screen-> attrib.scalex,	screen-> attrib.scaley,
				screen-> attrib.offsetx, screen-> attrib.offsety);
		gfx.printg(msg);

		sprintf(msg, "..SelectedPep[0x%zX], SelectedMole[0x%zX]",
				(long unsigned int) screen-> selected_pep,
				(long unsigned int) screen-> selected_mole);
		gfx.printg(msg);

		// end title =========================

		// ---------------
		// screen (render) callback
		if (screen-> renderCB ==NULL) {
			sprintf(msg, "No Render..");
			gfx.printg(msg);

		} else	{
			sprintf(msg, "Render..");
			gfx.printg(msg);
			screen-> renderCB (cli, 0, NULL);
		}

		//----------------------
		// get all menus
		mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = screen-> menu_list-> gethead();
		while ((current_item != NULL) && (current_item-> item != NULL)) {
		//	PRINT("==== menu = >\n");	//	current_item-> item-> dump(); NL	//	PRINT("<====\n");
			//draw_menu(&screen-> attrib, current_item-> item);
			draw_menu(current_item-> item);
			//-------
			current_item = current_item->next;
		}

		// -------------------------------------------
		gfx.printg((const char*) "End(screen).");
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

	new_item-> item-> set_title(screen_title);
	//--------------
	return new_item-> item;
}
//-------------------------------
ChemScreen *ChemDisplay::search_screen(const char* screen_title){
	//ChemScreen *found_screen = NULL;

	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = screen_list->gethead();
	while ((screen_item!=NULL)&&(screen_item-> item!=NULL)) {
		if (screen_item-> item->istitle(screen_title)==0) {
			//found_screen = screen_item-> item; 			break;
			return screen_item-> item;
		}
		//---------------------
		screen_item = screen_item->next;
	}
	//------
	return NULL;
}

//-------------------------------//-------------------------------
//-------------------------------//-------------------------------


