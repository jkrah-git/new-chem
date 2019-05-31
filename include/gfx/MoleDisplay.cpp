/*
 * MoleDisplay.cpp
 *
 *  Created on: May 20, 2019
 *      Author: jkrah
 */

#include "MoleDisplay.h"

/*
//-----------------
class MoleDisplay {
private:
	int	screenx(int pep_posx);
	int	screeny(int pep_posy);

public:
	int 		ysize;
	int 		xsize;
	int 		scale;
	int 		colr;
	int 		colg;
	int 		colb;
	int 		offsetx;
	int 		offsety;
	PeptidePos	*pos;

	MoleDisplay();
	virtual ~MoleDisplay();
	//-----------
	void	open();
	void	grid();
//	void	draw_pep(Peptide *pep, int colr, int colg, int colb){	draw_pep(pep, colr, colg, colb, 0, 0, NULL); }
//	void	draw_pep(Peptide *pep, int colr, int colg, int colb, int offsetx, int offsety);
//	void	draw_pep(Peptide *pep, int colr, int colg, int colb, PeptidePos *pos);
	void	draw_pep(Peptide *pep); //, int colr, int colg, int colb, int offsetx, int offsety, PeptidePos *pos);

//	void	draw_mole(Molecule *mole, int colr, int colg, int colb) { draw_mole(mole, colr, colg, colb, 0, 0); }
//	void	draw_mole(Molecule *mole, int colr, int colg, int colb, int offsetx, int offsety);
//	void	draw_mole(Molecule *mole, int colr, int colg, int colb, PeptidePos *pos);
	void	draw_mole(Molecule *mole); //, int colr, int colg, int colb, int offsetx, int offsety, PeptidePos *pos);

	void	draw_match(MoleculeMatchPos *matchpos);
};
//--------------

 */

#define  DISPLAY_FONT_HEIGHT 10

//-------------------------------
MoleDisplay::MoleDisplay() {
	//line_pos = DISPLAY_FONT_HEIGHT;
	gfx.title = "NewMoles";
	gfx.width = 800;
	gfx.height = 600;
	scale = 40;
	clearatt();
}
//-------------------------------
void MoleDisplay::clearatt(){
	offsetx = 0;
	offsety = 0;
	pos = NULL;
}
//-------------------------------
MoleDisplay::~MoleDisplay() {}
//-------------------------------
void MoleDisplay::dump() {
	printf("MoleDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d].scale[%d].col[%d,%d,%d].off[%d,%d].pos[0x%zX]\n",
			gfx.width, gfx.height, scale, colr, colg, colb, offsetx, offsety, (long unsigned int)  pos);
	if (pos !=NULL) {
		printf(".. pos[%d,%d,%d]\n", pos[0], pos[1], pos[2]);
	}
}
//-------------------------------
void MoleDisplay::gdump() {
	char msg[128];

	sprintf(msg, "MoleDisplay[0x%zX].", (long unsigned int) this);
	gfx.printg(msg);
	sprintf(msg, "size[%d,%d].scale[%d].col[%d,%d,%d].off[%d,%d].pos[0x%zX]",
			gfx.width, gfx.height, scale, colr, colg, colb, offsetx, offsety, (long unsigned int)  pos);
	gfx.printg(msg);

	if (pos !=NULL) {
		sprintf(msg, ".. pos[%d,%d,%d]", pos[0], pos[1], pos[2]);
		gfx.printg(msg);
	}

}
//-------------------------------
//void MoleDisplay::open(){ gfx.open(width,height,"MoleDisplay");	gfx.clear();}
//-------------------------------

