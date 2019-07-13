/*
 * Cell.cpp
 *
 *  Created on: Jul 8, 2019
 *      Author: jkrah
 */

#include "Cell.h"
//-----------------------------------------
/*
// -----------------------------------------------
class CellStatus {
public:
	MyBuffer<CellStatusType> 	energy;
	MyBuffer<CellStatusType> 	health;
	MyBuffer<CellStatusType> 	temperature;
	//-------------
	CellStatus();
	~CellStatus();
	void 	dump(void);
	float 	commit(void){ energy.commit(); health.commit(); temperature.commit();  };
};
// -----------------------------------------------
*/
CellStatus::CellStatus(){};
CellStatus::~CellStatus(){};
// -----------------------------------------------
void CellStatus::dump(void){
	printf("CellStatus[0x%zX]: Energy[%.3f/%.3f] Health[%.3f/%.3f] temperature[%.3f/%.3f", (long unsigned int) this,
			energy.get(), energy.getdelta(), health.get(), health.getdelta(), temperature.get(), temperature.getdelta());
}
// -----------------------------------------------
/*
// -----------------------------------------------
class Cell {
	CellStatus 				status;
	ConcentrationVolume		vol;

public:
	// -----------------
	Cell();
	virtual ~Cell();
	void dump();
};
// -----------------------------------------------
*/
Cell::Cell() {}
Cell::~Cell() {}
// -----------------------------------------------
void Cell::dump(void) {
	printf("Cell[0x%zX]:", (unsigned long int) this);
	status.dump(); NL
}
// -----------------------------------------------
int	Cell::apply_concentration(ConcentrationVolume *targ_vol, Concentration *conc, CellStatus *targ_status,  ChemTime run_time){
	if ((targ_vol==NULL) || (conc==NULL) || (targ_status==NULL)) return -1;
	Molecule *mole = conc->getmole(); if (mole==NULL) { PRINT("ERR: Conc has no mole\n"); return -2; }

	int n = 0;
	//--------------------------------
	ConcLevelType delta = conc->getdelta();
	PRINT("===============\n");
	PRINT("delta = [%.3f]\n", delta);
	if (delta==0) return 0;
	//mole-> dump();

	CellStatusType mole_affinity = mole->affinity();

/*	{
		Peptide *tail = NULL;
		mylist<Peptide>::mylist_item<Peptide> *current_item = mole->pep_list.gethead();
		while (current_item !=NULL) {
			if (current_item-> item != NULL) {
				// todo: ?? do base pep reserves (ie single pep moles in  volume) ??
				if (tail != NULL) {
					PepAffinity aff = tail-> get_affinity(current_item-> item->sig);
					PRINT("Affinity [0x%x]->[0x%x] = [%f]\n", tail->sig, current_item-> item->sig, aff);
					sum_affinity += aff;
				} // else tail==NULL (first item)
				tail = current_item-> item;
			} //endif item->item != NULL
			//--
			current_item = current_item-> next;
		} // next pep
	}
*/

	// +affinity = attractive / - affinity -= repulsive
	PRINT("sum_affinity = [%f]\n", mole_affinity);


	return n;








}




/*
// -----------------------------------------------
class AmbientCell {
public:
	ConcentrationVolume		*ambvol;
	Cell					*cell;
	CellPos					pos;
	CellStatusType			temperature;
	//-------------
	AmbientCell();
	~AmbientCell();
	void dump(void);
};
// -----------------------------------------------
*/
AmbientCell::AmbientCell(){
	pos.init();
	//temperature = 0;
	ambvol = NULL;
	cell = NULL;

}
AmbientCell::~AmbientCell(){
	if (ambvol!=NULL)
		delete ambvol; //free(ambvol);

	if (cell!=NULL)
		delete cell; //free(cell);
};
// -----------------------------------------------
void AmbientCell::dump(void){
	printf("AmbientCell[0x%zX]:" , (long unsigned int) this);
	pos.dump();
	printf(" Temperature[%.3f/%.3f] Vol[0x%zX] Cell[0x%zX] ", temperature.get(), temperature.getdelta(),
			(long unsigned int) ambvol, (long unsigned int) cell);

	if (cell!=NULL) { NL cell-> dump(); }
}
// -----------------------------------------------
/*
// -----------------------------------------------
class World {
public:
	ChemEngine				chem_engine;
	mylist<Molecule>		mole_list;
	mylist<AmbientCell>		cell_list;
	//-------------
	World();
	~World();
	void dump(void);

	AmbientCell 		*get_cell(CellPos *_pos);
	AmbientCell			*add_cell(CellPos *_pos);
};
// -----------------------------------------------
*/
// -----------------------------------------------
World::World(){

};
World::~World(){};
// -----------------------------------------------
void World::dump(void){
	printf("World[0x%zX]\n", (long unsigned int) this);
	printf("==== cells ====\n");	ambcell_list.dump();
	printf("==== moles ====\n");	mole_list.dump();
	printf("==== chem_engine ====\n");	chem_engine.dump();

};
// -----------------------------------------------
AmbientCell *World::get_ambcell(CellPos *_pos){
	if (_pos==NULL) return NULL;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell_item = ambcell_list.gethead();
	while (cell_item!=NULL){
		if (cell_item-> item!=NULL) {
			if ( cell_item-> item-> pos == (*_pos))
				return cell_item-> item;
		}

		// next
		cell_item = cell_item->next;
	}

	return NULL;
};
// -----------------------------------------------
AmbientCell *World::add_ambcell(CellPos *_pos){
	if (_pos==NULL) return NULL;
	AmbientCell *cell = get_ambcell(_pos);
	// cell exists
	if (cell!=NULL) return NULL;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell_item = ambcell_list.add();
	if (cell_item == NULL) { printf("cell_list.add failed\n"); return NULL; }
	if (cell_item-> item == NULL) { printf("cell_list.add->item failed\n"); return NULL; }
	cell_item-> item-> pos = (*_pos);
	return cell_item-> item;
}
// -----------------------------------------------
/*
	mylist<AmbientCell>::mylist_item<AmbientCell> *get_cell(CellPos *_pos);
	AmbientCell							*add_cell(CellPos *_pos);
};
// -----------------------------------------------
*/

