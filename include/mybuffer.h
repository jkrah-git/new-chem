/*
 * mybuffer.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#ifndef MYBUFFER_H_
#define MYBUFFER_H_
typedef double BufCommitType;
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------
template <class T> class MyBuffer {
private:
	T 		value;
	T 		delta;

public:
	MyBuffer() {
		value = 0;
		delta = 0;
	}
	virtual ~MyBuffer(){	}
	// -----------
	void	set(T new_value, T new_delta){ value = new_value; delta = new_delta; }
	void	setval(T new_value){ value = new_value;  }
	void	setdelta(T new_delta){ delta = new_delta; }
	//void	scaledelta(T delta_scale){ delta *= delta_scale; }


	void	reset(void){ delta = 0; }
	T 		get(void) { return value; }
	T 		getdelta(void) { return delta; }
	void 	dump(void) { printf("mybuffer[0x%zX].value[%.6f].delta[%.6f]", (long unsigned int) this, value, delta); }
	// =============
	void 	add(T ammount) { delta += ammount; }
	void 	remove(T ammount) { delta -= ammount; }
	void 	commit(void) { value += delta; delta = 0; }

	BufCommitType getmax(void) {
		if (delta>0) return 1.0;
		if ((delta+value) >0) return 1.0;
		return value/(-delta);
		// eg v=1 d=2 = 1/2
	}

	BufCommitType getmax(T floor, T ceiling) {
		// PRINT("val[%f], delta[%f], floor[%f], ceiling[%f]\n", value, delta, floor, ceiling);

		if (delta!=0) {
			T newval = delta+value;
			// eg v=3, d=2, C=4 (want 1/2):
			// Mx = (C-v)/d = 1/2
			if (newval > ceiling)
				return ((ceiling-value)/delta);

			// eg v=3,d=-4,f=1 (want 1/2)
			//Mx =  (F-v)/d = -2/-4
			if (newval < floor)
				return ((floor-value)/delta);
		}
		return 1.0;
	}

	void 	commit(BufCommitType max) {
		T change = delta * max;
		value += change;
		delta -= change;
	}
};

//===============================================================

template <class T> class CircularBuffer {
private:
	// first run (num_items < size)
	// next runs (num_items = size)

	int		size;
	int		next;
	int		num_items;
	T	*data;
	T	min;
	T	max;
	// get payload-offset from linea index ([0]=oldest [max]=newest)
	int		circ_index(int index){
		if (index>=num_items) return -2;
		if (num_items < size) return index;
		// from next -> (size-1) = 0 - (size-next)
		// from 0 -> (next-1) = (size-next)
		return (index + next) % size;

	};
//todo: txt[] - index tags - every 'x' samples
public:
	CircularBuffer(){
		size = 0;
		next = 0;
		num_items = 0;
		data = NULL;
		min = 0;
		max = 0;
	};

	virtual ~CircularBuffer(){
		if (data!=NULL) free(data);
	};


	void	dump(void){
		printf("CircularBuffer[0x%zX]:", (long unsigned int) this) ;
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
				printf("[%.3f]", data[ circ_index(i) ]);
			}
			printf("\n");
		}


	}
	int		setup(int _size){
		if (data!=NULL) free(data);
		if (_size>0) {
			data = (T*) malloc(sizeof(T)*_size);

			if (data==NULL) {
				size = 0; next = 0; num_items = 0;
				return -2;
			} // else OK
			size = _size;
			clear();
		}
		return 0;

	};

	void	clear(void){
		next = 0;
		num_items = 0;
		min = 0.0f;
		max = 0.0f;
		if (data==NULL) return;
		for (int i=0; i<size; i++)
			data[i] = 0;
	};

	T		last(void){
		if (data==NULL) return 0;
		if (next==0) {
			return data[size-1];
		}
		return data[next-1];
	};

	void	add(T _data){
		if (data==NULL) return;
		data[next] = _data;
		next++;

		if (next >= size)
			next = 0;

		if (num_items<size)
			num_items++;
	};

	int		get(int index, T *_data){
		if (data==NULL)	return -1;
		int ci = circ_index(index);
		if (ci<0) return -2;
		*_data = data[ci];
		return 0;
	};

	int		getsize(void){  return size; };
	int		count(void){ return num_items; };
	T		get_min(void){ return min; };
	T		get_max(void){ return max; };
	void	calc_bounds(void){
		if (size<1) { min = 0; max = 0;	return; }
		//return;
		min = data[0];
		max = data[0];
		for (int i=1; i<size; i++) {
			if (data[i] > max) max = data[i];
			if (data[i] < min) min = data[i];
		}
	};
};






#endif /* MYBUFFER_H_ */
