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
public:
	CellStatus 				status;
	ConcentrationVolume		vol;
	AmbientCell				*ambcell;
	// -----------------
	// -----------------
	Cell();
	virtual ~Cell();
	void dump();
	// -----------------
	// try to apply conc.deltas to cell.vol
	int		apply_concentration(ConcentrationVolume *_vol, Concentration *_conc, CellStatus *_status,  ChemTime run_time);
//	int	ChemEngine::get_reactions(ConcentrationVolume *vol){
//	int	ChemEngine::run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
//	int	ChemEngine::run_volume(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
	int	get_reactions(ChemEngine *eng, ConcentrationVolume *vol);
	int	run_reactions(ChemEngine *eng, ConcentrationVolume *vol, ChemTime run_time);
	int	run_cell(ChemEngine *eng, ChemTime run_time);

};
// -----------------------------------------------
*/
Cell::Cell() { ambcell  = NULL;}
Cell::~Cell() {}
#include "common.h"
// -----------------------------------------------
void Cell::dump(void) {
	printf("Cell[0x%zX] Amb[0x%zX] Vol[0x%zX](%d):", (PTR) this, (PTR) ambcell, (PTR) &vol, vol.get_conc_list()->count());
	status.dump(); NL
}
#undef PRINT
#define PRINT if (false) printf
// -----------------------------------------------


// -----------------------------------------------
int	Cell::apply_concentration(ChemEngine *eng, ConcentrationVolume *targ_vol, Concentration *conc, CellStatus *targ_status,  ChemTime run_time){
	if ((eng==NULL) || (targ_vol==NULL) || (conc==NULL) || (targ_status==NULL)) return -1;
	Molecule *mole = conc->getmole(); if (mole==NULL) { PRINT("ERR: Conc has no mole\n"); return -2; }

	//--------------------------------
	//ConcLevelType val = conc->getval();
	//ConcLevelType delta = conc->getdelta();
	ConcLevelType delta = conc->buf.getdelta();
	conc->buf.setval(targ_vol->get(mole));
	//ConcLevelType new_val = val + delta;

		PRINT("===============\n");
		PRINT("run_time = [%.3f]\n", run_time);
		PRINT("delta = [%.3f]\n", delta);
	if (delta==0) return 0;
	//mole-> dump();

	// +affinity = attractive add(build)=+E / - affinity -= repulsive
	CellStatusType current_energy = targ_status->energy.get();
	if (current_energy <= 0) { return -10; }

	CellStatusType cell_eff = targ_status-> efficiency();
	CellStatusType mole_affinity = mole->affinity();
		PRINT("cell_eff = [%f]\n", cell_eff);
		PRINT("mole_affinity = [%f]\n", mole_affinity);
		PRINT("current_energy  = [%f]\n", current_energy);

	CellStatusType total_energy = mole_affinity * delta * run_time;
	ConcLevelType total_ammount = cell_eff * delta * run_time;
		PRINT("total_energy  = [%f]\n", total_energy);
		PRINT("total_ammount = [%f]\n", total_ammount);

	// ========================
	// BufCommitType getmax(T floor, T ceiling) {
	BufCommitType conc_max_commit = conc->buf.getmax(eng->conc_min, eng->conc_max);
		PRINT("conc_max_commit  = [%f]\n", conc_max_commit);
	if (conc_max_commit<=0) return -3;
	if (conc_max_commit<=1) {
		total_ammount *= conc_max_commit;
		total_energy *= conc_max_commit;
		PRINT("scaling total_ammount (for conc_max_commit)= [%f]\n", total_ammount);
		PRINT("scaling total_energy (for conc_max_commit)= [%f]\n", total_energy);
	}

	// if total_energy <0 - takeE
	if (total_energy < -current_energy) {
		total_ammount *= (current_energy/-total_energy);
		total_energy = -current_energy;
		PRINT("scaling total_ammount (for total_energy)= [%f]\n", total_ammount);
	}



	// if total_energy <0 - takeE
	if (total_energy < -current_energy) {
		total_ammount *= (current_energy/-total_energy);
		total_energy = -current_energy;
		PRINT("scaling total_ammount (for total_energy)= [%f]\n", total_ammount);
	}

	if (delta>0) {
		targ_status->energy.add(total_energy);
		targ_vol->put(mole, total_ammount);
		return 0;
	}
	targ_status->energy.remove(-total_energy);
	targ_vol->take(mole, -total_ammount);

	return 0;



	//return -99;


}
// -----------------------------------------------
// -----------------------------------------------
#undef PRINT
#define PRINT printf("::%s.", __PRETTY_FUNCTION__); printf
// -----------------------------------------------
//	int	ChemEngine::get_reactions(ConcentrationVolume *vol){
// -----------------------------------------------
int	Cell::get_reactions(ChemEngine *eng){ //, AmbientCell *ambcell){
	if (eng==NULL) return -1;
	//if (cell==NULL) return -2;

	int r = eng-> get_reactions(&vol);
	PRINT(":: get (internal) reactions = [%d]\n", r);

	if ((ambcell!=NULL) && (ambcell-> ambvol!=NULL)) {
		r = eng-> get_reactions(ambcell-> ambvol);
		PRINT(":: get (external) reactions = [%d]\n", r);
	}
	// -------------
	return r;
}
//	int	ChemEngine::run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
// -----------------------------------------------
// int	Cell::run_reactions(ChemEngine *eng, AmbientCell *ambcell, ChemTime run_time){
int	Cell::run_reactions(ChemEngine *eng, ChemTime run_time){
	if (eng==NULL) return -1;
	//if (cell==NULL) return -2;

	int r = eng-> run_reactions(this, &vol, run_time);
	PRINT(":: run (internal) reactions = [%d]\n", r);

	if ((ambcell!=NULL) && (ambcell-> ambvol!=NULL)) {
		r = eng-> run_reactions(this, ambcell-> ambvol, run_time);
		PRINT(":: run (external) reactions = [%d]\n", r);
	}
	// -------------
	return r;
}
//	int	ChemEngine::run_volume(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
// ----------------------------------------------- 	int	run_cell(ChemEngine *eng, ConcentrationVolume *vol, AmbientCell *ambcell, ChemTime run_time);

