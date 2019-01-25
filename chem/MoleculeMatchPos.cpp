/*
 * MoleculeMatch.cpp
 *
 *  Created on: Jan 25, 2019
 *      Author: jkrah
 */

#include "MoleculeMatchPos.h"
#undef DEBUG
//#define DEBUG
#include "debug.h"
#include "common.h"
#include <stdio.h>
/*
//----------------------------------
class MoleculeMatchPos {
public:
	PeptidePos 	*start_pos;
	PeptidePos 	*end_pos;
	PeptidePos 	last_pos;
	PepRot 		last_rot;
	PepSig		match;

	//---------
	void		init(PeptidePos *start, PeptidePos *end);
	int			nextpos();

	MoleculeMatchPos();
	virtual ~MoleculeMatchPos();
	void	dump();
};
//----------------------------------
 */
//----------------------------------

void MoleculeMatchPos::init(PeptidePos *start, PeptidePos *end) {
	if (start != NULL) 	{
		start_pos = *start;
		current_pos = *start;
	} else {
		current_pos.init();
	}
	if (end != NULL){
		end_pos = *end;
	}


#ifdef DEBUG
#endif
};
//--------------------
void MoleculeMatchPos::dump(){
	//printf("MoleculeMatchPos:: last_rot[%d]\n", last_rot);
	printf("MoleculeMatchPos:: last_pos"); current_pos.dump(); NL
	printf("MoleculeMatchPos:: start_pos"); start_pos.dump(); NL
	printf("MoleculeMatchPos:: end_pos"); end_pos.dump();  NL
}
//----------------------------------
int	MoleculeMatchPos::nextpos(){

	//if ((start_pos==NULL) || (end_pos==NULL))  return -2;

	current_pos.dim[0]++;
	if (current_pos.dim[0] > end_pos.dim[0]) {
		current_pos.dim[1]++;
		current_pos.dim[0] = start_pos. dim[0];
	}

	if (current_pos.dim[1] > end_pos.dim[1]) {
//		last_rot ++;
//		last_pos.dim[1] = start_pos. dim[1];
//	}
//	if (last_rot >3) {
		return -1;
	}
	return 0;
}
//----------------------------------
void	MoleculeMatchPos::test(){
	printf("MoleculeMatchPos::test == START ==\n");
	printf("MoleculeMatchPos::test pre: ");	dump(); NL

	//------------
	PeptidePos start, end;
	start.dim[0] = -10;
	start.dim[1] = -5;
	end.dim[0] = 10;
	end.dim[1] = 5;
	printf("MoleculeMatchPos::test START = "); start.dump(); NL
	printf("MoleculeMatchPos::test END = "); end.dump(); NL
	init(&start, &end);
	printf("MoleculeMatchPos::test DUMP(init(start,end): ");	dump(); NL

	int r = nextpos();
	printf("MoleculeMatchPos::test nextpos =[%d] : ", r);	dump(); NL

	while (r>=0) {
		r = nextpos();
		//printf("MoleculeMatchPos::test nextpos =[%d] : ", r);	dump(); NL
	}
	printf("MoleculeMatchPos::test nextpos =[%d] : ", r);	dump(); NL

}
//----------------------------------
MoleculeMatchPos::MoleculeMatchPos() { init(NULL, NULL); }
MoleculeMatchPos::~MoleculeMatchPos() { }
//----------------------------------
//----------------------------------//----------------------------------