int	MoleDisplay::screenx(void){
	int px = (gfx.width/2) + offsetx;
	if (pos !=NULL)	{
		px += (pos[PEPPOS_X] * scale);
	}
	return px;
}
//-------------------------------
int	MoleDisplay::screeny(void){
	int py = (gfx.height/2) + offsety;
	if (pos !=NULL)	{
		py += (pos[PEPPOS_Y] * scale);
	}
	return (gfx.height-py);
}
//-------------------------------
void MoleDisplay::grid(int red, int green, int blue){
	PeptidePos p;
	pos = p.dim;
	if (pos==NULL) return;

	//gfx.color(red, green, blue);

	int x_steps = (gfx.width / scale)/2;
	int y_steps = (gfx.height / scale)/2;


	for (int x=-x_steps; x < x_steps; x++) {
		pos[PEPPOS_X] = x;
		int px = screenx();
		if (x==0)
			gfx.color(red, green, blue);
		else
			gfx.color(red/2, green/2, blue/2);

		gfx.line(px ,0, px, gfx.height);
	}

	for (int y=-y_steps; y<y_steps; y++) {
		pos[PEPPOS_Y] = y;
		int py = screeny();
		if (y==0)
			gfx.color(red, green, blue);
		else
			gfx.color(red/2, green/2, blue/2);

		gfx.line(0, py, gfx.width, py);

	}
	gfx.flush();

}
//-------------------------------
void MoleDisplay::draw_pep(Peptide *pep) {
	draw_pep(pep ,NULL);
}
//-------------------------------
void MoleDisplay::draw_pep(Peptide *pep, Peptide *previous) {
	// TODO: maybe this pos thing was a bad idea

	if (pep==NULL) return;

	PeptidePos new_peppos;
	PepPosVecType *newpos = new_peppos.dim;
	PepPosVecType *saved_pos = pos;


	// if no base offset
	if (pos==NULL) {
		// then just use pep.pos
		pos= pep->getpos();
	} else { // pos != NULL

		PepPosVecType *pep_pos = pep->getpos();
		// newpos = pos + pep_pos
		for (int i=0; i<PepPosVecMax; i++){
			newpos[i] = pos[i];
			if (pep_pos!=NULL) {
				newpos[i] += pep_pos[i];
			}
		} //----
		pos= newpos;
	}

	int x = screenx();
	int y = screeny();
	int s = scale/2;

	gfx.color(colr, colg, colb);
	gfx.line(x-s, y-s, x+s, y-s);
	gfx.line(x+s, y-s, x+s, y+s);
	gfx.line(x+s, y+s, x-s, y+s);
	gfx.line(x-s, y+s, x-s, y-s);


	int t = s/2;
	switch (pep-> getrot()) {
	case 0:
		gfx.line(x-t, y+s, x, y+t);
		gfx.line(x+t, y+s, x, y+t);
		break;
	case 1:
		gfx.line(x-s, y-t, x-t, y);
		gfx.line(x-s, y+t, x-t, y);
		break;
	case 2:
		gfx.line(x-t, y-s, x, y-t);
		gfx.line(x+t, y-s, x, y-t);
		break;
	case 3:
		gfx.line(x+s, y-t, x+t, y);
		gfx.line(x+s, y+t, x+t, y);
		break;
	}


	char str[64];
	sprintf(str, "0x%x", pep-> get());	gfx.color(200,200,200);	gfx.text(str,x-gfx.line_height/2,y+gfx.line_height/2);

	sprintf(str, "sig[0x%x].pos[%d,%d].rot[%d]", pep-> get(), pep->pos.dim[PEPPOS_X], pep->pos.dim[1], pep->rot);
	gfx.printg(str);

/*

	int oldx = x;
	int oldy = y;
	//----------------------------------------
	if (previous !=NULL) {
		sprintf(str, "(PREV)0x%x", previous-> get());
		gfx.printg(str);

		pos = saved_pos;
		// if no base offset
		if (pos==NULL) {
			// then just use pep.pos
			pos= previous->getpos();
		} else { // pos != NULL

			PepPosVecType *pep_pos = previous->getpos();
			// newpos = pos + pep_pos
			for (int i=0; i<PepPosVecMax; i++){
				newpos[i] = pos[i];
				if (pep_pos!=NULL) {
					newpos[i] += pep_pos[i];
				}
			} //----
			pos= newpos;
		}
		gfx.color(colr, colg, colb);
		x = screenx();
		y = screeny();
		gfx.line(oldx, oldy, x, y );

	}
*/

	//-------------
	// (newpos leaving scope)
	pos = saved_pos;
	gfx.flush();

}

//-------------------------------

void MoleDisplay::draw_mole(Molecule *mole){

	if (mole==NULL) return;
	//PepPosVecType *globalpos = pos;

	Peptide *previous = NULL;

	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		// (local) pos = destroyed by render_pep
		//pos = globalpos;
		draw_pep(current_item-> item, previous);
		previous = current_item-> item;
		//---
		current_item = current_item-> next;
	}

}

//-------------------------------
void MoleDisplay::draw_match(MoleculeMatchPos *matchpos){
	if (matchpos==NULL) return;

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
		setcol(200,0,0);
		gfx.cprintg((const char*) "M1");
		draw_mole(matchpos-> getM1()); //, 100, 0, 0);
	}

	if ((matchpos-> rotmole != NULL) && (matchpos-> rotmole-> pep_list.gethead() !=NULL)) {
		//printf("########### ROTMOLE ############\n");
		//matchpos-> rotmole-> dump();
		//printf("########### ROTMOLE ############\n");
		pos = matchpos-> current_pos.dim;
		setcol(0,100,0);
		gfx.cprintg("rotemole");
		pos = matchpos-> current_pos.dim;
		draw_mole(matchpos-> rotmole);
	}

	if (matchpos-> get_test_item()!=NULL) {
		setcol(100,100,100);
		gfx.cprintg("test_item");
		pos = matchpos-> current_pos.dim;
		draw_pep(matchpos-> get_test_item()-> item);
	}

	//---------------
	gfx.flush();
}

//-------------------------------
