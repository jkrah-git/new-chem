/*
 * VMDisplay.cpp
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#include "ChemDisplay.h"
//#include "ChemMenuList.h"
#define  DISPLAY_FONT_HEIGHT 10
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
ChemDisplay::ChemDisplay() {
	//line_pos = DISPLAY_FONT_HEIGHT;
	gfx.title = "NewChem";
	gfx.width = 1000;
	gfx.height = 800;
	attrib.scalex = 30;
	attrib.scaley = 20;

	core = NULL;
	pep = NULL;
	mole = NULL;
	conc = NULL;
	concvol = NULL;
	matchpos = NULL;
	menu_list = NULL;
	attrib.gfx = &gfx;
	//clearatt();
}
//-------------------------------
//-------------------------------
//---- new
void ChemDisplay::draw_regs(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue){


}
//-------------------------------
void ChemDisplay::draw_pep(Peptide *pep, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue){

}
//-------------------------------
void ChemDisplay::draw_mole(Peptide *mole, int offsetx, int offsety, PepPosVecType *pos, float scale, int red, int green, int blue){

}
//-------------------------------


//-------------------------------
//-------------------------------	//-------------------------------
//- OLD  ------------------------------
/*
void ChemDisplay::clearatt(){
	attrib.offsetx = 0;
	attrib.offsety = 0;
	attrib.pos = NULL;
}
*/
//-------------------------------
ChemDisplay::~ChemDisplay() {}
//-------------------------------
void ChemDisplay::dump() {
	printf("ChemDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d].scale[%d,%d].off[%d,%d].pos[0x%zX]\n",
			gfx.width, gfx.height, attrib.scalex, attrib.scaley, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos);
			//gfx.width, gfx.height, attrib.scale, col.r, col.g, col.b, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos);
	if (attrib.pos !=NULL) {
		printf(".. pos[%d,%d,%d]\n", attrib.pos[0], attrib.pos[1], attrib.pos[2]);
	}
}
//-------------------------------
void ChemDisplay::gdump() {
	char msg[256];

	//sprintf(msg, "ChemDisplay[0x%zX].", (long unsigned int) this);
	//gfx.printg(msg);
//	sprintf(msg, "size[%d,%d].scale[%f].col[%d,%d,%d].off[%d,%d].pos[0x%zX]",
//			gfx.width, gfx.height, attrib.scale, col.r, col.g, col.b, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos);
	sprintf(msg, "ChemDisplay[0x%zX][%s].size[%d,%d].scale[%d, %d].off[%d,%d].pos[0x%zX] CursPos[%d,%d]",
			(long unsigned int) this,
			gfx.title,
			gfx.width, gfx.height, attrib.scalex, attrib.scaley, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos,
			curs_pos.dim[PEPPOS_X], curs_pos.dim[PEPPOS_Y] );
	gfx.printg(msg);

	if (attrib.pos !=NULL) {
		sprintf(msg, ".. pos[%d,%d,%d]", attrib.pos[0], attrib.pos[1], attrib.pos[2]);
		gfx.printg(msg);
	}

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
void ChemDisplay::curs(int red, int green, int blue){
	Peptide curs;
	curs.sig = '?';
	curs.pos =  curs_pos;
	draw_pep(&curs, red, green, blue);
}
//-------------------------------
void ChemDisplay::grid(int red, int green, int blue){

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
	int x_steps = (gfx.width / attrib.scalex)/2;
	int y_steps = (gfx.height / attrib.scaley)/2;


	for (int x=(-x_steps-oldposx); x < (x_steps-oldposx); x++) {
		attrib.pos[PEPPOS_X] = x+oldposx;
		int px = attrib.screenx();
		if (x==0)	gfx.color(red, green, blue);
		else		gfx.color(red/2, green/2, blue/2);

		gfx.line(px ,0, px, gfx.height);
	}

	for (int y=(-y_steps-oldposy); y< (y_steps-oldposy); y++) {
		attrib.pos[PEPPOS_Y] = y+oldposy;
		int py = attrib.screeny();
		if (y==0)	gfx.color(red, green, blue);
		else		gfx.color(red/2, green/2, blue/2);

		gfx.line(0, py, gfx.width, py);

	}

	if (attrib.pos!=NULL) {
		attrib.pos[PEPPOS_X] = oldposx;
		attrib.pos[PEPPOS_Y] = oldposy;
	}


	gfx.flush();
	attrib.pos = oldpos;

}
//-------------------------------
void ChemDisplay::draw_pep(Peptide *pep){ //, ChemDisplayColor *_col) {

	if (pep==NULL) return;

	PeptidePos new_peppos;
	PepPosVecType *newpos = new_peppos.dim;
	PepPosVecType *saved_pos = attrib.pos;


	// if no base offset
	if (attrib.pos==NULL) {
		// then just use pep.pos
		attrib.pos= pep->getpos();
	} else { // pos != NULL

		PepPosVecType *pep_pos = pep->getpos();
		// newpos = pos + pep_pos
		for (int i=0; i<PepPosVecMax; i++){
			newpos[i] = attrib.pos[i];
			if (pep_pos!=NULL) {
				newpos[i] += pep_pos[i];
			}
		} //----
		attrib.pos= newpos;
	}

	int x = attrib.screenx();
	int y = attrib.screeny();
	int sx = attrib.scalex/2;
	int sy = attrib.scaley/2;

//	gfx.line(x-s, y-s, x+s, y-s);
//	gfx.line(x+s, y-s, x+s, y+s);
//	gfx.line(x+s, y+s, x-s, y+s);
//	gfx.line(x-s, y+s, x-s, y-s);
	gfx.box(x,y,sx, sy);

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
	sprintf(str, "0x%x", pep-> get());	gfx.color(200,200,200);	gfx.text(str,x-gfx.line_height/2,y+gfx.line_height/2);

	sprintf(str, "sig[0x%x].pos[%d,%d].rot[%d]", pep-> get(), pep->pos.dim[PEPPOS_X], pep->pos.dim[PEPPOS_Y], pep->rot);
	gfx.printg(str);

	//-------------
	// (restore pos)
	attrib.pos = saved_pos;
	gfx.flush();

}
//-------------------------------
void ChemDisplay::draw_mole(Molecule *mole, int r, int g, int b){
	ChemDisplayColor col(r,g,b);
	draw_mole(mole, &col);
}
//-------------------------------
void ChemDisplay::draw_mole(Molecule *mole, ChemDisplayColor *col){

	if (mole==NULL) return;
	//PepPosVecType *globalpos = pos;

	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		draw_pep(current_item-> item, col);
		//---
		current_item = current_item-> next;
	}

}

