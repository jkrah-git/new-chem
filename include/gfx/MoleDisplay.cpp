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
//-------------------------------
MoleDisplay::MoleDisplay() {
	ysize = 800;
	xsize = 600;
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
MoleDisplay::~MoleDisplay() {}
//-------------------------------
void MoleDisplay::open(){
	gfx_open(xsize,ysize,"MoleDisplay");
	gfx_clear();
}
//-------------------------------

int	MoleDisplay::screenx(void){
	int px = (xsize/2) + offsetx;
	if (pos !=NULL)	px += (pos[PEPPOS_X] * scale);
	return px;
}
//-------------------------------
int	MoleDisplay::screeny(void){
	int py = (ysize/2) + offsety;
	if (pos !=NULL)	py += (pos[PEPPOS_Y] * scale);
	return (ysize-py);
}
//-------------------------------
void MoleDisplay::grid(){
	PeptidePos p;
	pos = p.dim;
	if (pos==NULL) return;

	int x_steps = (xsize / scale)/2;
	int y_steps = (ysize / scale)/2;


	for (int x=-x_steps; x < x_steps; x++) {
		pos[PEPPOS_X] = x;
		int px = screenx();
		if (x==0)
			gfx_color(colr,colg,colb);
		else
			gfx_color(colr*2, colg*2, colb*2);

		gfx_line(px ,0, px, ysize);
	}

	for (int y=-y_steps; y<y_steps; y++) {
		pos[PEPPOS_Y] = y;
		int py = screeny();
		if (y==0)
			gfx_color(colr,colg,colb);
		else
			gfx_color(colr*2, colg*2, colb*2);

		gfx_line(0, py, xsize, py);

	}
	gfx_flush();

}
//-------------------------------
void MoleDisplay::draw_pep(Peptide *pep) {

	if (pep==NULL) return;
	pos = pep->getpos();
	int x = screenx();
	int y = screeny();
	int s = scale/2;

	gfx_color(colr, colg, colb);
	gfx_line(x-s, y-s, x+s, y-s);
	gfx_line(x+s, y-s, x+s, y+s);
	gfx_line(x+s, y+s, x-s, y+s);
	gfx_line(x-s, y+s, x-s, y-s);

	setcol(200,200,200);
	char str[8];
	sprintf(str, "0x%x", pep-> get());
	gfx_text(str,x,y);

	gfx_flush();

}

//-------------------------------
/*
void MoleDisplay::draw_pep(Peptide *pep, int colr, int colg, int colb, PeptidePos *pos){
	if ((pep==NULL)||(pos==NULL)) return;
	Peptide pep2;
	pep2.set(pep-> get());
	pep2.pos.dim[0] = pep-> pos.dim[0] + pos-> dim[0];
	pep2.pos.dim[1] = pep-> pos.dim[1] + pos-> dim[1];

	pep2.setpos()
	draw_pep(&pep2, colr, colg, colb);


}
//-------------------------------
void MoleDisplay::draw_mole(Molecule *mole, int colr, int colg, int colb, int offsetx, int offsety){
	if (mole==NULL) return;

	mylist<Peptide>::mylist_item<Peptide> *current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		draw_pep(current_item-> item, colr, colg, colb, offsetx, offsety);

		//---
		current_item = current_item-> next;
	}
	//gfx_flush();
}

void MoleDisplay::draw_mole(Molecule *mole, int colr, int colg, int colb, PeptidePos *pos){

	if ((mole==NULL)||(pos==NULL)) return;
	mylist<Peptide>::mylist_item<Peptide> *current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		draw_pep(current_item-> item, colr, colg, colb, pos);

		//---
		current_item = current_item-> next;
	}


}
*/
void MoleDisplay::draw_mole(Molecule *mole){

	if (mole==NULL) return;

	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
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
	//draw_mole(matchpos-> rotmole, 0, 100, 0, &matchpos-> current_pos);
	setcol(0,100,0);
	draw_mole(matchpos-> rotmole);


	if (matchpos-> get_test_item()!=NULL) {
		//draw_pep(matchpos-> get_test_item()-> item, 100, 100, 100,  &matchpos-> current_pos );
	}

	char str[32];
	sprintf(str, "Rot: %d", matchpos-> rotation);
	gfx_color(200,200,200);
	gfx_text(str, 10, 10);
	gfx_flush();
}
