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
/*
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
*/
AmbientCell::AmbientCell(){
	cell = NULL;
	vol = NULL;
	temperature = 0;
}
AmbientCell::~AmbientCell(){};
// -----------------------------------------------
void AmbientCell::dump(void){
	printf("AmbientCell[0x%zX]." , (long unsigned int) this);
	pos.dump();
	printf(" Temperature[%.3f] Cell[0x%zX] Vol[0x%zX]", temperature,
			(long unsigned int) cell, (long unsigned int) vol);
	if (cell!=NULL) cell-> dump();
}
// -----------------------------------------------
/*
// -----------------------------------------------
class World {
public:
	mylist<AmbientCell>		cell_list;
	//-------------
	World();
	~World();
	void dump(void);

	mylist<AmbientCell>::mylist_item<AmbientCell> *get_cell(CellPos *_pos);
	AmbientCell							*add_cell(CellPos *_pos);
};
// -----------------------------------------------
*/
// -----------------------------------------------
World::World(){};
World::~World(){};
// -----------------------------------------------
void World::dump(void){
	printf("World[0x%zX]\n", (long unsigned int) this);
	cell_list.dump();

};
// -----------------------------------------------
AmbientCell *World::get_cell(CellPos *_pos){
	if (_pos==NULL) return NULL;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell_item = cell_list.gethead();
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
AmbientCell *World::add_cell(CellPos *_pos){
	if (_pos==NULL) return NULL;
	AmbientCell *cell = get_cell(_pos);
	// cell exists
	if (cell!=NULL) return NULL;

	mylist<AmbientCell>::mylist_item<AmbientCell>  *cell_item = cell_list.add();
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

