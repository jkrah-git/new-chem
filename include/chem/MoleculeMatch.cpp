/*
 * MoleculeMatch.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: jkrah
 */

#include "MoleculeMatch.h"
#include "Molecule.h"

#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"
#include <stdio.h>

/*
//----------------------------------
class MoleculeMatchResult {
public:
	PeptidePos 						current_pos;
	PepRot								rotation;	//   4=(end), 5=(start), 6=(modified)
mylist<Peptide>::mylist_item<Peptide>	*matched_item;
	//-----------
MoleculeMatchResult(){ matched_item = NULL; };
	void	dump(void);
};
//----------------------------------
void MoleculeMatchResult::dump(void){
	printf("MoleculeMatchResult[0x%zX]", (long unsigned int) this);
	printf(":: Rot[%d].", rotation); current_pos.dump();
}
*/

/*
class Molecule;
//----------------------------------
enum MatchPos_State { INV, READY, NOMATCH, MATCH };
//----
class MoleculeMatchPos {
private:
	MatchPos_State	state;
	Molecule	*mole1;
	Molecule	*mole2;
	mylist<Peptide>::mylist_item<Peptide>	*test_item;
	//----------
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;	//   4=(end), 5=(start), 6=(modified)
	Molecule	*rotmole;

	// todo:  int Molecule::rotateto(PepRot rotation, Molecule *dest)
	void		rotatemole();

public:
	//---------
	MoleculeMatchPos();
	virtual 	~MoleculeMatchPos();

 MatchPos_State	get_state(void){ return state; };
	Molecule	*getM1(){ return mole1; }
	...
	Molecule	*get_rotmole(void) { return rotmole; }

	void		setM1(Molecule *_mole){ mole1 = _mole; }
	void		setM2(Molecule *_mole){ mole2 = _mole; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }
	void		clear(){ mole1 = NULL; mole2 = NULL; test_item = NULL; }
	void		render();
	void		dump();
	//---------
	int		start();
	//			resets root_item

	int			nextpos();
	// returns: -1=(end), 0=(ok), 1=(newrot),

	int			nextmatch_item();
	//	returns: r= -3=(null_item) -2=(end), -1=(notfound), 0=(found), 1=(match)

};
//----------------------------------
*/ //----------------------------------//----------------------------------
MoleculeMatch::MoleculeMatch() {

	//rotmole = new Molecule;
	rotation = -1;
	//current_pos.dim[PEPPOS_ROT] = -1;

	clear();
}
MoleculeMatch::~MoleculeMatch() {
	//if (rotmole != NULL ) {		delete rotmole;	}

}
//--------------------
void MoleculeMatch::clear(){
//	state = INV;
	mole1 = NULL;
	mole2 = NULL;
	test_item = NULL;
	matched_item = NULL;
	start_pos.init();
	end_pos.init();
	current_pos.init();
	rotation = -1;
	//if (rotmole!=NULL)
	rotmole.clear();
}
//--------------------
void MoleculeMatch::render(){

	Molecule 	buf;
	PeptidePos 	offset;

	offset.dim[PEPPOS_X] = 10;
	PepSig ch = 'x';

	//printf("MoleculeMatchPos:: M1 :"); //DUMP(mole1) if (mole1==NULL) NL else printf("===============================\n");
	if (mole1==NULL) { printf("M1 = NULL\n"); }
	else {
		mole1-> drawto(&buf, NULL, NULL, NULL);
		mole1-> drawto(&buf, NULL, &offset, &ch);
	}

	//printf("MoleculeMatchPos:: M2 :"); // DUMP(mole2) if (mole2==NULL) NL else printf("===============================\n");
	if (mole2==NULL) { 	printf("M2 = NULL\n"); }
	else {
		offset.dim[0] = 20;
		mole2-> drawto(&buf, NULL, &offset, NULL);
		//mole2-> drawto(&buf, NULL, &offset, NULL);
	}


	printf("MoleculeMatchPos:: rotmole :");
//	if (rotmole==NULL) { printf("Rot=NULL\n"); }
//	else {
		//rotmole-> dump();
		rotmole.render();
		ch = 'Y';
		offset.dim[0] = 10;
		for (int i=0; i<PepPosVecMax; i++) {
			offset.dim[i] += current_pos.dim[i];
		}
		rotmole.drawto(&buf, NULL, &offset, &ch);
//	}

	ch = 'X';
	Molecule m;
	mylist<Peptide>::mylist_item<Peptide> *new_item = m.pep_list.add();
	if ((new_item!=NULL) &&(new_item-> item!=NULL)) {
		new_item-> item->setpos(current_pos.dim[PEPPOS_X], current_pos.dim[PEPPOS_Y], 0);
		new_item-> item->set(ch);
		m.drawto(&buf, NULL, NULL, NULL);
	}

	if (test_item !=NULL) {
		PeptidePos pos;
	//	testpos.dim[0] = test_item-> item-> pos.dim[0] + current_pos.dim[0];
	//	testpos.dim[1] = test_item-> item-> pos.dim[1] + current_pos.dim[1];
		PepPosVecType	*test_pos = test_item-> item-> getpos();
		if (test_pos !=NULL) {
			pos.dim[PEPPOS_X] = current_pos.dim[PEPPOS_X] + test_pos[PEPPOS_X];
			ch = '*';

			mylist<Peptide>::mylist_item<Peptide> *new_item = m.pep_list.add();
			if ((new_item!=NULL) &&(new_item-> item!=NULL)) {
				//new_item-> item->pos = testpos;
				new_item-> item-> setpos(test_pos[PEPPOS_X],test_pos[PEPPOS_Y], 0);
				new_item-> item-> set(ch);
				m.drawto(&buf, NULL, NULL, NULL);
			}
		}

	}
/*
	printf("x=M1, Y=rot, X=current_pos, *=test_pos\n");
	printf("===============================\n");
	//if ((root_item!=NULL) &&(root_item-> item!=NULL) &&
	if ((test_item!=NULL) &&
		(test_item-> item!=NULL)) {
		//----------------
		printf("--- Items --- .\n");
	//	root_item-> item->dump(); NL
		test_item-> item->dump(); NL


		char bin0[32], bin1[32];
		sprintb(bin0, (char) root_item-> item-> get(), '0');
		sprintb(bin1, (char) test_item-> item-> get(), '0');
		printf("Peptide::testing [%s]->[%s]\n", bin0, bin1);

	//----------------
	}
	*/
	printf("============ buf =================\n");
	//buf.dump();
	buf.render();
	printf("x=M1, Y=rot, X=current_pos, *=test_pos\n");

}

