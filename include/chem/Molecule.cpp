/*
 * chem.cpp
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */


#include "Peptide.h"
#include "Molecule.h"
//#include "MoleculeMatchPos.h"
//-----
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"
#include <string.h>

/*
// -------------------------------
class Molecule {
private:
	// ---
	char 	*err;
public:
	mylist<Peptide> 	pep_list;
	// ----
	Molecule();
	virtual ~Molecule();
	//bool operator =(const Molecule& p);
	int rotateto(PepRot rotation, Molecule *dest);
	int drawto(Molecule *m, PepRot *rotation, PeptidePos *pos, PepSig *value);
	int drawto(PeptidePos *pos, PepSig *value);

	bool operator ==(const Molecule& p);

	// -- build
	int			addpep(PepSig sig);

	//----------- matching
	//MoleculeMatchPos	*startmatch(Molecule *matchmole);
	//int			nextmatch(MoleculeMatchPos *matchpos);
	//------------
	void		clear(void);
	void		getbounds(PeptidePos *min, PeptidePos *max);
	void		dump(void) { dump(false); }
	void		dump(bool dorender);
	mylist<Peptide>::mylist_item<Peptide>  *test_pos(PeptidePos *testpos);

	// move to helper
	int			rand(int count) { return rand(count, 1, 0, 255); };
	int			rand(int count, int tries, PepSig min, PepSig max);
	void		test(void);
	void		test2(void);
	void		testrot(void);
	void		testmatch(void);
	void		print(void);
	void		render(void);
	void		render(int x, int y);
};
// -------------------------------

 */
// -------------------------------// -------------------------------
// -------------------------------// -------------------------------
Molecule::Molecule() {
		err = NULL;

}
Molecule::~Molecule() {	clear();}
// -------------------------------

void Molecule::print_short(int num_pep){
	// [0x12] = 6bytes per pep
	printf("Molecule[0x%zX]", (long unsigned int) this);

	if (num_pep>0) {
		mylist<Peptide>::mylist_item<Peptide> *pep_item = pep_list.gethead();
		for (int i=0; i<num_pep; i++) {
			//int buf_pos = i*6;
			if ((pep_item == NULL)|| (pep_item-> item == NULL)) {
				printf("[    ]");
			} else {
				printf("[0x%.2x]", pep_item->item-> get());
				pep_item = pep_item->next;
			}
		} //next i
		printf("[..]");
	}

	if (num_pep>=0) {
		printf("/[0x%.2x]", pep_list.count());
	}
	//NL

}

// -------------------------------
bool Molecule::operator ==(const Molecule& p){
#ifdef DEBUG
	LOG("\npep_list => ");
	pep_list.dump();;

	LOG("\np.pep_list => ");
	//p.pep_list.dump();

	//if (pep_list == p.pep_list) {
	if (false) {
		LOG("\npep_list == p.pep_list\n");
	}
	else {
		LOG("\npep_list != p.pep_list\n");
	}
#endif
/*
	printf("Molecule::operator == :: ??\n");
	bool r = (pep_list == p.pep_list);
	if (r) {	printf("Molecule::operator == ::  == \n");	}
	else {		printf("Molecule::operator == :: != \n");	}
	return (r);
	*/
	return (pep_list == p.pep_list);

}

// -------------------------------// -------------------------------
void Molecule::dump(void){

	PeptidePos min, max;
	getbounds(&min, &max);
	printf("Molecule[0x%zX].. [%s]\n",	(long unsigned int) this, err);
	printf("Min: "); min.dump();
	printf(", Max: "); max.dump(); NL
	//print();	NL
	pep_list.dump();
//	render(21,11);
//	if (dorender) render();

}
// -------------------------------// -------------------------------
mylist<Peptide>::mylist_item<Peptide>   *Molecule::testpos(PeptidePos *_pos){
	//mylist<Peptide>::mylist_item<Peptide> *found_item = NULL;

	if (_pos!=NULL) {
		mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
		//while (	(current_item !=NULL) && (found_item==NULL)) {
		while (current_item !=NULL) {
			if ((current_item-> item != NULL) &&
				(current_item-> item-> testpos(_pos)) ) {
				return current_item;
				//found_item = current_item;
				//break;
			}
			//--
			current_item = current_item-> next;
		}
	}
	//--
	return NULL;
}
// -------------------------------
// -------------------------------// -------------------------------
mylist<Peptide>::mylist_item<Peptide>   *Molecule::testpos(Peptide *new_pep) {

	mylist<Peptide>::mylist_item<Peptide> *found_item = NULL;
	if (new_pep!=NULL) {
		mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
		while (	(current_item !=NULL) &&
				(found_item==NULL)) {

			if ((current_item-> item != NULL) &&
				(current_item-> item-> testpos(new_pep)) ) {

				found_item = current_item;
				break;
			}
			//--
			current_item = current_item-> next;
		}
	}
	//--
	return found_item;
}
// -------------------------------

