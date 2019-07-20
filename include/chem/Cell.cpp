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

//#undef PRINT
//#define PRINT if (false) printf
//#define PRINTAC printf("::%s.", __PRETTY_FUNCTION__); printf
#define PRINTAC if (false) printf
// -----------------------------------------------
int	Cell::apply_concentration(ChemEngine *eng, ConcentrationVolume *targ_vol, Concentration *conc, CellStatus *targ_status,  ChemTime run_time){
	if ((eng==NULL) || (targ_vol==NULL) || (conc==NULL) || (targ_status==NULL)) return -1;
	Molecule *mole = conc->getmole(); if (mole==NULL) { PRINTAC("ERR: Conc has no mole\n"); return -2; }

	//--------------------------------
	//ConcLevelType val = conc->getval();
	//ConcLevelType delta = conc->getdelta();
	ConcLevelType delta = conc->buf.getdelta();

	conc->buf.setval(targ_vol->get(mole));
	//ConcLevelType new_val = val + delta;

		PRINTAC("===============\n");
		PRINTAC("run_time = [%.3f]\n", run_time);
		PRINTAC("delta = [%.3f]\n", delta);
	if (delta==0) return 0;
	//mole-> dump();

	// +affinity = attractive add(build)=+E / - affinity -= repulsive
	CellStatusType current_energy = targ_status->energy.get();
	if (current_energy <= 0) { return -10; }

	CellStatusType cell_eff = targ_status-> efficiency();
	CellStatusType mole_affinity = mole->affinity();
		PRINTAC("cell_eff = [%f]\n", cell_eff);
		PRINTAC("mole_affinity = [%f]\n", mole_affinity);
		PRINTAC("current_energy  = [%f]\n", current_energy);

	CellStatusType total_energy = mole_affinity * delta * run_time;
	ConcLevelType total_ammount = cell_eff * delta * run_time;
		PRINTAC("total_energy  = [%f]\n", total_energy);
		PRINTAC("total_ammount = [%f]\n", total_ammount);

	// ========================
	// BufCommitType getmax(T floor, T ceiling) {
	BufCommitType conc_max_commit = conc->buf.getmax(eng->conc_min, eng->conc_max);
		PRINTAC("conc_max_commit  = [%f]\n", conc_max_commit);


	if (conc_max_commit<=0) return -3;
	if (conc_max_commit<=1) {
		total_ammount *= conc_max_commit;
		total_energy *= conc_max_commit;
		PRINTAC("scaling total_ammount (for conc_max_commit)= [%f]\n", total_ammount);
		PRINTAC("scaling total_energy (for conc_max_commit)= [%f]\n", total_energy);
	}

	// if total_energy <0 - takeE
	if (total_energy < -current_energy) {
		total_ammount *= (current_energy/-total_energy);
		total_energy = -current_energy;
		PRINTAC("scaling total_ammount (for total_energy)= [%f]\n", total_ammount);
	}



	// if total_energy <0 - takeE
	if (total_energy < -current_energy) {
		total_ammount *= (current_energy/-total_energy);
		total_energy = -current_energy;
		PRINTAC("scaling total_ammount (for total_energy)= [%f]\n", total_ammount);
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
// -----------------------------------------------
#undef PRINT
#define PRINT printf("::%s.", __PRETTY_FUNCTION__); printf
// -----------------------------------------------
//	int	ChemEngine::get_reactions(ConcentrationVolume *vol){
// -----------------------------------------------
int	Cell::get_reactions(ChemEngine *eng){ //, AmbientCell *ambcell){
	if (eng==NULL) return -1;
	//if (cell==NULL) return -2;
	int n = 0;
	int r = eng-> get_reactions(&vol);
	if (r<0) { PRINT(" get (internal) reactions = [%d]\n", r); }
	n += r;
	if ((ambcell!=NULL) && (ambcell-> ambvol!=NULL)) {
		r = eng-> get_reactions(ambcell-> ambvol);
		if (r<0) {  PRINT(" get (external) reactions = [%d]\n", r); }
		n += r;
	}
	// -------------
	return n;
}
//	int	ChemEngine::run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
// -----------------------------------------------
// int	Cell::run_reactions(ChemEngine *eng, AmbientCell *ambcell, ChemTime run_time){
int	Cell::run_reactions(ChemEngine *eng, ChemTime run_time){
	if (eng==NULL) return -1;
	//if (cell==NULL) return -2;
	int n = 0;
	int r = eng-> run_reactions(this, &vol, run_time);
	if (r<0) { PRINT(":: run (internal) reactions = [%d]\n", r); }
	n += r;
	if ((ambcell!=NULL) && (ambcell-> ambvol!=NULL)) {
		r = eng-> run_reactions(this, ambcell-> ambvol, run_time);
		if (r<0) { PRINT(":: run (external) reactions = [%d]\n", r); }
		n += r;
	}
	// -------------
	return n;
}
// -----------------------------------------------

int	Cell::run_cell(ChemEngine *eng, ChemTime run_time){
	if (eng==NULL) return -1;
	int r,s,n;
	n = 0;
	s = 0;
	//	r =  run_cell(eng, &vol, run_time);
	r = eng-> run_reactions(this, &vol, run_time);
	if (r<0) { PRINT("run_reactions cell.vol =[%d]\n", r); }
	else { n += r; }
	if ((ambcell!=NULL) && (ambcell->ambvol !=NULL)){
		s = eng-> run_reactions(this, ambcell-> ambvol, run_time);
		if (s<0) { PRINT("run_reactions amb.vol =[%d]\n", r); }
		else { n += r; }
	}
	return n;
}
// -----------------------------------------------

int	Cell::run_cell(ChemEngine *eng, ConcentrationVolume *vol, ChemTime run_time){
	if (eng==NULL) return -1;
	if (vol==NULL) return -2;
//===============================================
	int r;
	int n = 0;

	eng-> next_tick();
	r = eng-> get_reactions(vol);
	if (r<0) { PRINT(".. got [%d] new reactions..\n", r); }

	n = eng-> run_reactions(this, vol, run_time);
	if (n<0) { PRINT(".. run_reactions.time[%f]= [%d]\n", run_time, n); }

	ChemTime	max_commit = vol-> get_maxcommit(eng-> conc_min, eng-> conc_max) ;
	if (max_commit<=0) { PRINT(".. max_commit[%f]\n", max_commit); }
	if (max_commit>1.0) {
		PRINT(".. scaling max_commit back to 1.0\n");
		max_commit = 1.0;
	}

	vol-> commit(max_commit);
	r = vol->clip_conc(eng-> conc_clip, eng-> conc_max);
	if (r<0) { PRINT(".. vol-> clean_conc = [%d]\n", r); }
//	r = eng-> clean_volume_moles(vol);
//	if (r<0) { PRINT(".. clean_volume_moles(vol) = [%d]\n", r); }
	r = eng-> clear_all_hits();
	if (r<0) { PRINT(".. clear_all_hits = [%d]\n", r); }


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
	char vol_txt[64];
	sprintf(vol_txt, "()");
	if (ambvol!=NULL) {	sprintf(vol_txt, "(%d conc's)", ambvol->get_conc_list()->count());	}

	char cell_txt[64];
	sprintf(cell_txt, "()");
	if (cell!=NULL) {	sprintf(cell_txt, "(%d conc's)", cell->vol.get_conc_list()->count());	}


	printf(" Temperature[%.3f/%.3f] Vol[0x%zX]%s Cell[0x%zX]%s ", temperature.get(), temperature.getdelta(),
			(long unsigned int) ambvol, vol_txt, (long unsigned int) cell, cell_txt);

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
	chem_engine.set_moledb(&moledb);
	age = 0.0;

};
World::~World(){};
// -----------------------------------------------
void World::dump(void){
	printf("World[0x%zX] Age[%f]\n", (long unsigned int) this, age);
	printf("==== cells ====\n");	ambcell_list.dump();
	printf("==== moles ====\n");	moledb.dump();
	printf("==== chem_engine ====\n");	chem_engine.dump();

};
// -----------------------------------------------
mylist<AmbientCell>::mylist_item<AmbientCell> *World::get_ambcell(CellPos *_pos){
	if (_pos==NULL) return NULL;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell_item = ambcell_list.gethead();
	while (cell_item!=NULL){
		if (cell_item-> item!=NULL) {
			if ( cell_item-> item-> pos == (*_pos))
				return cell_item;
		}

		// next
		cell_item = cell_item->next;
	}

	return NULL;
};
// -----------------------------------------------
AmbientCell *World::add_ambcell(CellPos *_pos){
	if (_pos==NULL) return NULL;
	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell = get_ambcell(_pos);
	// cell exists
	if (cell!=NULL) return NULL;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell_item = ambcell_list.add();
	if (cell_item == NULL) { printf("cell_list.add failed\n"); return NULL; }
	if (cell_item-> item == NULL) { printf("cell_list.add->item failed\n"); return NULL; }
	cell_item-> item-> pos = (*_pos);
	return cell_item-> item;
};
// -----------------------------------------------


// ----------------------------------------------- // -----------------------------------------------
int	World::get_reactions(ChemEngine *eng){
	if (eng==NULL)	eng = &chem_engine;
	int n = 0;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *ambcell_item = ambcell_list.gethead();
	while (ambcell_item!=NULL){
		if ((ambcell_item->item !=NULL) && (ambcell_item->item-> cell !=NULL)){
			int r = ambcell_item->item-> cell->get_reactions(eng);
			if (r<0) { PRINT("Cell[x%zX].get_reactions()= [%d]\n", (PTR) ambcell_item->item-> cell, r); }
			if (r>=0) n += r;

		} // end cell
		// ---
		ambcell_item = ambcell_item->next;
	}

	return n;
}
// -----------------------------------------------
int	World::run_reactions(ChemEngine *eng, ChemTime run_time){
	if (eng==NULL)	eng = &chem_engine;
	int n = 0;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *ambcell_item = ambcell_list.gethead();
	while (ambcell_item!=NULL){
		if ((ambcell_item->item !=NULL) && (ambcell_item->item-> cell !=NULL)){

			int r = ambcell_item->item-> cell->run_reactions(eng, run_time);

			if (r<-0) { PRINT("Cell[x%zX].run_reactions()= [%d]\n", (PTR) ambcell_item->item-> cell, r); }
			if (r>=0) n += r;

		} // end cell
		// ---
		ambcell_item = ambcell_item->next;
	}
	return n;
}
// -----------------------------------------------
#include "common.h"
// -----------------------------------------------
ChemTime	World::finish_reactions(ChemEngine *eng){ //, ChemTime run_time){
	if (eng==NULL)	eng = &chem_engine;
	int n = 0;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *ambcell_item;

	ChemTime		max_commit = 1.0;
	// ---------------------------------
	// -- getmax
	// ---------------------------------
	ambcell_item = ambcell_list.gethead();
	while (ambcell_item!=NULL){
		if ((ambcell_item->item !=NULL) && (ambcell_item->item-> cell !=NULL)){
			//-------------------------------------------
			ChemTime		m = get_cell_maxcommit(ambcell_item->item-> cell);
			if (m<max_commit) max_commit = m;
			//-------------------------------------------
		} // end cell
		// ---
		ambcell_item = ambcell_item->next;
	}
	if (max_commit<=0) { PRINT(".. max_commit[%f]\n", max_commit); }
	if (max_commit>1.0) {
		PRINT(".. scaling max_commit back to 1.0\n");
		max_commit = 1.0;
	}
	// ---------------------------------
	// commit and clip
	// ---------------------------------
	ambcell_item = ambcell_list.gethead();
	while (ambcell_item!=NULL){
		if ((ambcell_item->item !=NULL) && (ambcell_item->item-> cell !=NULL)){
			//-------------------------------------------
			ambcell_item->item-> cell->vol.commit(max_commit);
			// r = vol->clip_conc(conc_clip, conc_max);
			int r = ambcell_item->item-> cell->vol.clip_conc(chem_engine.conc_clip, chem_engine.conc_max);
			if (r<0){ PRINT("cell[0x%zX].clip_conc = [%d]\n", (PTR) ambcell_item->item-> cell, r); }
			else { n+= r; }

			if ((ambcell_item->item-> cell-> ambcell != NULL)&&(ambcell_item->item-> cell-> ambcell->ambvol!=NULL)) {
				ambcell_item->item-> cell-> ambcell-> ambvol-> commit(max_commit);
				int s = ambcell_item->item-> cell-> ambcell->ambvol-> clip_conc(chem_engine.conc_clip, chem_engine.conc_max);
				if (s<0){ PRINT("cell[0x%zX].ambvol.clip_conc = [%d]\n", (PTR) ambcell_item->item-> cell, r); }
				else { n+= s; }
			}

			//-------------------------------------------
		} // end cell
		// ---
		ambcell_item = ambcell_item->next;
	}
	// ---------------------------------
	// ---------------------------------
	// clear eng hits
	// ---------------------------------
	int t = eng-> clear_all_hits();
	if (t<0) { PRINT(".. clear_all_hits = [%d]\n", t); }



	return max_commit;
}
// -----------------------------------------------
int	World::run_world(ChemEngine *eng, ChemTime run_time){
	if (eng==NULL)	eng = &chem_engine;

//	PRINT("|--------   RUN WORLD [%.3f]    --------| \n", run_time);
//	PRINT(".. (tick)\n");
	eng-> next_tick();

	int r = get_reactions(eng);
//	PRINT(".. get_reactions = [%d]\n", r);

	int s = run_reactions(eng, run_time);
//	PRINT(".. run_reactions = [%d]\n", s);


	ChemTime max_commit = finish_reactions(eng);
//	PRINT(".. finish_reactions = [%d]\n", t);
	age += (run_time*max_commit);


	if (r<0) return r-100;
	if (s<0) return s-110;
	if (max_commit<1.0) return 1;
	return 0;
}
// -----------------------------------------------
/*
	mylist<AmbientCell>::mylist_item<AmbientCell> *get_cell(CellPos *_pos);
	AmbientCell							*add_cell(CellPos *_pos);
};
// -----------------------------------------------
*/
ChemTime World::get_cell_maxcommit(Cell *cell){
	if (cell==NULL) return 1.0;

	ChemTime max = 1.0;
	// ChemTime ConcentrationVolume::get_maxcommit(ConcLevelType min_level, ConcLevelType max_level){
	BufCommitType m;
	m =  cell->vol.get_maxcommit(chem_engine.conc_min, chem_engine.conc_max);
	if (m<max) max = m;

	if ((cell->ambcell!=NULL)&&(cell->ambcell->ambvol!=NULL)) {
		m = cell->ambcell->ambvol->get_maxcommit(chem_engine.conc_min, chem_engine.conc_max);
		if (m<max) max = m;
	}
	return max;
}

