/*
 * Cell.h
 *
 *  Created on: Jul 8, 2019
 *      Author: jkrah
 */

#ifndef CELL_H_
#define CELL_H_
#include "debug.h"
#include "mybuffer.h"
#include "Concentration.h"
#include "CellPos.h"
#include "ChemEngine.h"
// -----------------------------------------------
typedef double  CellStatusType;

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
	void 	commit(void){ energy.commit(); health.commit(); temperature.commit();  };
	CellStatusType	efficiency(void){ return  (health.get() / (1+(temperature.get()*temperature.get()))); };
};
// -----------------------------------------------
class AmbientCell;
// -----------------------------------------------
class Cell {
public:
	CellStatus 				status;
	ConcentrationVolume		vol;
	// -----------------
	Cell();
	virtual ~Cell();
	void dump();

	// BufCommitType	get_maxcommit(ChemEngine *eng, ConcentrationVolume *targ_vol);

	// ----------------- apply_concentration
	// try to apply 'conc-> delta' to cell.vol
	// NB: will overwrite 'conc)-> val' (with current conc->val)
	int		apply_concentration(ChemEngine *eng, ConcentrationVolume *targ_vol, Concentration *conc, CellStatus *targ_status,  ChemTime run_time);
	// -------------------------
//	int	ChemEngine::get_reactions(ConcentrationVolume *vol){
//	int	ChemEngine::run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
//	int	ChemEngine::run_volume(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
	int	get_reactions(ChemEngine *eng, AmbientCell *ambcell);
	int	run_reactions(ChemEngine *eng, AmbientCell *ambcell, ChemTime run_time);
	int	run_cell(ChemEngine *eng, AmbientCell *ambcell, ChemTime run_time);

};
// -----------------------------------------------
class AmbientCell {
public:
	CellPos					pos;
MyBuffer<CellStatusType> 	temperature;
	ConcentrationVolume		*ambvol;
	Cell					*cell;
	//CellStatusType			temperature;


	//-------------
	AmbientCell();
	~AmbientCell();
	void dump(void);
	CellPosVecType			get_x(void){ return pos.dim[CELLPOS_X]; };
	CellPosVecType			get_y(void){ return pos.dim[CELLPOS_Y]; };
	ConcentrationVolume		*get_ambvol(void){ return ambvol;	};
	Cell					*get_cell(void){ return cell; };


};
// -----------------------------------------------

// -----------------------------------------------
class World {
public:
	ChemEngine				chem_engine;
	mylist<Molecule>		mole_list;
	mylist<AmbientCell>		ambcell_list;
	//-------------
	World();
	~World();
	void dump(void);

	AmbientCell 		*get_ambcell(CellPos *_pos);
	AmbientCell			*add_ambcell(CellPos *_pos);
	// todo
	AmbientCell			*del_ambcell(CellPos *_pos);


};
// -----------------------------------------------

#endif /* CELL_H_ */