int Molecule::rotateto(PepRot rotation, Molecule *dest) {
	if (dest==NULL) {
		err =  "Molecule::rotateto(NULL dest)";
		return 1;
	}
	dest-> clear();

	// start at pep_list.head
	mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){

		// add new_item to dest
		mylist<Peptide>::mylist_item<Peptide> *new_item = dest-> pep_list.add();
		if (new_item==NULL)	break;
		Peptide *pep =new_item-> item;			// check new list ite.payload
		if (pep==NULL) {
			 pep_list.del(new_item);
			 break;
		}
		// new_item is OK, set pep..
		current_item->item->rotateto(rotation, pep);
		//---
		current_item = current_item-> next;
	}

	return 0;
}
// -------------------------------
int Molecule::addpep(PepSig sig){

	// get tail
	mylist<Peptide>::mylist_item<Peptide> *tail = pep_list.gettail();

	// if no-tail then .. simple.. newpos = (0,0) / no clash check
	if (tail==NULL) {
		//-------------------------------------
		// new_item -
		mylist<Peptide>::mylist_item<Peptide> *new_item = pep_list.add();
		if (new_item==NULL) {
			err =  "Molecule::addpep(NULL new_item)";
			return -1;
		}

		Peptide *new_pep =new_item-> item;
		if (new_pep==NULL) {
			 pep_list.del(new_item);
			 err =  "Molecule::addpep(NULL new_item.payload)";
			 return -2;
		}
		//-------------------------------------
		new_pep-> addpep(sig, NULL);

	} else	{  		// After 1st PEP
		// check tail->item
		if (tail-> item==NULL) {
			err =  "Molecule::addpep(NULL tail.item)";
			return -4;
		}
		//-------------------------------------
		// we add peptide out of band..as we need to scan for collsion after we add (ie calc new.pos)
		Peptide tmp_pep;
		tmp_pep.addpep(sig, tail->item);

		//PRINT("::temp_pep ==> "); tmp_pep.dump(); NL


		mylist<Peptide>::mylist_item<Peptide>  *testpep = testpos(&tmp_pep);
		if (testpep == NULL) {
			//-------------------------------------
			// new_item -
			mylist<Peptide>::mylist_item<Peptide> *new_item = pep_list.add();
			if (new_item==NULL) {
				err =  "Molecule::addpep(NULL new_item)";
				return -1;
			}

			Peptide *new_pep =new_item-> item;
			if (new_pep==NULL) {
				 pep_list.del(new_item);
				 err =  "Molecule::addpep(NULL new_item.payload)";
				 return -2;
			}
			//-------------------------------------
			*new_pep = tmp_pep;
		}
		else
		{
			 //printf("Molecule::addpep.clash:");	 dump(); NL	 testpep-> dump(); NL
			 //pep_list.del(new_item);
			 err =  "Molecule::addpep(pep_clash)";
			 return -9;
		}


	} // end else


	return 0;
}
// -------------------------------
void Molecule::getbounds(PeptidePos *min, PeptidePos *max){

	mylist<Peptide>::mylist_item<Peptide> *next_item = pep_list.gethead();
	while (next_item !=NULL) {
		//PRINT("item="); DUMP(next_item-> item); NL
		if (next_item-> item !=NULL) {
			PepPosVecType	*pos = next_item-> item-> getpos();
			if (pos!=NULL) {
				if (min != NULL) {
					for (int i=0; i<PepPosVecMax; i++)
						// if (next_item-> item-> pos.dim[i] < min-> dim[i])
						if (pos[i] < min-> dim[i])
							min-> dim[i] = pos[i];

				}

				if (max != NULL) {
					for (int i=0; i<PepPosVecMax; i++)
						if (pos[i] > max-> dim[i])
							max-> dim[i] = pos[i];

				}
			}
		}

		//
		next_item = next_item-> next;
	}	// end while

}
// -------------------------------
int	Molecule::rand(int count, int tries, PepSig min, PepSig max){
	if (max<1) return -1;

	Peptide p;
	int c=0;
	while (c<count) {
		int t = 0;
		int r = -1;
		while ((t<tries)&&(r<0)) {
			p.randsig(min, max);
			r = addpep(p.get());
			t++;
		}
		if (r<-0)
			break;

		c++;
	}
	return c;
}
// -------------------------------
PepAffinity	Molecule::affinity(void){

	PepAffinity sum_affinity = 0;
	{
		Peptide *tail = NULL;
		mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
		while (current_item !=NULL) {
			if (current_item-> item != NULL) {
				// todo: ?? do base pep reserves (ie single pep moles in  volume) ??
				if (tail != NULL) {
					PepAffinity aff = tail-> get_affinity(current_item-> item->sig);
					//PRINT("Affinity [0x%x]->[0x%x] = [%f]\n", tail->sig, current_item-> item->sig, aff);
					sum_affinity += aff;
				} // else tail==NULL (first item)
				tail = current_item-> item;
			} //endif item->item != NULL
			//--
			current_item = current_item-> next;
		} // next pep
	}
	return sum_affinity;

}

//-------------------------------
//-------------------------------
