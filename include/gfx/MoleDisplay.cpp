/*
 * MoleDisplay.cpp
 *
 *  Created on: May 20, 2019
 *      Author: jkrah
 */

#include "MoleDisplay.h"

/*
 	int ysize = 300;
	int xsize = 300;

	gfx_open(xsize,ysize,"Example Graphics Program");

	gfx_clear();
	// Set the current drawing color to green.
	gfx_color(0,200,100);

	// Draw a triangle on the screen.
	gfx_line(100,100,200,100);
	gfx_line(200,100,150,150);
	gfx_line(150,150,100,100);

	char str[16];
	sprintf(str, "argv: %s\0",argv[0]);
	gfx_text(str,80,80);

	gfx_flush();

 */
//-------------------------------
MoleDisplay::MoleDisplay() {
	ysize = 300;
	xsize = 300;
	scale = 20;
}
//-------------------------------
MoleDisplay::~MoleDisplay() {}
//-------------------------------
void MoleDisplay::open(){
	gfx_open(xsize,ysize,"MoleDisplay");
	gfx_clear();
}
//-------------------------------

int	MoleDisplay::screenx(int pep_posx){
	return (pep_posx *scale) + xsize/2;
}
//-------------------------------
int	MoleDisplay::screeny(int pep_posy){
	return ysize - ((pep_posy *scale) + ysize/2);
}

//-------------------------------
void MoleDisplay::grid(){


	int x_steps = (xsize / scale)/2;
	int y_steps = (ysize / scale)/2;


	for (int x=-x_steps; x < x_steps; x++) {
		int px = screenx(x);
		if (x==0)
			gfx_color(80,80,80);
		else
			gfx_color(20,20,20);

		gfx_line(px ,0, px, ysize);
	}

	for (int y=-y_steps; y<y_steps; y++) {
		int py = screeny(y);
		if (y==0)
			gfx_color(80,80,80);
		else
			gfx_color(20,20,20);

		gfx_line(0, py, xsize, py);

	}

	gfx_flush();

}
//-------------------------------
void MoleDisplay::draw_pep(Peptide *pep){
	if (pep==NULL) return;

	int x = screenx(pep->pos.dim[0]);
	int y = screeny(pep->pos.dim[1]);
	int s = scale/2;

	//gfx_color(0,100,0);
	gfx_line(x-s, y-s, x+s, y-s);
	gfx_line(x+s, y-s, x+s, y+s);
	gfx_line(x+s, y+s, x-s, y+s);
	gfx_line(x-s, y+s, x-s, y-s);


	gfx_color(200,200,200);
	char str[2];
	str[0] = pep->get();
	str[1] = '\0';
	gfx_text(str,x,y);

	gfx_flush();

}
//-------------------------------
void MoleDisplay::draw_mole(Molecule *mole){
	if (mole==NULL) return;

	mylist<Peptide>::mylist_item<Peptide> *current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		draw_pep(current_item-> item);

		//---
		current_item = current_item-> next;
	}
	//gfx_flush();
}

//-------------------------------
void MoleDisplay::draw_match(MoleculeMatchPos *matchpos){
	if (matchpos==NULL) return;

	gfx_color(100,0,0);
	draw_mole(matchpos-> getM1());

	//gfx_color(0,100,0);
	//draw_mole(matchpos-> getM2());

	gfx_color(0,0,100);
	draw_mole(matchpos-> rotmole);


}
