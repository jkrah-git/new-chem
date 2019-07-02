/*
 * ChemEngine.cpp
 *
 *  Created on: 2 Jul 2019
 *      Author: bimkrj
 */

#include "ChemEngine.h"

/*
// ----------------------------
class ChemFunc{
private:
	MyString 	name;
	MyString 	opcode;
	Molecule 	active_mole;
	int 	(*operation)(Concentration_VM*, int, char**);

public:
	// ------------------------------
	ChemFunc();
	virtual ~ChemFunc();
	void	dump(void);

};
// ----------------------------
*/
// ----------------------------// ----------------------------
ChemFunc::ChemFunc(){
	operation = NULL;
};
ChemFunc::~ChemFunc(){	};
// ----------------------------
void ChemFunc::dump(void) {
	printf("ChemFunc::[0x%zX] name[%s] opcode[%s] active_mole[0x%zX] operation[0x%zX]",	(long unsigned int) this, name.get(), opcode.get(), (long unsigned int) &active_mole, (long unsigned int) operation );
}
// ----------------------------
/*
// ----------------------------
class ChemEngine {
private:

public:
	mylist<ChemFunc>	func_list;
	//---------------------------------
	ChemEngine();
	virtual ~ChemEngine();
	void	dump(void);

};
// ----------------------------
*/
ChemEngine::ChemEngine() {	}
// ----------------------------// ----------------------------
ChemEngine::~ChemEngine() {	}
// ----------------------------

void ChemEngine::dump(void) {
	printf("ChemEngine::[0x%zX]..\n",	(long unsigned int) this);
	func_list.dump();

}

// ----------------------------

