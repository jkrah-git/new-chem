/*
 * ChemConcDisplay.h
 *
 *  Created on: Jul 2, 2019
 *      Author: jkrah
 */

#ifndef CHEMCONCDISPLAY_H_
#define CHEMCONCDISPLAY_H_

#include "chem/Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "MyString.h"
//-----------------------------
class CircBuffer {
private:
	// first run (num_items < size)
	// next runs (num_items = size)

	int		size;
	int		next;
	int		num_items;
	float	*data;
	// get payload-offset from linea index ([0]=oldest [max]=newest)
	int		circ_index(int index);

public:
	CircBuffer();
	virtual ~CircBuffer();
	void	dump(void);
	int		setup(int _size);
	void	clear(void);
	void	add(float _data);
	int		get(int index, float *_data);
};
//-----------------------------

//-----------------------------
class ChemConcDisplay {
private:
	Concentration		*conc;
public:
	CircBuffer				buf;
	//MyString				name;
	ChemDisplayCoords		coords;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	//----------------------public:
	ChemConcDisplay();
	virtual ~ChemConcDisplay();
	void		dump(void);
	void		set_conc(Concentration *_conc);
Concentration	*get_conc(void);

};
//-----------------------------

//-----------------------------//-----------------------------
#endif /* CHEMCONCDISPLAY_H_ */