//--------------------
void MoleculeMatch::dump(){
	printf("===============================\n");
	printf("MoleculeMatchPos:: start_pos: "); start_pos.dump(); NL
	printf("MoleculeMatchPos:: end_pos: "); end_pos.dump();  NL
//	printf("MoleculeMatchPos:: last_rot: %d\n", current_pos.dim[PEPPOS_ROT]);
	printf("MoleculeMatchPos:: last_rot: %d\n", rotation);
	printf("MoleculeMatchPos:: last_pos ->: "); current_pos.dump(); NL
	printf("MoleculeMatchPos:: test_item: "); DUMP(test_item) NL
	printf("===============================\n");
	printf("== results ==\n");
//	results_list.dump();
	//render();

}
//---------------------------------------------------------
int	MoleculeMatch::start(){
	if (mole1==NULL) return -1;
	if (mole2==NULL) return -2;

	test_item = NULL;
	matched_item = NULL;
	current_pos.init();
	rotation = 4;
	//rotatemole();
//	results_list.clear();
	return 0;
}

//----------------------------------
void MoleculeMatch::rotatemole() {
	if ((mole1==NULL)||(mole2==NULL)) return;

	mole2-> rotateto(rotation, &rotmole);

	PeptidePos min1, max1, min2, max2;
	mole1-> getbounds(&min1, &max1);
	rotmole.getbounds(&min2, &max2);

	//PRINT(":: min1, max1 : "); min1.dump(); max1.dump(); NL
	//PRINT(":: min2, max2 : "); min2.dump(); max2.dump(); NL

	for (int i=0; i< 2; i++) {

		// !!!!!!!!!!!!!!!!!!!!!!!
		PepPosVecType len2 = max2.dim[i]-min2.dim[i] ;
		// PRINT(":: len2=[%d]\n", len2);
		//	start_pos.dim[i] = min1.dim[i] - len2;
		//	end_pos.dim[i] =   max1.dim[i] + len2;
		start_pos.dim[i] = min1.dim[i] - max2.dim[i];
		end_pos.dim[i] =   max1.dim[i] - min2.dim[i];

		//---------------
		//PRINT(":: start_pos[%d] end_pos[%d]\n", start_pos.dim[i], end_pos.dim[i]);
		//---------------
		if (start_pos.dim[i] > end_pos.dim[i]) {
			len2 = end_pos.dim[i];
			end_pos.dim[i] = start_pos.dim[i];
			start_pos.dim[i] = len2;
		}

		//----
		current_pos.dim[i] = start_pos.dim[i];
	}
	// reset new head
	test_item  = rotmole.pep_list.gethead();
	matched_item = NULL;
}
//----------------------------------//----------------------------------
int	MoleculeMatch::nextpos(){
	// nextpos() returns: -2 (no items) -1=(end), 0=(start), 1=(next_item),2=(nextX),3=(nextY),4=(nextRot)

	// start new run ??
	// todo: if (test_item==NULL) ??
	if (rotation>3) {
		rotation = 0;
		// nb: rotemole also resets: test_item
		rotatemole();
		return 0;	//   0=(start)
	}

	// else try to test next (rotmole) item
	if (test_item !=NULL) {
		test_item = test_item -> next;
		if (test_item != NULL) {
			return 1; // 1=(next_item)
		} // simple next test_item (no pos/rot change)
	}

	// else try restart at rotmole-> head
	test_item  = rotmole.pep_list.gethead();
	// empty / bad rotmole - if no head / items
	if (test_item == NULL) return -2;

	// next posX
	current_pos.dim[PEPPOS_X]++;
	if (current_pos.dim[PEPPOS_X] <= end_pos.dim[0])
		return 2; // 2=(nextX)

	// else  next posY
	current_pos.dim[PEPPOS_X] = start_pos. dim[0];
	current_pos.dim[PEPPOS_Y]++;

	if (current_pos.dim[PEPPOS_Y] <= end_pos.dim[1])
		return 3; //3=(nextY)

	// else next rot
	current_pos.dim[PEPPOS_Y] = start_pos. dim[1];
	rotation ++;

	if (rotation >3) {
		// End.. Out of positions
		test_item = NULL;
		return -1;	// -1=(end)
	}

	rotatemole();
	return 4; // 4=(nextRot)
}
//----------------------------------
int	MoleculeMatch::match_pep(Peptide *pep1, Peptide *pep2){
// returns: -2=(no pep1) -1=(no_match) 0=(no_active), 1=(match)
	if (pep2==NULL) return -5;
	// pep1 = M1 = (target)
	// pep2 = M2 = (active)
	/*************
[0--- ----] GENE(store)
[1--- ----] PROTIEN(funcs) -> match-map

[Z--- -QqR] <- REACT BITS
[Z--- -QqR] <- REACT BITS
[0-xx x---] <- DATA BITs (3xbits/pep) (8xgroups)
[00xx x---] Start
[Z1xx x---] end
	**************/
	if (pep2->sig < 128) return 0;		// 0=(no_active)
	if (pep1==NULL) return -2; 			// -2=(no pep1)
	// else
	PepSig sig = pep2->sig -128;
	if (sig != pep1-> sig) return -1;	// -1=(no_match)
	// else
	return 1;							// 1=(match)
}
// -------------------------------
int	MoleculeMatch::match_item(void){
	//	match_item(): returns:  -4=(END) -3=(NOMATCH) -2=(MISS) -1=(COLLISION) 0=(NEXT) 1=(MATCH)
	// todo: how to signal (next_pep) back to next_mole
	// ---------------------------------------------------------------------------
	if (mole1 ==NULL) return -10;
	if (mole2 ==NULL) return -11;
	// nextpos
	int result_nextpos  = nextpos();
	// nextpos() returns: -2 (no items) -1=(end), 0=(start), 1=(next_item),2=(nextX),3=(nextY),4=(nextRot)
	if (result_nextpos== -1) return -4;		// (END)
	if (result_nextpos <0) return result_nextpos-20;
	if (test_item ==NULL) return -12;

	PeptidePos testpos;
	// testpos =   current_pos + test_item-> item-> pos;
	// todo: FIX vector adds	//
	PepPosVecType	*test_item_pos = test_item-> item-> getpos();
	if (test_item_pos ==NULL) return -13;
	testpos.dim[PEPPOS_X] = test_item_pos[PEPPOS_X] + current_pos.dim[PEPPOS_X];
	testpos.dim[PEPPOS_Y] = test_item_pos[PEPPOS_Y] + current_pos.dim[PEPPOS_Y];

	// ---check (mole1) pos for testpos...
	mylist<Peptide>::mylist_item<Peptide>  *test_pep = mole1-> testpos(&testpos);
//	PRINT("test-pos=>"); testpos.dump(); NL
//	PRINT("test_pep(M1)==\n");	DUMP(test_pep); NL
//	PRINT("test_item(M2)==\n");	DUMP(test_item-> item); NL

	//--------------------------
	// if not active and no test_pep then: return NEXT (0)
	// if not active and test_pep then: return COLSSION (-1)
	// if active :  if (no test_pep) then: return -2=(MISS)
	// if active :  if (no match) then: return -3=(NOMATCH)
	//--------------------------
	if (test_item-> item->sig <128) {
		if (test_pep==NULL) return 0;	// NEXT (0)
		else return -1;					// COLSSION (-1)
	} // else active
	if (test_pep==NULL) return -2; 		// -2=(MISS(pep)
	// test 2 peps
	int match = match_pep(test_pep->item,  test_item-> item);
	if (match!=1) return -3; 			// -3=(NOMATCH)
	// -------------------------------------
	//matched_item = test_item;
	matched_item = test_pep;
	return 1; //  1=(MATCH)
}
/*************

	PRINT("found pep -> "); test_pep-> dump(); NL
	PRINT("test_item-> "); test_item-> dump(); NL
	//----------------
	// returns: -1=(no_match) 0=(no_active), 1=(match)

	//PRINT("MATCH pep[0x%x]..\n", test_pep-> item-> get() );
	//---------------------------------
	// - active elements ... 0bXXsstttt  .. match 0bYYsseett
	// - ss = match.strength = 0-3
	// - eett = match. energy/temp deltas = (0-3) = { -1,0,1,2 }

	//PepSig A = root_item-> item-> get();
	PepSig A = test_pep-> item-> get();
	PepSig B = test_item-> item-> get();
	char bin0[32], bin1[32];
	sprintb(bin0, (char) A, '0');
	sprintb(bin1, (char) B, '0');
	printf("####################################\n");
	printf("Peptide::match [%s]->[%s]\n", bin0, bin1);

	// 0b1100 0000 = 0xc0
	// 0b0011 0000 = 0x30
	// 0b0000 1100 = 0x0c
	// 0b0000 0011 = 0x03
	PepSig data = test_pep-> item-> get();

	// 0bYYsseett
	//data = data &  0x3f;
	PepSig strength = (data &  0x30) >> 4;
	PepSig energy = (data &  0x0c) >> 2;
	PepSig temp = data &  0x03;

	sprintb(bin0, (char) data, '0');		printf("data=[%s]\n", bin0);
	sprintb(bin0, (char) strength, '0');	printf("strength=[%s]\n", bin0);
	sprintb(bin0, (char) energy, '0');		printf("energy=[%s]\n", bin0);
	sprintb(bin0, (char) temp, '0');		printf("temp=[%s]\n", bin0);
	printf("####################################\n");
	//---------------------------------
	return 1; //  1=(MATCH)
}
****************/
/*
int MoleculeMatch::save_match(){
	mylist<MoleculeMatchResult>::mylist_item<MoleculeMatchResult>	*result_item = results_list.add();
	if (result_item==NULL)  { PRINT("add.item failed\n"); return -1; }
	if (result_item->item==NULL) { PRINT("add.item.item NULL\n"); return -2; }

	result_item->item-> current_pos = current_pos;
	result_item->item-> rotation = rotation;
	//result_item->item-> matched_item = matched_item;
	return 0;
}
*/
//----------------------------------
int	MoleculeMatch::match_mole(){
	if (mole1 ==NULL) return -10;
	if (mole2 ==NULL) return -11;
	// match_mole() returns -2=(save_err)  -1=(NOMATCH), 0=(END), 1=(MATCH)

	// until end
	int m =0;
	while (m!=-4) {
		while (m >= 0) {
			m =match_item();
			//	match_item(): returns:  -4=(END) -3=(NOMATCH) -2=(MISS) -1=(COLLISION) 0=(NEXT) 1=(MATCH)			//PRINT("==> match[%d]\n", m);

			// if 'last_item' then test 'matched_item'
			if ((m>=0) && (test_item-> next ==NULL)) {
				// PRINT("==> tail[%d]\n", m);
				if (matched_item !=NULL){
					// Matched Mole !!
				//	if (save_match()<0)	{ return -2; } // -2=(save_err)
				//	PRINT("saved.. ---------- \n");
					return 1;	// , 1=(MATCH)
				}
			}
		}
		// if not end then (re)start next pos
		if (m != -4) {
			// start next item..
			test_item = NULL;
			m =0;
		}
	}
	if (m==-4) return 0;		//  0=(END)
	else return -1;				// -1=(NOMATCH)
	return 0;

}
//----------------------------------

