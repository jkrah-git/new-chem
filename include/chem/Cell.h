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
};
// -----------------------------------------------

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
	// -------------------------
};
// -----------------------------------------------

// -----------------------------------------------
class World {
public:
	mylist<Molecule>		mole_list;
	ChemEngine				chem_engine;
	mylist<AmbientCell>		ambcell_list;
	//-------------
	World();
	~World();
	void dump(void);

	AmbientCell 		*get_ambcell(CellPos *_pos);
	AmbientCell			*add_ambcell(CellPos *_pos);


};
// -----------------------------------------------

#endif /* CELL_H_ */