//int	Cell::run_cell(ChemEngine *eng, ConcentrationVolume *vol, AmbientCell *ambcell, ChemTime run_time){
int	Cell::run_cell(ChemEngine *eng, ConcentrationVolume *vol, ChemTime run_time){
	if (eng==NULL) return -1;
	if (vol==NULL) return -2;
//===============================================
	int r;
	int n = 0;

	PRINT("|--------   RUN Cell [%.3f]    --------| \n", run_time);
	PRINT(".. update ttls\n");
	eng-> next_tick();
	PRINT(".. updating reactions\n");
	r = eng-> get_reactions(vol);
	PRINT(".. got [%d] new reactions..\n", r);
	PRINT(".. running reactions [%.3f]\n", run_time);
	PRINT("---------------------------------------\n");
	n = eng-> run_reactions(this, vol, run_time);
	PRINT("---------------------------------------\n");
	PRINT(".. run_reactions.time[%f]= [%d]\n", run_time, n);

	ChemTime	max_commit = vol-> get_maxcommit(eng-> conc_min, eng-> conc_max) ;
	PRINT(".. max_commit[%f]\n", max_commit);
	if (max_commit>1.0) {
		PRINT(".. scaling max_commit back to 1.0\n");
		max_commit = 1.0;
	}

	vol-> commit(max_commit);
	r = vol->clip_conc(eng-> conc_clip, eng-> conc_max);

	PRINT(".. vol-> clean_conc = [%d]\n", r);
	r = eng-> clean_volume_moles(vol);
	PRINT(".. clean_volume_moles(vol) = [%d]\n", r);
	r = eng-> clear_all_hits();
	PRINT(".. clear_all_hits = [%d]\n", r);


//==============================================
	return 0;
}
// -----------------------------------------------


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

