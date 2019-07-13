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
CellStatus::CellStatus(){
	energy.setval(100.0);
	health.setval(1.0);
	temperature.setval(0);

};
CellStatus::~CellStatus(){};
// -----------------------------------------------
void CellStatus::dump(void){
	printf("CellStatus[0x%zX]: Energy[%.3f/%.3f] Health[%.3f/%.3f] temperature[%.3f/%.3f] = efficency[%.3f]", (long unsigned int) this,
			energy.get(), energy.getdelta(), health.get(), health.getdelta(), temperature.get(), temperature.getdelta(), efficiency());
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
#undef PRINT
#define PRINT if (false) printf
// -----------------------------------------------
int	Cell::apply_concentration(ConcentrationVolume *targ_vol, Concentration *conc, CellStatus *targ_status,  ChemTime run_time){
	if ((targ_vol==NULL) || (conc==NULL) || (targ_status==NULL)) return -1;
	Molecule *mole = conc->getmole(); if (mole==NULL) { PRINT("ERR: Conc has no mole\n"); return -2; }

	//--------------------------------
	ConcLevelType delta = conc->getdelta();
	PRINT("===============\n");
	PRINT("run_time = [%.3f]\n", run_time);
	PRINT("delta = [%.3f]\n", delta);
	if (delta==0) return 0;
	//mole-> dump();

	// +affinity = attractive add(build)=+E / - affinity -= repulsive
	CellStatusType cell_eff = targ_status-> efficiency();
	CellStatusType mole_affinity = mole->affinity();
	PRINT("cell_eff = [%f]\n", cell_eff);
	PRINT("mole_affinity = [%f]\n", mole_affinity);

	CellStatusType	current_energy = targ_status->energy.get();
	PRINT("current_energy  = [%f]\n", current_energy);
	if (current_energy <= 0) { return -10; }

	CellStatusType total_energy = mole_affinity * run_time;
	ConcLevelType total_ammount = delta * run_time * cell_eff;
	PRINT("total_energy  = [%f]\n", total_energy);
	PRINT("total_ammount = [%f]\n", total_ammount);

	// if total_energy <0 - takeE
	if (total_energy < -current_energy) {
		total_ammount *= (current_energy/-total_energy);
		total_energy = -current_energy;
		PRINT("scaling total_ammount = [%f]\n", total_ammount);
	}

	// add / put - E=E+total_energy (+affinity = attractive add(build)=+Exo)
	if (delta>0) {
		targ_status->energy.add(total_energy);
		ConcLevelType res = targ_vol->put(mole, total_ammount);
		if (res<0) {  PRINT(" targ_vol->put failed\n"); return -50; 	}
		return 0;
	}
	// else
	targ_status->energy.remove(total_energy);
	ConcLevelType res = targ_vol->take(mole, -total_ammount);
	PRINT(" targ_vol-> take(%f)= [%f]\n", -total_ammount, res);

	if (res<0) {  PRINT(" targ_vol->put failed\n"); return -50; 	}

	return 0;



	//return -99;


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

