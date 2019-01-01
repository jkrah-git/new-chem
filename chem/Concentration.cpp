/*
 * Concentration.cpp
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#include "Concentration.h"
// -------------------
/*
 // -------------
typedef float ConcLevel;

// -------------------------------
class Concentration {
private:

public:
	MyBuffer<ConcLevel> 	buf;
	Molecule				*mole;
	// ---
	Concentration();
	virtual ~Concentration();
	void dump();
	void test();

};
// -------------------------------
 */
Concentration::Concentration(Molecule	*m) {
	mole = m;
}
Concentration::~Concentration() {	}
// -------------------------------
void Concentration::dump(){
	printf("Concentration[0x%zX].",	(long unsigned int) this);
	buf.dump(); NL
	//mole.dump();
	DUMP(mole);
}
// -------------------------------
void Concentration::test(){
	printf("Concentration.test: == START ==\n");
	printf("Concentration.test: PRE: ");	dump();
	//------------

	printf("Concentration.test: buf.test: "); buf.test();
	printf("Concentration.test: POST: ");	dump();
	// -------------
	printf("Concentration.test: == END ==\n");

}
// -------------------------------
/*
// -------------------------------
class ConcentrationVolume {
private:

public:
	Mylist<Concentration> 	conc_list;

	// ---
	ConcentrationVolume();
	virtual ~ConcentrationVolume();
	void dump();
	void test();
};
// -------------------------------
*/
ConcentrationVolume::ConcentrationVolume(){}
ConcentrationVolume::~ConcentrationVolume(){}
//--------------
void ConcentrationVolume::dump(){
	printf("ConcentrationVolume[0x%zX].",	(long unsigned int) this);
	conc_list.dump();
}
//--------------
Concentration	*ConcentrationVolume::search(Molecule	*m){

	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.head;

	//Concentration *result = NULL;

	LOG("Searching..");

	while (item!=NULL) {
		item-> dump();

		if (*item-> item-> mole	== *m)
			return item-> item;
		item = item-> next;
	}
	return NULL;
}
//--------------



void ConcentrationVolume::test(Concentration *c1, Concentration *c2, Concentration *c3){
	printf("ConcentrationVolume.test: == START ==\n");
	printf("ConcentrationVolume.test: pre: ");	dump(); //printf("\n");

	printf("ConcentrationVolume.test: conc_list.test..\n");
	conc_list.test(c1, c2, c3);
	//------------
	printf("ConcentrationVolume.test: POST: ");	dump();
	// -------------
	printf("ConcentrationVolume.test: == END ==\n");




}

//--------------


