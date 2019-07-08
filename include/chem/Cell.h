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
	Cell					*cell;
	ConcentrationVolume		*vol;
	CellPos					pos;
	CellStatusType			temperature;
	//-------------
	AmbientCell();
	~AmbientCell();
	void dump(void);
};
// -----------------------------------------------

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

#endif /* CELL_H_ */