// -------------------------------
/*
int	MoleculeMatchPos::OLDnextmatch_item(void){

	// ---------------------------------------------------------------------------
	//	nextmatch(): returns: -3=(null_item) -2=(end), -1=(notfound), 0=(found), 1=(match)
	// ---------------------------------------------------------------------------
	if (mole1 ==NULL) return -10;
	if (mole2 ==NULL) return -11;
	//if (rotmole ==NULL) return -12;
	// both root and test items need to be set here

	// nextpos
	int result  = nextpos();
	if (result <0) return result-10;
	result = -1;

	PepPosVecType	*test_item_pos = test_item-> item-> getpos();
	if (test_item_pos ==NULL) return -13;

	PeptidePos testpos;
	testpos.dim[PEPPOS_X] = test_item_pos[PEPPOS_X] + current_pos.dim[PEPPOS_X];
	testpos.dim[PEPPOS_Y] = test_item_pos[PEPPOS_Y] + current_pos.dim[PEPPOS_Y];
	// todo: FIX vector adds
	//testpos =   current_pos + test_item_pos;

	// ------------
	mylist<Peptide>::mylist_item<Peptide>  *test_pep = mole1-> testpos(&testpos);
	// mylist<Peptide>::mylist_item<Peptide>  *test_pos(Peptide *new_pep);


	if (test_pep!=NULL) {
		result  = 0;
		//PRINT("Colis @ "); testpos.dump();
	//	PRINT("found pep[0x%x]..\n", test_pep-> item-> get() );
		PRINT("found pep -> "); test_pep-> dump(); NL
		PRINT("test_item-> "); test_item-> dump(); NL
		//----------------
		if (test_pep-> item-> match( test_item-> item-> get())) {
			result = 1;
			//PRINT("MATCH pep[0x%x]..\n", test_pep-> item-> get() );
			//---------------------------------
			// - active elements ... 0bXXsstttt  .. match 0bYYsseett
			// - ss = match.strength = 0-3
			// - eett = match. energy/temp deltas = (0-3) = { -1,0,1,2 }

			//PepSig A = root_item-> item-> get();
			PepSig A = test_pep-> item-> get();
			PepSig B = test_item-> item-> get();
			char bin0[32], bin1[32];
			sprintb(bin0, (char) A, '0');
			sprintb(bin1, (char) B, '0');
			printf("####################################\n");
			printf("Peptide::match [%s]->[%s]\n", bin0, bin1);

			// 0b1100 0000 = 0xc0
			// 0b0011 0000 = 0x30
			// 0b0000 1100 = 0x0c
			// 0b0000 0011 = 0x03
			PepSig data = test_pep-> item-> get();

			// 0bYYsseett
			//data = data &  0x3f;
			PepSig strength = (data &  0x30) >> 4;
			PepSig energy = (data &  0x0c) >> 2;
			PepSig temp = data &  0x03;

			sprintb(bin0, (char) data, '0');		printf("data=[%s]\n", bin0);
			sprintb(bin0, (char) strength, '0');	printf("strength=[%s]\n", bin0);
			sprintb(bin0, (char) energy, '0');		printf("energy=[%s]\n", bin0);
			sprintb(bin0, (char) temp, '0');		printf("temp=[%s]\n", bin0);
			printf("####################################\n");


			//---------------------------------
		}
	} // else keep looking for colis
	return result;
}
*/
//----------------------------------


//----------------------------------//----------------------------------
