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
	if (conc==NULL) return -1.0;
	return conc->get();
}
// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
//--------------
ConcLevelType	ConcentrationVolume::take(Molecule	*m, ConcAdjustType adj){
	Concentration *conc = search(m);
	if (conc==NULL) return -1.0;
	return conc->take(adj);

}
//--------------
ConcLevelType	ConcentrationVolume::put(Molecule	*m, ConcLevelType amount){
	Concentration *conc = search(m);
	printf("::ConcentrationVolume::put.. search ="); DUMP(conc); NL
	if (conc==NULL) {
		mylist<Concentration>::mylist_item<Concentration> *item = NULL;
		conc = new  Concentration(m);
		LOG("malloc[0x%zX]\n", (long unsigned int) conc);
		printf("::ConcentrationVolume::put.. create ="); DUMP(conc) NL;
		if (conc==NULL)
			return -1.0;

		item = conc_list.add(conc);
		printf("::ConcentrationVolume::put.. list.create ="); DUMP(item) NL;
	}
	return conc->put(amount);
}
//--------------
void ConcentrationVolume::test(void){
	printf("======================================\n");
	printf("ConcentrationVolume.test2: == START ==\n");
	printf("======================================\n");

	Molecule M1,M2,M3;

	printf("======================================\n");
	printf("ConcentrationVolume.test2: Building M1 - single unit\n");
	printf("======================================\n");
	M1.test2();
	printf("======================================\n");
	printf("ConcentrationVolume.test2: Building M2 - DUAL unit\n");
	printf("======================================\n");
	M2.test2();
	M2.test2();
	printf("======================================\n");
	printf("ConcentrationVolume.test2: Building M3 - singleunit (same as M1)\n");
	printf("======================================\n");
	M3.test2();
	printf("======================================\n");
	printf("ConcentrationVolume.test2: checking M3\n");
	printf("======================================\n");
	// M1(=M3)!=M2
	if (M1==M2) printf("ConcentrationVolume.test2: (M1==M2): FAILED\n");
	else 		printf("ConcentrationVolume.test2: (M1!=M2): PASSED\n");

	if (M1==M3)	printf("ConcentrationVolume.test2: (M1==M3): PASSED\n");
	else 		printf("ConcentrationVolume.test2: (M1!=M3): FAILED\n");
	printf("======================================\n");
	printf(" .. M1,M2,M3 built ..\n");
	printf("======================================\n");
	/*
	 * 	Concentration	*search(Molecule	*m);
		ConcLevelType	get(Molecule	*m);
		// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
		ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
		ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	 */
	Concentration	*conc;
	printf("======================================\n");
	printf("ConcentrationVolume.test2: search conc.M1 = ");	conc = search(&M1);		DUMP(conc); NL
	printf("ConcentrationVolume.test2: search conc.M2 = ");	conc = search(&M2);		DUMP(conc); NL
	printf("ConcentrationVolume.test2: search conc.M3 = ");	conc = search(&M3);		DUMP(conc); NL
	printf("======================================\n");

	ConcLevelType v,w;
	w = .5;

	printf("======================================\n");
	printf("======================================\n");
	v = put(&M1, w);		printf("ConcentrationVolume.test2: put(M1, %3.3f) = %3.3f\n", w, v);
	conc = search(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");
	v = put(&M1, w);		printf("ConcentrationVolume.test2: put(M1, %3.3f) = %3.3f\n", w, v);
	conc = search(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");
	printf("ConcentrationVolume.test2: commit()..\n");
	if (conc!=NULL) conc->commit();		dump();
	printf("======================================\n");
	printf("======================================\n");
	v = take(&M1, w);		printf("ConcentrationVolume.test2: take(M1, %3.3f) = %3.3f\n", w, v);
	conc = search(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");

	if (conc!=NULL) {
		printf("ConcentrationVolume.test2: conc.test();\n");
		conc-> test();
	}

	printf("ConcentrationVolume.test2: POST.fulldump()\n");

	printf("======================================\n");
	printf("ConcentrationVolume.test2: == END ==\n");
	printf("======================================\n");

}

//--------------


