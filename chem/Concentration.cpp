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
Concentration::Concentration(Molecule *m) {	mole = m;	}
Concentration::~Concentration() 			{	mole = NULL; }
Molecule	*Concentration::getmole(void)	{	return mole;	}

// -------------------------------
void Concentration::dump(){
	printf("Concentration[0x%zX].",	(long unsigned int) this);
	buf.dump(); NL
	//mole.dump();
	DUMP(mole);
}
// -------------------------------

// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
ConcLevelType	Concentration::take(ConcAdjustType adj){
	ConcLevelType	result = ( buf.get() * adj );
	buf.remove(result);
	return result;

}
// -------------------------------
ConcLevelType	Concentration::put(ConcLevelType amount){
	ConcLevelType	result = amount;
	buf.add(result);
	return result;
}

// -------------------------------
void Concentration::test(){
	printf("Concentration.test: == START ==\n");
	printf("Concentration.test: PRE: ");	dump();
	//------------
	printf("Concentration.test: buf.test: "); buf.test();
	printf("Concentration.test: POST: ");		dump();


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
	//printf("########## ########## ConcentrationVolume::search.m. ..\n");	DUMP(m)

	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();

	while (item!=NULL) {
		//printf("########## ConcentrationVolume::search.item ...\n");
		//DUMP(item-> item->  getmole())
		//printf("##########  \n");
		if (*item-> item-> getmole() == *m)
			return item-> item;
		// -- else
		item = item-> next;
	}
	return NULL;
}
//--------------
ConcLevelType	ConcentrationVolume::get(Molecule	*m){
	Concentration *conc = search(m);
	if (conc==NULL) return 0.0;
	return conc->get();
}
// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
//--------------
ConcLevelType	ConcentrationVolume::take(Molecule	*m, ConcAdjustType adj){
	Concentration *conc = search(m);
	if (conc==NULL) return 0.0;
	return conc->take(adj);

}
//--------------
ConcLevelType	ConcentrationVolume::put(Molecule	*m, ConcLevelType amount){
	Concentration *conc = search(m);
	if (conc==NULL) return 0.0;
	return conc->put(amount);

}
//--------------



void ConcentrationVolume::test(Concentration *c1, Concentration *c2, Concentration *c3){
	printf("ConcentrationVolume.test: == START ==\n");
	printf("------------\n");
	printf("ConcentrationVolume.test: pre: ");	dump(); //printf("\n");
	printf("------------\n");

//	printf("ConcentrationVolume.test:
//	printf("ConcentrationVolume.test: conc_list.test..\n");
//	conc_list.test(c1, c2, c3);
	//printf("ConcentrationVolume.test:
	Molecule 	m1;

	printf("------------\n");
	printf("ConcentrationVolume.test: m1.test..\n");
	printf("------------\n");
	m1.test2();
	printf("------------\n");
	return;

	printf("------------\n");
	m1.test();
	printf("------------\n");
	return;

	printf("------------\n");
	printf("ConcentrationVolume.test: POST: ");	dump();
	// -------------
	printf("ConcentrationVolume.test: == END ==\n");

}

//--------------


