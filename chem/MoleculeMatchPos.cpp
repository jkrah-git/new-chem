/*
 * MoleculeMatch.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: jkrah
 */

#include "MoleculeMatchPos.h"
#include "Molecule.h"

#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"
#include <stdio.h>

/*
//----------------------------------
class MoleculeMatchPos {
private:
	Molecule	*mole1;
	Molecule	*mole2;
	void		rotatemole();
	mylist<Peptide>::mylist_item<Peptide>	*root_item;
	mylist<Peptide>::mylist_item<Peptide>	*test_item;
public:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;	//   4=(end), 5=(start), 6=(modified)
	Molecule	*rotmole;

	//---------

	mylist<Peptide>::mylist_item<Peptide>	*get(){  return test_item; };

	void		setM1(Molecule *_mole){ mole1 = _mole; }
	void		setM2(Molecule *_mole){ mole2 = _mole; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }
	void		clear(){ mole1 = NULL; mole2 = NULL; test_item = NULL; }

	MoleculeMatchPos();
	virtual 	~MoleculeMatchPos();
	void		render();
	void		dump();
	//---------
	int		start();
	//			resets root_item

	int			nextpos();
	// returns: -1=(end), 0=(ok), 1=(newrot),

	int			nextmatch();
	//	returns: r= -3=(null_item) -2=(end), -1=(notfound), 0=(found), 1=(match)


};
//----------------------------------
 */
//----------------------------------
//----------------------------------
MoleculeMatchPos::MoleculeMatchPos() {
	rotmole = new Molecule;
	rotation = -1;
	clear();
}
MoleculeMatchPos::~MoleculeMatchPos() {
	if (rotmole != NULL ) {
		delete rotmole;
	}

}//--------------------
void MoleculeMatchPos::render(){

	Molecule 	buf;
	PeptidePos 	offset;

	offset.dim[0] = 10;
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
	if (rotmole==NULL) { printf("Rot=NULL\n"); }
	else {
		//rotmole-> dump();
		rotmole-> render();
		ch = 'Y';
		offset.dim[0] = 10;
		for (int i=0; i<PepPosVecMax; i++) {
			offset.dim[i] += current_pos.dim[i];
		}
		rotmole-> drawto(&buf, NULL, &offset, &ch);
	}

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
void MoleculeMatchPos::dump(){
	printf("===============================\n");
	printf("MoleculeMatchPos:: start_pos: "); start_pos.dump(); NL
	printf("MoleculeMatchPos:: end_pos: "); end_pos.dump();  NL
	printf("MoleculeMatchPos:: last_rot: %d\n", rotation);
	printf("MoleculeMatchPos:: last_pos ->: "); current_pos.dump(); NL
	//printf("MoleculeMatchPos:: root_item: "); DUMP(root_item) NL
	printf("MoleculeMatchPos:: test_item: "); DUMP(test_item) NL
	printf("===============================\n");

	//render();

}
//---------------------------------------------------------
int	MoleculeMatchPos::start(){
	if (mole1==NULL) return -1;
	if (mole2==NULL) return -2;

	rotation = 5;
	test_item = NULL;

	return 0;
}

//----------------------------------
void MoleculeMatchPos::rotatemole() {
	if ((mole1==NULL)||(mole2==NULL)) return;
	PeptidePos min1, max1, min2, max2;


	mole2-> rotateto(rotation, rotmole);
	mole1-> getbounds(&min1, &max1);
	rotmole-> getbounds(&min2, &max2);

	printf(":: min1, max1 : "); min1.dump(); max1.dump(); NL
	printf(":: min2, max2 : "); min2.dump(); max2.dump(); NL
	// void		getbounds(PeptidePos *min, PeptidePos *max);
	//mole->
	// sub size m2 from min
	// add size m2 to max
	for (int i=0; i< PepPosVecMax; i++) {
		PepPosVecType len2 = max2.dim[i]-min2.dim[i] ;
		start_pos.dim[i] = min1.dim[i] - min2.dim[i]; // + len2;
		end_pos.dim[i] =   max1.dim[i] - max2.dim[i]; // + len2;
		if (start_pos.dim[i] > end_pos.dim[i]) {
			len2 = end_pos.dim[i];
			end_pos.dim[i] = start_pos.dim[i];
			start_pos.dim[i] = len2;
		}

		current_pos.dim[i] = start_pos.dim[i];
	}

	// reset new head
	test_item  = rotmole-> pep_list.gethead();

}
//----------------------------------//----------------------------------
int	MoleculeMatchPos::nextpos(){
	// returns: -2 nullpeps, -1=(end), 0=(ok), 1=(newrot),

	// ?? root_item first (initialise)
/*	if (root_item == NULL)
	{	root_item = mole1-> pep_list.gethead();
		if (root_item == NULL) return -2;
		rotation = 0;
		rotatemole();

		test_item  = rotmole-> pep_list.gethead();
		if (test_item == NULL) return -2;
		return 0;

	}
	//else { 	// next test_item
	 *
	 */


	if (rotation>3) {
		rotation = 0;
		rotatemole();
		return 1;
	}

	if (test_item !=NULL) {
		test_item = test_item -> next;
		if (test_item != NULL) {	return 0;	} // simple next test_item (no pos/rot change)
	}


	// at this pount - root_item is good, test_item needs restarting

	// initialise (or end of test_item)
	// (restart @pos) test_item to start of 'rotmole'
	test_item  = rotmole-> pep_list.gethead();
	if (test_item == NULL) return -2;




	current_pos.dim[0]++;
	if (current_pos.dim[0] > end_pos.dim[0]) {
		current_pos.dim[1]++;
		current_pos.dim[0] = start_pos. dim[0];
	}

	if (current_pos.dim[1] > end_pos.dim[1]) {
		//if ( (matchmole !=NULL) &&   (matchmole-> pep_list.head == matchmole-> pep_list.tail) ) {	return -1;		}

		rotation ++;
		current_pos.dim[1] = start_pos. dim[1];

		// End.. Out of positions
		if (rotation >3) {
			test_item = NULL;
			return -1;
		}

		rotatemole();
		return 1;
	}

	//dump();
	return 0;
}


//----------------------------------
// -------------------------------
int	MoleculeMatchPos::nextmatch(void){

	// ---------------------------------------------------------------------------
	//	nextmatch(): returns: -3=(null_item) -2=(end), -1=(notfound), 0=(found), 1=(match)
	// ---------------------------------------------------------------------------
	if (mole1 ==NULL) return -10;
	if (mole2 ==NULL) return -11;
	if (rotmole ==NULL) return -12;
	// both root and test items need to be set here

	// nextpos
	int result  = nextpos();
	if (result <-1) return -3;
	if (result <0) return -2;
	result = -1;

	PepPosVecType	*test_item_pos = test_item-> item-> getpos();
	if (test_item_pos ==NULL) return -13;

	PeptidePos testpos;
	testpos.dim[0] = test_item_pos[0] + current_pos.dim[0];
	testpos.dim[1] = test_item_pos[1] + current_pos.dim[1];

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

//----------------------------------
// -------------------------------
void MoleculeMatchPos::test(void){
	Molecule m1;

	m1.test();


}

//----------------------------------//----------------------------------
