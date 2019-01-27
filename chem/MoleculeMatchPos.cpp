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
public:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;
	Molecule	*basemole;
	Molecule	*matchmole;
	Molecule	*rotmole;
	//---------
	void		init2(PeptidePos *start, PeptidePos *end);

	// nextpos returns 0=ok, 1=new rot, -1
	int			nextpos();
	//Molecule	*gettestmole(void) { return testmole; }
	//PepRot		getrotation(void) { return rotation; }

	MoleculeMatchPos();
	virtual ~MoleculeMatchPos();
	void	dump();
	void 	test();
};
//----------------------------------

 */
//----------------------------------
//----------------------------------
MoleculeMatchPos::MoleculeMatchPos(Molecule *base, Molecule *match) {
	basemole = base;
	matchmole = match;
	rotmole = new Molecule;
	rotation = -1;
	//init(NULL, NULL);
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
	printf("MoleculeMatchPos:: basemole :"); DUMP(basemole) if (basemole==NULL) NL
	printf("MoleculeMatchPos:: matchmole :"); DUMP(matchmole) if (matchmole==NULL) NL
	printf("MoleculeMatchPos:: rotmole :"); DUMP(rotmole)
}

//----------------------------------
void MoleculeMatchPos::rotatemole() {
	if (basemole==NULL) return;
	if (matchmole==NULL) return;
	PeptidePos min1, max1, min2, max2;

	matchmole-> rotate(rotation, rotmole);
	basemole-> getbounds(&min1, &max1);
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
//----------------------------------//----------------------------------
