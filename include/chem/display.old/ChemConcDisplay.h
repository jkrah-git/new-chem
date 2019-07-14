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
#include "chem/ChemEngine.h"
//----------------------------- todo: <T>
class CircBuffer {
private:
	// first run (num_items < size)
	// next runs (num_items = size)

	int		size;
	int		next;
	int		num_items;
	float	*data;
	float	min;
	float	max;
	// get payload-offset from linea index ([0]=oldest [max]=newest)
	int		circ_index(int index);
//todo: txt[] - index tags - every 'x' samples
public:
	CircBuffer();
	virtual ~CircBuffer();
	void	dump(void);
	int		setup(int _size);
	void	clear(void);
	float	last(void);
	void	add(float _data);
	int		get(int index, float *_data);
	int		getsize(void){  return size; };
	int		count(void){ return num_items; };
	void	calc_bounds(void);
	float		get_min(void){ return min; };
	float		get_max(void){ return max; };
};
//-----------------------------

//-----------------------------
class ChemConcDisplay {
private:
	//Concentration		*conc;
	ConcentrationVolume		*vol;
	Molecule				*mole;
	ChemStep				last_tick;
public:

	CircBuffer				buf;
	MyString				name;
	ChemDisplayCoords		coords;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	//----------------------public:
	ChemConcDisplay();
	virtual ~ChemConcDisplay();
	void		dump(void);
	void		set_lasttick(ChemStep t){ last_tick = t; };
//	void		set_conc(Concentration *_conc);
	void		set_conc(Molecule *_mole, ConcentrationVolume *_vol);
	Molecule	*get_mole(void){ return mole; };
	ConcentrationVolume *get_vol(void){ return vol; };
	int			update(ChemStep t);
Concentration	*get_conc(void);

};
//-----------------------------

//-----------------------------//-----------------------------
#endif /* CHEMCONCDISPLAY_H_ */
