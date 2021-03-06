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
ConcentrationVolume::ConcentrationVolume(){
	mole_list = NULL;
}
// -------------------------------
ConcentrationVolume::~ConcentrationVolume(){}
// -------------------------------
void Concentration::dump(){
	printf("Concentration[0x%zX].mole[0x%zX]::",	(long unsigned int) this, (long unsigned int) mole);
	buf.dump(); NL
	//mole.dump();
	DUMP(mole);
}
// -------------------------------
void	Concentration::commit(BufCommitType max_commit){
	buf.commit(max_commit);
}
// -------------------------------
//--------------
void ConcentrationVolume::dump(void){
	printf("ConcentrationVolume[0x%zX].mole_list[0x%zX].count[%d]\n",	(long unsigned int) this, (long unsigned int) mole_list, conc_list.count());
	//conc_list.dump();
}
//--------------
//--------------
void ConcentrationVolume::list(void){
	printf("ConcentrationVolume[0x%zX]\n",	(long unsigned int) this);
	//conc_list.dump();
	//mylist<Concentration> 		*conc_list = vol-> get_conc_list();

	int n = 0;
	mylist<Concentration>::mylist_item<Concentration>  *conc_item = conc_list.gethead();
	while (conc_item!=NULL) {
		//printf("Molecule[0x%zX].len(%d)")
		if (conc_item->item !=NULL) {
			Molecule *m = conc_item->item-> getmole();
			printf("Conc[0x%zX].", (long unsigned int) conc_item-> item); //,  (long unsigned int)  m);
			if (m==NULL) {
				printf("<null mole>");
			} else {
				m->print_short(5);
			}
			printf(" = Level[%.3f].Delta[%.3f]\n", conc_item->item->get(), conc_item->item->getdelta());
			n++;
		}
		//---------------
		conc_item = conc_item->next;
	}



}
//--------------
void ConcentrationVolume::clear(void){
//	mole_list.clear();
	conc_list.clear();

}
//--------------
mylist<Molecule>::mylist_item<Molecule>	*ConcentrationVolume::molesearch_list(Molecule	*m){
	//printf("########## ########## ConcentrationVolume::search.m. ..\n");	DUMP(m)
	if (mole_list==NULL) { return NULL; }
	mylist<Molecule>::mylist_item<Molecule> *item = mole_list-> gethead();
	while (item!=NULL) {
		//printf("########## ConcentrationVolume::search.item ...\n");
		//DUMP(item-> item->  getmole())
		//printf("##########  \n");
		if ((item-> item == m) || (*(item-> item) == *m))
			return item;
		// -- else
		item = item-> next;
	}
	return NULL;
}
//--------------
Concentration	*ConcentrationVolume::_molesearch(Molecule	*m){
	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();
	while (item!=NULL) {
		if (item-> item-> getmole() == m)
			return item-> item;
		item = item-> next;
	}
	return NULL;
}
//--------------
//--------------
Concentration	*ConcentrationVolume::molesearch(Molecule	*m){
	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();
	while (item!=NULL) {
		if ((item-> item-> getmole() == m) || (*(item-> item-> getmole()) == *m))
			return item-> item;
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
	if (conc==NULL) return 0.0;
	return conc->get();
}
//--------------
void ConcentrationVolume::take(Molecule	*m, ConcLevelType amount){
	Concentration *conc = molesearch(m);
	if (conc!=NULL)
		conc-> buf.remove(amount);
}
//--------------
void	ConcentrationVolume::put(Molecule	*m, ConcLevelType amount){
	if (m==NULL) return; // -1.0;
	if (mole_list==NULL) return;// { return -2.0; }

	Concentration *conc = molesearch(m);
	//PRINT("search mole[0x%zX] = conc[0x%zX]\n", m, conc);	DUMP(conc); NL

	if (conc==NULL) {
		// copy new_mole to mole_list
		mylist<Molecule>::mylist_item<Molecule>	*new_mole = molesearch_list(m); // search_molelist(m);
		if (new_mole==NULL) {
			new_mole =  mole_list-> add();
			if (new_mole ==NULL) { return; }
			if (new_mole-> item ==NULL) {	mole_list->del(new_mole); return; }

			m-> rotateto(0, new_mole-> item);
		}

		mylist<Concentration>::mylist_item<Concentration> *new_conc = conc_list.add();
		if ((new_conc==NULL)||(new_conc-> item==NULL)) { return; }

		conc = new_conc-> item;
		conc -> setmole(new_mole-> item);
	}
	conc-> buf.add(amount);
}
//--------------
ChemTime ConcentrationVolume::get_maxcommit(ConcLevelType min_level, ConcLevelType max_level){

	ChemTime max = 1.0;
	mylist<Concentration>::mylist_item<Concentration> *item = conc_list.gethead();
	while (item!=NULL) {
		if (item-> item!=NULL) {
			BufCommitType m =  item-> item->buf.getmax(min_level, max_level);
			if (m<max)
				max = m;

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
	conc_list.del(conc_item);

	// todo: X99 can't clean mole list as still used by upstream enzymes/reactions cache
	/*
	Molecule *m = conc_item-> item->getmole(); 	if (m==NULL) return -3;
	mylist<Molecule>::mylist_item<Molecule> *mole_item = mole_list.search(m);
	if (mole_item==NULL) return -4;
	mole_list.del(mole_item);
	*/
	return 0;
}

//--------------
//void			commit(ConcAdjustType *max_commit);

void ConcentrationVolume::commit(BufCommitType max_commit) {
	mylist<Concentration>::mylist_item<Concentration> *conc_item = conc_list.gethead();
	while (conc_item!=NULL) {
		if (conc_item-> item!=NULL) {
			conc_item-> item->commit(max_commit);
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
int ConcentrationVolume::clip_conc(ConcLevelType min_level, ConcLevelType max_level){
	int n =0 ;
	mylist<Concentration>::mylist_item<Concentration> *conc_item = conc_list.gethead();
	while (conc_item!=NULL) {
		if (conc_item-> item!=NULL) {
			ConcLevelType val = conc_item-> item->get();
			ConcLevelType delta = conc_item-> item->getdelta();

			// -- clean any less than <= min_level --
			if ((val+delta) <= min_level) {
				mylist<Concentration>::mylist_item<Concentration> *next_item = conc_item-> next;
				conc_item = conc_list.del(conc_item);
				n++;
				if (conc_item==NULL) {
					conc_item = next_item;
					continue;
				}
			}
			// -- clamp any greater than > max_level --
			if (val > max_level) {
				conc_item-> item->setval(max_level);
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