//-------------------------------
void ChemDisplay::draw_match(MoleculeMatchPos *matchpos){
	if (matchpos==NULL) return;

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
		draw_mole(matchpos-> getM1(), &m1_col);
	}

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
void ChemDisplay::draw_menus(void){
	if (menu_list==NULL) return;

	mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = menu_list-> gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		current_item-> item-> draw();
		//-------
		current_item = current_item->next;
	}

}
//-------------------------------
int ChemDisplay::main(int argc, char **argv) {
	if (core==NULL) { PRINT("[null core]\n"); return -1; }
	if (menu_list==NULL) { PRINT("[null menu_list]\n"); return -2; }

	//gfx.title = (const char*) "- NewChem -";
	gfx.open();
	PRINT("-----RENDER ----\n");
	while(true) {
		gfx.clear();
		grid(100,100,100);
		gdump();


		if (menu_list!=NULL) {
			// clear the list
			menu_list-> clear();

			ChemMenu *menu = add_menu("test_menu");
			if (menu!=NULL) {
				menu-> add_button("A");
				menu-> add_button("B");
				menu-> add_button("C");
				menu->layout_buttons();
				menu-> dump();
			}

			//menu_list-> dump();
		}

		curs(200,200,0);
		draw_menus();
		int x=0;
		int y=0;

		PRINT("# waiting ...\n");
		int w = gfx.wait();
//		if ((w>31)&&(w<127)) {	PRINT("# recieved[%c][%d][0x%x] [%d][%d] ...\n", w, w, w, gfx.xpos(), gfx.ypos());		}
//		else {					PRINT("# recieved[][%d][0x%x] [%d][%d] ...\n", w, w, gfx.xpos(), gfx.ypos());		}
		if (w==27) {			PRINT("# [ESC][%d]##\n", w);	break;	}

		switch(w) {
		// MOUSE CLICK
		case 01:	//curs_pos.dim[PEPPOS_X] --;
			x = attrib.getxcell(gfx.xpos());
			y = attrib.getycell(gfx.ypos());
	//		PRINT("mouse: xcell[%d,%d]", x, y);
			curs_pos.dim[PEPPOS_X]=x;
			curs_pos.dim[PEPPOS_Y]=y;
			break;
		// ARROWS
		case 81:	curs_pos.dim[PEPPOS_X] --;	break;
		case 82:	curs_pos.dim[PEPPOS_Y] ++;	break;
		case 83:	curs_pos.dim[PEPPOS_X] ++;	break;
		case 84:	curs_pos.dim[PEPPOS_Y] --;	break;
		}

	}
	// -------------------------------

	PRINT("# done ...\n");
	gfx.close();
	return 0;
}
//-------------------------------

//-------------------------------//-------------------------------
//-------------------------------//-------------------------------


