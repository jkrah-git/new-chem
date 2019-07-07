/*
 * Concentration.cpp
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#include "Concentration.h"
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"




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
/*
Concentration::Concentration() {	mole = NULL;	}
Concentration::Concentration(Molecule *m) {	mole = m;	}
Concentration::~Concentration() 			{	mole = NULL; }
Molecule	*Concentration::getmole(void)	{	return mole;	}
*/
// -------------------------------
// -------------------------------
void Concentration::dump(){
	printf("Concentration[0x%zX].mole[0x%zX]::",	(long unsigned int) this, (long unsigned int) mole);
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
	mylist<Molecule> 	mole_list;
	mylist<Concentration> 	conc_list;

public:

	// ---
	ConcentrationVolume();
	virtual ~ConcentrationVolume();
	// ----
	void 	dump(void);
	void	clear(void);
	void 	dumpmoles(void) { mole_list.dump(); }
	// ---------
	Concentration	*molesearch(Molecule	*m);

	mylist<Molecule>::mylist_item<Molecule> *search_molelist(Molecule *m){ return mole_list.search(m); };
	mylist<Concentration>::mylist_item<Concentration> *search_conclist(Concentration *c){ return conc_list.search(c); };

	ConcLevelType	get(Molecule	*m);
	void			set(Molecule	*m, ConcLevelType new_val, ConcLevelType new_delta);

	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
	ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	// ---------
	ChemTime		get_maxcommit(void);
	void			commit(void);
	//----
};
// -------------------------------

*/
ConcentrationVolume::ConcentrationVolume(){}
ConcentrationVolume::~ConcentrationVolume(){}
//--------------
void ConcentrationVolume::dump(void){
	printf("ConcentrationVolume[0x%zX].",	(long unsigned int) this);
	conc_list.dump();
}
//--------------
void ConcentrationVolume::clear(void){
//	mole_list.clear();
	conc_list.clear();

}

//--------------
Concentration	*ConcentrationVolume::molesearch(Molecule	*m){
	//printf("########## ########## ConcentrationVolume::search.m. ..\n");	DUMP(m)

	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();
	while (item!=NULL) {
		//printf("########## ConcentrationVolume::search.item ...\n");
		//DUMP(item-> item->  getmole())
		//printf("##########  \n");
		if ((*item-> item-> getmole()) == *m)
			return item-> item;
		// -- else
		item = item-> next;
	}
	return NULL;
}
//--------------
void	ConcentrationVolume::set(Molecule	*m, ConcLevelType new_val, ConcLevelType new_delta){
	Concentration *conc = molesearch(m);
	if (conc!=NULL) {
		conc-> set(new_val, new_delta);
	}
}
//--------------
ConcLevelType	ConcentrationVolume::get(Molecule	*m){
	Concentration *conc = molesearch(m);
	if (conc==NULL) return -1.0;
	return conc->get();
}
// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
//--------------
ConcLevelType	ConcentrationVolume::take(Molecule	*m, ConcAdjustType adj){
	Concentration *conc = molesearch(m);
	if (conc==NULL) return -1.0;
	ConcLevelType raw = conc->get() * adj;
	return conc->take(raw);

}
//--------------
//#define DEBUG
ConcLevelType	ConcentrationVolume::put(Molecule	*m, ConcLevelType amount){
	if (m==NULL) return -1.0;

	Concentration *conc = molesearch(m);
	//PRINT("search mole[0x%zX] = conc[0x%zX]\n", m, conc);
	//DUMP(conc); NL

	if (conc==NULL) {

		// copy new_mole to mole_list
		mylist<Molecule>::mylist_item<Molecule> *new_mole = mole_list.add();
		if ((new_mole ==NULL) || (new_mole-> item ==NULL)) { return -1.0; }
		m-> rotateto(0, new_mole-> item);

		mylist<Concentration>::mylist_item<Concentration> *new_conc;
		new_conc = conc_list.add();
		if ((new_conc==NULL)||(new_conc-> item==NULL)) { return -2.0; }

		conc = new_conc-> item;
		conc -> setmole(new_mole-> item);
		//new_conc-> item-> setmole(new_mole-> item);
		//PRINT("new conc=[0x%zX]\n",  conc);
		// conc-> dump();
	}
	return conc->put(amount);
}
//--------------
double ConcentrationVolume::get_maxcommit(void){

	double max = 1.0;
	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();
	while (item!=NULL) {
		if (item-> item!=NULL) {
			ConcLevelType delta = item-> item->getdelta();
			if (delta<0) {
				ConcLevelType val = item-> item->get();
				if (delta <= val) {
					double m = -((double) val/delta);
					if (max>m)
						max = m;
				} // endif (delta <= val)
			} // endif (delta<0)
		} // endif  (item-> item!=NULL)
		// -----------
		item = item-> next;
	}
	return max;
}
//--------------
int	ConcentrationVolume::del_conc(mylist<Concentration>::mylist_item<Concentration> *conc_item){

	if (conc_item==NULL) return -1;
	if (conc_item-> item ==NULL) return -2;
	Molecule *m = conc_item-> item->getmole();
	if (m==NULL) return -3;
	conc_list.del(conc_item);

	// todo: can't clean mole list as still used by enzymes/reactions cache
	/*
	mylist<Molecule>::mylist_item<Molecule> *mole_item = mole_list.search(m);
	if (mole_item==NULL) return -4;
	mole_list.del(mole_item);
	*/
	return 0;
}

