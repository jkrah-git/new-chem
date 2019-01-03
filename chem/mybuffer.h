/*
 * mybuffer.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#ifndef MYBUFFER_H_
#define MYBUFFER_H_
typedef double BufCommitType;

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

	void 	commit(BufCommitType max) {	T change = delta * max;		value += change; delta -= change; }



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

};


#endif /* MYBUFFER_H_ */
