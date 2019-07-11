/*
 * ChemConcDisplay.cpp
 *
 *  Created on: Jul 2, 2019
 *      Author: jkrah
 */

#include "ChemConcDisplay.h"
/*****
//-----------------------------
class CircBuffer {
private:
	int		size;
	int		max;
	int		last;
	float	*data;

public:
	CircBuffer();
	virtual ~CircBuffer();
	void	dump(void);
	void	setup(int _size);
	void	clear(void);
	void	add(float _data);
	int		get(int index, float *_data);
};
//-----------------------------
******/
CircBuffer::CircBuffer(){
	size = 0;
	next = 0;
	num_items = 0;
	data = NULL;
	min = 0.0f;
	max = 0.0f;
}
CircBuffer::~CircBuffer(){
	if (data!=NULL) free(data);
}
//-----------------------------
void	CircBuffer::dump(void){
	printf("CircBuffer[0x%zX]:", (long unsigned int) this) ;
	printf("Size[%d].Num[%d].Last[%d]:", size, num_items, next);
	printf("Min[%.3f].Max[%.3f]\n", min, max);
	printf(" *data[0x%zX]..\n", (long unsigned int) data) ;
	if (data!=NULL) {
		printf("RAW:");
		for (int i=0; i<size; i++) {
			printf("[%.3f]", data[i]);
		}
		printf("\nCOOKED:");
		for (int i=0; i<num_items; i++) {
			//printf("[%.3f]", data[ ((i+next)%size) ]);
			printf("[%.3f]", data[ circ_index(i) ]);
		}
		printf("\n");
	}



}
//-----------------------------
int	CircBuffer::setup(int _size){

	if (data!=NULL) free(data);
	if (_size>0) {
		data = (float*) malloc(sizeof(float)*_size);

		if (data==NULL) {
			size = 0; next = 0; num_items = 0;
			return -2;
		} // else OK
		size = _size;
		clear();
	}
	return 0;
}
//-----------------------------
void CircBuffer::clear(void){
	next = 0;
	num_items = 0;
	min = 0.0f;
	max = 0.0f;
	if (data==NULL) return;
	for (int i=0; i<size; i++)
		data[i] = 0.0f;

}
// first run (num_items < size) && (next == num_items)
// next runs (num_items = size)


//-----------------------------
float	CircBuffer::last(void){
	if (data==NULL) return 0;
	if (next==0) {
		return data[size-1];
	}
	return data[next-1];
}
void	CircBuffer::add(float _data){
	if (data==NULL) return;
	data[next] = _data;
//	if (_data < min) min = _data;
//	if (_data > max) max = _data;

	next++;

	if (next >= size)
		next = 0;

	if (num_items<size)
		num_items++;
}

// get payload-offset from linea index ([0]=oldest [max]=newest)
int	CircBuffer::circ_index(int index){
	if (index>=num_items) return -2;
	if (num_items < size) return index;
	// from next -> (size-1) = 0 - (size-next)
	// from 0 -> (next-1) = (size-next)
	return (index + next) % size;
}


//-----------------------------
int		CircBuffer::get(int index, float *_data){
	if (data==NULL)	return -1;
	int ci = circ_index(index);
	if (ci<0) return -2;
	*_data = data[ci];
	return 0;
}
//-----------------------------
void CircBuffer::calc_bounds(void){
	if (size<1) { min = 0; max = 0;	return; }
	//return;
	min = data[0];
	max = data[0];
	for (int i=1; i<size; i++) {
		if (data[i] > max) max = data[i];
		if (data[i] < min) min = data[i];
	}
}


/*****
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

******/
//-----------------------------
ChemConcDisplay::ChemConcDisplay() {
	//conc = NULL;
	vol = NULL;
	mole = NULL;
	last_tick = 0;
	coords.scalex = 200;
	coords.scaley = 100;
}
ChemConcDisplay::~ChemConcDisplay() {}
//-----------------------------
void ChemConcDisplay::dump(void){
//	printf("ChemConcDisplay[0x%zX],[%s].Conc[0x%zX]\n", (long unsigned int) this,  name.get(), (long unsigned int)  conc) ;
	printf("ChemConcDisplay[0x%zX],[%s].Mole[0x%zX] (in) Vol[0x%zX] (last_tick[%ld])\n",
			(long unsigned int) this,  name.get(), (long unsigned int)  mole, (long unsigned int)  vol, last_tick);
		buf.dump();
		coords.dump(); NL
		col.dump(); selcol.dump(); NL
}
//-----------------------------
//void ChemConcDisplay::set_conc(Concentration *_conc){
void ChemConcDisplay::	set_conc(Molecule *_mole, ConcentrationVolume *_vol){
	//conc = _conc;
	mole = _mole;
	vol = _vol;
	last_tick = 0;
	buf.clear();
}
//-----------------------------
Concentration *ChemConcDisplay::get_conc(void){
	if ((vol==NULL) ||(mole==NULL)) return NULL;
	return vol->molesearch(mole);
		//return conc;
}
//-----------------------------
int	ChemConcDisplay::update(ChemStep t){
	// concdisp->buf.add(f);
	if (last_tick==t) return 0;
	last_tick = t;

	if ((vol==NULL) ||(mole==NULL)) return -1;
	Concentration *c = vol->molesearch(mole);
	if (c==NULL) return -2;
	float f = c->get();
	//printf("ChemConcDisplay[%s].Mole[0x%zX] Vol[0x%zX] : updated(%.3f)..\n", name.get(),	(long unsigned int) mole,(long unsigned int) vol, f);
	buf.add(f);
	return 0;
}
