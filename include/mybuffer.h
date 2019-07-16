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
		PRINT("val[%f], delta[%f], floor[%f], ceiling[%f]\n", value, delta, floor, ceiling);

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







	void 	commit(BufCommitType max) {	T change = delta * max;		value += change; delta -= change; }


/*
	void test(void) {

		printf("MyBuffer.test: == START ==\n");
		printf("Pre : "); dump(); NL
		add(1.5);	printf("+1.5 : "); dump(); NL
		T v;
		//v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f\n", v);
		v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f, ", v);	v = getmax(); printf(".. max() = %f\n", v);

		remove(3);	printf("-3 : "); dump(); NL
		v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f, ", v);	v = getmax(); printf(".. max() = %f\n", v);

		commit(v); 	printf("comit (%3.3f): ", v); dump(); NL
		v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f\n", v);
		printf("MyBuffer.test: == END ==\n");

	}
*/

};


#endif /* MYBUFFER_H_ */
