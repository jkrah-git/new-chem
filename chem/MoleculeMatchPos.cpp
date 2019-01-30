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
	root_item = NULL;
	test_item = NULL;

	clear();
}
MoleculeMatchPos::~MoleculeMatchPos() {
	if (rotmole != NULL ) {
		delete rotmole;
	}

}//--------------------
// todo render-match-pos
void MoleculeMatchPos::render(){

	Molecule 	buf;
	PeptidePos offset;

	offset.dim[0] = 10;
	PepSig ch = 'x';

	printf("MoleculeMatchPos:: M1 :"); //DUMP(mole1) if (mole1==NULL) NL else printf("===============================\n");
	if (mole1==NULL) { printf("NULL\n"); }
	else {
		//mole1-> dump();
		//mole1-> render();
		mole1-> drawto(&buf, NULL, NULL, NULL);
		mole1-> drawto(&buf, NULL, &offset, &ch);
		// drawto(Molecule *m, PepRot *rotation, PeptidePos *pos, PepSig *value)
	}

	printf("MoleculeMatchPos:: M2 :"); // DUMP(mole2) if (mole2==NULL) NL else printf("===============================\n");
	if (mole2==NULL) { 	printf("NULL\n"); }
	else {
		//mole2-> dump();
		//mole2-> render();
		offset.dim[0] = 20;		mole2-> drawto(&buf, NULL, &offset, NULL);
		//drawto(Molecule *m, PepRot *rotation, PeptidePos *pos, PepSig *value)
		mole2 -> drawto(&buf, NULL, &offset, NULL);
	}


	printf("MoleculeMatchPos:: rotmole :");//  DUMP(rotmole)
	if (rotmole==NULL) { printf("NULL\n"); }
	else {
		//rotmole-> render();
		ch = 'Y';
		offset.dim[0] = 10;
		for (int i=0; i<PepPosVecMax; i++) {
			offset.dim[i] += current_pos.dim[i];
		}
		rotmole-> drawto(&buf, NULL, &offset, &ch);
	}
	printf("===============================\n");
	if ((root_item!=NULL) &&
		(root_item-> item!=NULL) &&
		(test_item!=NULL) &&
		(test_item-> item!=NULL)) {
		//----------------
		printf("--- Matched --- .\n");
		root_item-> item->dump(); NL
		test_item-> item->dump(); NL

	//----------------
	}
	printf("============ buf =================\n");
	//buf.dump();
	buf.render();

}

//--------------------
void MoleculeMatchPos::dump(){
	printf("===============================\n");
	printf("MoleculeMatchPos:: start_pos: "); start_pos.dump(); NL
	printf("MoleculeMatchPos:: end_pos: "); end_pos.dump();  NL
	printf("MoleculeMatchPos:: last_rot: %d\n", rotation);
	printf("MoleculeMatchPos:: last_pos ->: "); current_pos.dump(); NL
	printf("MoleculeMatchPos:: root_item: "); DUMP(root_item) NL
	printf("MoleculeMatchPos:: test_item: "); DUMP(test_item) NL
	printf("===============================\n");

	render();

}
//---------------------------------------------------------
int	MoleculeMatchPos::start(){
	if (mole1==NULL) return -1;
	if (mole2==NULL) return -2;

	rotation = 5;
	root_item = mole1-> pep_list.gethead();
	if (mole1==NULL) return -3;
	return 0;
}

//----------------------------------
void MoleculeMatchPos::rotatemole() {
	if ((mole1==NULL)||(mole2==NULL)) return;
	PeptidePos min1, max1, min2, max2;


	mole2-> rotate(rotation, rotmole);
	mole1-> getbounds(&min1, &max1);
	rotmole-> getbounds(&min2, &max2);

//	PRINT(":: min1, max1 : "); min1.dump(); max1.dump(); NL
//	PRINT(":: min2, max2 : "); min2.dump(); max2.dump(); NL
	// void		getbounds(PeptidePos *min, PeptidePos *max);
	//mole->
	// sub size m2 from min
	// add size m2 to max
	for (int i=0; i< PepPosVecMax; i++) {
		PepPosVecType len2 = max2.dim[i]-min2.dim[i] +1;
		start_pos.dim[i] = min1.dim[i] - len2;
		end_pos.dim[i] = max1.dim[i] + len2;
		current_pos.dim[i] = start_pos.dim[i];
	}

	// reset new head
	test_item  = rotmole-> pep_list.gethead();

}
//----------------------------------
int	MoleculeMatchPos::nextpos(){
	// returns: -1=(end), 0=(ok), 1=(newrot),

	// set test_item to current 'rotmole' - (rotate will also refresh)
	test_item  = rotmole-> pep_list.gethead();

	// iniitalise -  on any invalid rot
	if (rotation >3) {
		rotation = 0;
		rotatemole();
		return 1;
	}

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
	//PRINT("nextmatch..\n");

	if (mole1 ==NULL) return -10;
	if (mole2 ==NULL) return -11;
	if (rotmole ==NULL) return -12;


	while ((root_item!=NULL)&& (root_item-> item!=NULL))
	{		//---------------- for each 'root_item'
			int r;
			if (test_item==NULL)	{
				r = nextpos();		// returns 0=(ok), 1=(newrot), -1=(end)
				//PRINT("nextpos returned [%d]\n", r);//		dump();		PRINT("== end dump==\n");
				if (r<0) return -2;
				//nextpos();		// returns 0=(ok), 1=(newrot), -1=(end)if (nextpos()<0) return -2;		//nextpos(): returns 0=(ok), 1=(newrot), -1=(end))
			}
			else {
				test_item = test_item-> next;
			}

		//	if (test_item==NULL)
			r = -3;
			while(true)
			{
				// new rotoation
				//if (r>0) {  rotate(matchpos-> rotation, matchpos-> rotmole); }

				//  - Match = 0bXXsseett.... = 4x64 sets
				//--------------------------------------
				// this.base = molecule
				// testmole = (translated mole to check for collisions)
				//--------------------------------------

				while((test_item!=NULL)&&(test_item-> item!=NULL)) {
					//PepSig s1 = current_item-> item-> get();
					r = -1;

					PeptidePos testpos;
					testpos.dim[0] = test_item-> item-> pos.dim[0] + current_pos.dim[0];
					testpos.dim[1] = test_item-> item-> pos.dim[1] + current_pos.dim[1];
				//	PRINT("=============================\n");
				//	PRINT("testpos ==>");	testpos.dump(); NL
				//	PRINT("matchpos==>");	dump(); NL
				//	PRINT("=============================\n");

					// test the traslated pos on 'this' (root)  molecole
					mylist<Peptide>::mylist_item<Peptide>  *test_pep = mole1-> test_pos(&testpos);
					if (test_pep!=NULL) {
						r  = 0;
						//PRINT("Colis @ "); testpos.dump();
						//PRINT("found pep[0x%x]..\n", test_pep-> item-> get() );
						//----------------
						if (test_pep-> item-> match( test_item-> item-> get())) {
							r = 1;
							//PRINT("MATCH pep[0x%x]..\n", test_pep-> item-> get() );
							//---------------------------------
							//---------------------------------
							break;
						}
					} // else keep looking for colis

					//----
					test_item = test_item-> next;
				} // next item

				if (r>=0)
					return r;
				if (nextpos()<0)
					return -2;
			} // else next rot

			// ---
			root_item = root_item-> next;
	} // next root_item

	return -1;
}
//------------

//----------------------------------//----------------------------------
