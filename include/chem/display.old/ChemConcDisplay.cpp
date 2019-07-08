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
	data = (float*) malloc(sizeof(float)*_size);

	if (_size>0) {
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
	if (data==NULL) return;
	for (int i=0; i<size; i++)
		data[i] = 0.0f;
	next = 0;
	num_items = 0;
	min = 0.0f;
	max = 0.0f;

}
// first run (num_items < size) && (next == num_items)
// next runs (num_items = size)


//-----------------------------
void	CircBuffer::add(float _data){
	data[next] = _data;
	if (_data < min) min = _data;
	if (_data > max) max = _data;

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
	conc = NULL;
}
ChemConcDisplay::~ChemConcDisplay() {}
//-----------------------------
void ChemConcDisplay::dump(void){
		printf("ChemConcDisplay[0x%zX],[%s].Conc[0x%zX]\n", (long unsigned int) this,  name.get(), (long unsigned int)  conc) ;
		buf.dump();
		coords.dump(); NL
		col.dump(); selcol.dump(); NL
}
//-----------------------------
void ChemConcDisplay::set_conc(Concentration *_conc){
	conc = _conc;
	buf.clear();
}
//-----------------------------
Concentration *ChemConcDisplay::get_conc(void){	return conc; }
//-----------------------------
