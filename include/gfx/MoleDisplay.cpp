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
	gfx.line_height = 30;
	scale = 30;
	clearatt();
}
//-------------------------------
void MoleDisplay::clearatt(){
	colr = 0;
	colg = 0;
	colb = 0;
	offsetx = 0;
	offsety = 0;
	pos = NULL;
}
//-------------------------------
//void MoleDisplay::cls(){
	//line_pos = DISPLAY_FONT_HEIGHT;
//	gfx.clear();
//}
//-------------------------------
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
/*
void MoleDisplay::printg(char *str){
	if (str==NULL) return;
	if (line_pos >= gfx.height) return;
	int x = 0;
	gfx.color(200,200,200);
	gfx.text(str,x,line_pos);
	line_pos+= DISPLAY_FONT_HEIGHT;

	gfx.flush();
}
*/
//-------------------------------
void MoleDisplay::gdump() {
	char msg[128];
	sprintf(msg, "MoleDisplay[0x%zX].", (long unsigned int) this);
	gfx.printg(msg);

	sprintf(msg, "size[%d,%d].scale[%d].col[%d,%d,%d].off[%d,%d].pos[0x%zX]\n",
			gfx.width, gfx.height, scale, colr, colg, colb, offsetx, offsety, (long unsigned int)  pos);
	gfx.printg(msg);

	if (pos !=NULL) {
		sprintf(msg, ".. pos[%d,%d,%d]\n", pos[0], pos[1], pos[2]);
		gfx.printg(msg);
	}

}
//-------------------------------
void MoleDisplay::open(){
	//gfx.open(width,height,"MoleDisplay");
	gfx.clear();
}
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
void MoleDisplay::grid(){
	PeptidePos p;
	pos = p.dim;
	if (pos==NULL) return;

	int x_steps = (gfx.width / scale)/2;
	int y_steps = (gfx.height / scale)/2;


	for (int x=-x_steps; x < x_steps; x++) {
		pos[PEPPOS_X] = x;
		int px = screenx();
		if (x==0)
			gfx.color(colr*2,colg*2,colb*2);
		else
			gfx.color(colr, colg, colb);

		gfx.line(px ,0, px, gfx.height);
	}

	for (int y=-y_steps; y<y_steps; y++) {
		pos[PEPPOS_Y] = y;
		int py = screeny();
		if (y==0)
			gfx.color(colr*2,colg*2,colb*2);
		else
			gfx.color(colr, colg, colb);

		gfx.line(0, py, gfx.width, py);

	}
	gfx.flush();

}
//-------------------------------
void MoleDisplay::draw_pep(Peptide *pep) {

	if (pep==NULL) return;
	PeptidePos new_peppos;
	PepPosVecType *newpos = new_peppos.dim;

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

	char str[8];
	sprintf(str, "0x%x", pep-> get());
	gfx.color(200,200,200);
	gfx.text(str,x,y);

	//-------------
	// (newpos leaving scope)
	pos = NULL;
	gfx.flush();

}

//-------------------------------

void MoleDisplay::draw_mole(Molecule *mole){

	if (mole==NULL) return;
	PepPosVecType *globalpos = pos;

	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		// fix: bug afger firsr pep - reload pos
		pos = globalpos;
		draw_pep(current_item-> item);
		//---
		current_item = current_item-> next;
	}

}

//-------------------------------
void MoleDisplay::draw_match(MoleculeMatchPos *matchpos){
	if (matchpos==NULL) return;

	setcol(100,0,0);
	draw_mole(matchpos-> getM1()); //, 100, 0, 0);

	pos = matchpos-> current_pos.dim;
	setcol(0,100,0);
	draw_mole(matchpos-> rotmole);


	if (matchpos-> get_test_item()!=NULL) {
		setcol(100,100,100);
		draw_pep(matchpos-> get_test_item()-> item);
	}

	gfx.color(200,200,200);
	char str[32];

	int tx=10, ty=10;
	sprintf(str, "Rot: %d", matchpos-> rotation);	gfx.text(str, tx, ty); ty+=20;
	sprintf(str, "Pos[%d,%d] Rot[%d]",
			matchpos-> current_pos.dim[PEPPOS_X],
			matchpos-> current_pos.dim[PEPPOS_Y],
			matchpos-> current_pos.dim[PEPPOS_ROT]);
	gfx.text(str, tx, ty); ty+=20;
	gfx.flush();
}
