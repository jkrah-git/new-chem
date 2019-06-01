/*
 * VMDisplay.cpp
 *
 *  Created on: May 31, 2019
 *      Author: jkrah
 */

#include "ChemDisplay.h"
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
	attrib.scale = 40;

	core = NULL;
	pep = NULL;
	mole = NULL;
	conc = NULL;
	concvol = NULL;
	matchpos = NULL;


	clearatt();
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
void ChemDisplay::main(void) {
	gfx.title = (const char*) "- NewChem -";
	gfx.open();
	gfx.clear();

	if (core==NULL) {
		gfx.printg("- Null Core -");
		return;
	}
	// else core OK
	draw_vm(core);

}



//-------------------------------
//-------------------------------	//-------------------------------
//- OLD  ------------------------------

void ChemDisplay::clearatt(){
	attrib.offsetx = 0;
	attrib.offsety = 0;
	attrib.pos = NULL;
}
//-------------------------------
ChemDisplay::~ChemDisplay() {}
//-------------------------------
void ChemDisplay::dump() {
	printf("ChemDisplay[0x%zX].", (long unsigned int) this);
	printf("size[%d,%d].scale[%f].col[%d,%d,%d].off[%d,%d].pos[0x%zX]\n",
			gfx.width, gfx.height, attrib.scale, colr, colg, colb, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos);
	if (attrib.pos !=NULL) {
		printf(".. pos[%d,%d,%d]\n", attrib.pos[0], attrib.pos[1], attrib.pos[2]);
	}
}
//-------------------------------
void ChemDisplay::gdump() {
	char msg[128];

	sprintf(msg, "ChemDisplay[0x%zX].", (long unsigned int) this);
	gfx.printg(msg);
	sprintf(msg, "size[%d,%d].scale[%f].col[%d,%d,%d].off[%d,%d].pos[0x%zX]",
			gfx.width, gfx.height, attrib.scale, colr, colg, colb, attrib.offsetx, attrib.offsety, (long unsigned int)  attrib.pos);
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
void ChemDisplay::grid(int red, int green, int blue){
	PeptidePos p;
	attrib.pos = p.dim;
	if (attrib.pos==NULL) return;

	//gfx.color(red, green, blue);

	int x_steps = (gfx.width / attrib.scale)/2;
	int y_steps = (gfx.height /attrib. scale)/2;


	for (int x=-x_steps; x < x_steps; x++) {
		attrib.pos[PEPPOS_X] = x;
		int px = attrib.getx();
		if (x==0)
			gfx.color(red, green, blue);
		else
			gfx.color(red/2, green/2, blue/2);

		gfx.line(px ,0, px, gfx.height);
	}

	for (int y=-y_steps; y<y_steps; y++) {
		attrib.pos[PEPPOS_Y] = y;
		int py = attrib.gety();
		if (y==0)
			gfx.color(red, green, blue);
		else
			gfx.color(red/2, green/2, blue/2);

		gfx.line(0, py, gfx.width, py);

	}
	gfx.flush();

	attrib.pos = NULL;

}
//-------------------------------
void ChemDisplay::draw_pep(Peptide *pep) {
	// TODO: maybe this pos thing was a bad idea

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

	int x = attrib.getx();
	int y = attrib.gety();
	int s = attrib.scale/2;

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



	//-------------
	// (restore pos)
	attrib.pos = saved_pos;
	gfx.flush();

}

//-------------------------------

void ChemDisplay::draw_mole(Molecule *mole){

	if (mole==NULL) return;
	//PepPosVecType *globalpos = pos;

	mylist<Peptide>::mylist_item<Peptide> 	*current_item = mole-> pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){
		draw_pep(current_item-> item);
		//---
		current_item = current_item-> next;
	}

}

//-------------------------------
void ChemDisplay::draw_match(MoleculeMatchPos *matchpos){
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
		attrib.pos = matchpos-> current_pos.dim;
		setcol(0,100,0);
		gfx.cprintg("rotemole");
		attrib.pos = matchpos-> current_pos.dim;
		draw_mole(matchpos-> rotmole);
	}

	if (matchpos-> get_test_item()!=NULL) {
		setcol(100,100,100);
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
	setcol(100,100,100);
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
//-------------------------------
