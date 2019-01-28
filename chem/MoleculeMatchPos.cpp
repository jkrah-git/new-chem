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
	void		rotatemole();
	Molecule	*mole1;
	Molecule	*mole2;
public:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;
	Molecule	*rotmole;
	//---------
	//void		init2(PeptidePos *start, PeptidePos *end);
	void		clear(){ mole1 = NULL; mole2 = NULL; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }

	// nextpos returns 0=ok, 1=new rot, -1
	int			nextpos();

	MoleculeMatchPos(Molecule *base, Molecule *match);
	virtual ~MoleculeMatchPos();
	void	dump();
	void 	test();
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
		rotmole = NULL;
	}

}//--------------------
void MoleculeMatchPos::dump(){
	printf("MoleculeMatchPos:: last_rot[%d]\n", rotation);
	printf("MoleculeMatchPos:: last_pos"); current_pos.dump(); NL
	printf("MoleculeMatchPos:: start_pos"); start_pos.dump(); NL
	printf("MoleculeMatchPos:: end_pos"); end_pos.dump();  NL
	printf("===============================\n");
	printf("MoleculeMatchPos:: M1 :"); DUMP(mole1) if (mole1==NULL) NL else printf("===============================\n");
	printf("MoleculeMatchPos:: M2 :"); DUMP(mole2) if (mole2==NULL) NL else printf("===============================\n");
	printf("MoleculeMatchPos:: rotmole :"); DUMP(rotmole) printf("===============================\n");
}

//----------------------------------
void MoleculeMatchPos::rotatemole() {
	if ((mole1==NULL)||(mole2==NULL)) return;
	PeptidePos min1, max1, min2, max2;

	mole2-> rotate(rotation, rotmole);
	mole1-> getbounds(&min1, &max1);
	rotmole-> getbounds(&min2, &max2);

	PRINT(":: min1, max1 : "); min1.dump(); max1.dump(); NL
	PRINT(":: min2, max2 : "); min2.dump(); max2.dump(); NL
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



}
//----------------------------------
// nextpos returns 0=ok, 1=new rot, -1 end
int	MoleculeMatchPos::nextpos(){

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
		if (rotation >3) { return -1; }
		rotatemole();
		return 1;

	}
	return 0;
}
//----------------------------------
void	MoleculeMatchPos::test(){
	printf("MoleculeMatchPos::test == START ==\n");
	//printf("MoleculeMatchPos::test pre: ");	dump(); NL

	//------------
	//PeptidePos start, end;
	start_pos.dim[0] = -10;
	start_pos.dim[1] = -5;
	end_pos.dim[0] = 10;
	end_pos.dim[1] = 5;
	//printf("MoleculeMatchPos::test START = "); start.dump(); NL
	//printf("MoleculeMatchPos::test END = "); end.dump(); NL

	printf("MoleculeMatchPos:: ----------------------\n");
	printf("MoleculeMatchPos::test pre DUMP: ");	dump(); NL
	int r;

	/*
	printf("MoleculeMatchPos:: ----------------------\n");
	r = nextpos();	printf("MoleculeMatchPos::test nextpos =[%d] : ", r);	dump(); NL

	printf("MoleculeMatchPos:: ----------------------\n");
	r = nextpos();	printf("MoleculeMatchPos::test nextpos =[%d] : ", r);	dump(); NL
//	return;
	*/
	while (r>=0) {
		r = nextpos();
		if (r!=0) { printf("MoleculeMatchPos::test nextpos =[%d] : ", r);	dump(); NL }
	}
	//printf("MoleculeMatchPos::test last nextpos =[%d] : ", r);	dump(); NL

}

//----------------------------------
// -------------------------------
int	MoleculeMatchPos::nextmatch(void){

	PRINT("nextmatch..\n");
	 //if (matchpos ==NULL) return -10;
	 if (mole1 ==NULL) return -10;
	 if (mole2 ==NULL) return -11;
	 if (rotmole ==NULL) return -12;

	 int r =  nextpos();
	 if (r<0) return r;

	 // new rotoation
	 //if (r>0) {  rotate(matchpos-> rotation, matchpos-> rotmole); }

	//  - Match = 0bXXsseett.... = 4x64 sets
	//--------------------------------------
	// this.base = molecule
	// testmole = (translated mole to check for collisions)
	//--------------------------------------
	// for each test-pep = *test_item
	mylist<Peptide>::mylist_item<Peptide>
		*test_item  = rotmole-> pep_list.gethead();


	while((test_item!=NULL)&&(test_item-> item!=NULL)) {
		//PepSig s1 = current_item-> item-> get();
		r = -1;

		PeptidePos testpos;
		testpos.dim[0] = test_item-> item-> pos.dim[0] + current_pos.dim[0];
		testpos.dim[1] = test_item-> item-> pos.dim[1] + current_pos.dim[1];
		PRINT("=============================\n");
		PRINT("testpos ==>");	testpos.dump(); NL
		PRINT("matchpos==>");	dump(); NL
		PRINT("=============================\n");

		// test the traslated pos on 'this' (root)  molecole
		mylist<Peptide>::mylist_item<Peptide>  *test_pep = mole1-> test_pos(&testpos);
		if (test_pep!=NULL) {


			PRINT("found pep[0x%x]..\n", test_pep-> item-> get() );
			//----------------
			if (test_pep-> item-> match( test_item-> item-> get())) {
				PRINT("MATCH pep[0x%x]..\n", test_pep-> item-> get() );

			}
		}


		//----
		test_item = test_item-> next;
	} // next current_item

	return 0;
}
//------------

//----------------------------------//----------------------------------