//--------------
void ConcentrationVolume::commit(void){
	mylist<Concentration>::mylist_item<Concentration> *conc_item = conc_list.gethead();
	while (conc_item!=NULL) {
		if (conc_item-> item!=NULL) {
			conc_item-> item->commit();
		}
		// ----
		conc_item = conc_item-> next;
	}
}
//--------------
void ConcentrationVolume::reset(void){
	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();
	while (item!=NULL) {
		if (item-> item!=NULL)
			item-> item->reset();
		//-----------
		item = item-> next;
	}
}
//--------------
//--------------
int ConcentrationVolume::clean_conc(void){
	int n =0 ;
	mylist<Concentration>::mylist_item<Concentration> *conc_item = conc_list.gethead();
	while (conc_item!=NULL) {
		if (conc_item-> item!=NULL) {
			// deletete (zero) conc's
			if (conc_item-> item->get() <=0) {
				mylist<Concentration>::mylist_item<Concentration> *prev_item = conc_item->prev;
				int r = del_conc(conc_item);
				PRINT("del conc = [%d]\n", r);
				conc_item = prev_item;
				n++;
			}
		}
		//-----------
		conc_item = conc_item-> next;
	}


	return n;
}
//--------------
/*************************************************************
void ConcentrationVolume::test(){
	printf("======================================\n");
	printf("ConcentrationVolume.test2: == START ==\n");
	printf("======================================\n");

	Molecule M1,M2,M3;

	printf("======================================\n");
	printf("ConcentrationVolume.test2: Building M1 - single unit\n");
	printf("======================================\n");
	M1.test2();
	printf("======================================\n");
	printf("======================================\n");
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
	Concentration	*conc;
	printf("======================================\n");
	printf("ConcentrationVolume.test2: search conc.M1 = ");	conc = molesearch(&M1);		DUMP(conc); NL
	printf("ConcentrationVolume.test2: search conc.M2 = ");	conc = molesearch(&M2);		DUMP(conc); NL
	printf("ConcentrationVolume.test2: search conc.M3 = ");	conc = molesearch(&M3);		DUMP(conc); NL
	printf("======================================\n");

	ConcLevelType v,w;
	w = .5;

	printf("======================================\n");
	printf("ConcentrationVolume.test2: M1 put/search..\n");
	printf("======================================\n");
	v = put(&M1, w);		printf("ConcentrationVolume.test2: put(M1, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");
	v = put(&M1, w);		printf("ConcentrationVolume.test2: put(M1, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");
	if (conc==NULL) {
		printf("ConcentrationVolume.test2: NULL conc. !! Can't Commit !!\n");
		printf("======================================\n");
	} else {
		printf("ConcentrationVolume.test2: commit()..\n");
		conc->commit();
		printf("======================================\n");
		conc-> dump();
		printf("======================================\n");
	}

	printf("======================================\n");
	v = take(&M1, w);		printf("ConcentrationVolume.test2: take(M1, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");

	if (conc!=NULL) {
		printf("======================================\n");
		printf("ConcentrationVolume.test2: conc.test();\n");
		printf("======================================\n");
		conc-> test();
	}
	printf("======================================\n");
	printf("ConcentrationVolume.test2: M2 put..\n");
	printf("======================================\n");
	conc = molesearch(&M2);		printf("ConcentrationVolume.test2: search conc.M2 = ");	DUMP(conc); NL
	v = put(&M2, w);		printf("ConcentrationVolume.test2: put(M2, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M2);		printf("ConcentrationVolume.test2: search conc.M2 = ");	DUMP(conc); NL
	printf("======================================\n");
	v = put(&M2, w);		printf("ConcentrationVolume.test2: put(M2, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M2);		printf("ConcentrationVolume.test2: search conc.M2 = ");	DUMP(conc); NL
	printf("======================================\n");


	printf("======================================\n");
	printf("ConcentrationVolume.test2: POST.fulldump()\n");
	printf("======================================\n");
	dump();

	printf("======================================\n");
	printf("ConcentrationVolume.test2: == END ==\n");
	printf("======================================\n");

}

//--------------


void ConcentrationVolume::test2(ConcentrationVolume *cvol){
	return;


	if (cvol==NULL) return;
	printf("======================================\n");
	printf("ConcentrationVolume.test2: == START ==\n");
	printf("======================================\n");

	//	mylist<Molecule>::mylist_item<Molecule> *M1 = cvol-> mole_list.add();
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

	Concentration	*conc;
	printf("======================================\n");
	printf("ConcentrationVolume.test2: search conc.M1 = ");	conc = molesearch(&M1);		DUMP(conc); NL
	printf("ConcentrationVolume.test2: search conc.M2 = ");	conc = molesearch(&M2);		DUMP(conc); NL
	printf("ConcentrationVolume.test2: search conc.M3 = ");	conc = molesearch(&M3);		DUMP(conc); NL
	printf("======================================\n");

	ConcLevelType v,w;
	w = .5;

	printf("======================================\n");
	printf("ConcentrationVolume.test2: M1 put/search..\n");
	printf("======================================\n");
	v = put(&M1, w);		printf("ConcentrationVolume.test2: put(M1, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");
	v = put(&M1, w);		printf("ConcentrationVolume.test2: put(M1, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");
	if (conc==NULL) {
		printf("ConcentrationVolume.test2: NULL conc. !! Can't Commit !!\n");
		printf("======================================\n");
	} else {
		printf("ConcentrationVolume.test2: commit()..\n");
		conc->commit();
		printf("======================================\n");
		conc-> dump();
		printf("======================================\n");
	}

	printf("======================================\n");
	v = take(&M1, w);		printf("ConcentrationVolume.test2: take(M1, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M1);		printf("ConcentrationVolume.test2: search conc.M1 = ");	DUMP(conc); NL
	printf("======================================\n");

	if (conc!=NULL) {
		printf("======================================\n");
		printf("ConcentrationVolume.test2: conc.test();\n");
		printf("======================================\n");
		conc-> test();
	}
	printf("======================================\n");
	printf("ConcentrationVolume.test2: M2 put..\n");
	printf("======================================\n");
	conc = molesearch(&M2);		printf("ConcentrationVolume.test2: search conc.M2 = ");	DUMP(conc); NL
	v = put(&M2, w);		printf("ConcentrationVolume.test2: put(M2, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M2);		printf("ConcentrationVolume.test2: search conc.M2 = ");	DUMP(conc); NL
	printf("======================================\n");
	v = put(&M2, w);		printf("ConcentrationVolume.test2: put(M2, %3.3f) = %3.3f\n", w, v);
	conc = molesearch(&M2);		printf("ConcentrationVolume.test2: search conc.M2 = ");	DUMP(conc); NL
	printf("======================================\n");


	printf("======================================\n");
	printf("ConcentrationVolume.test2: POST.fulldump()\n");
	printf("======================================\n");
	dump();

	printf("======================================\n");
	printf("ConcentrationVolume.test2: == END ==\n");
	printf("======================================\n");

}
*************************************************************/
//--------------


