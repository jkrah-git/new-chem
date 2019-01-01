/*
 * mybuffer.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#ifndef MYBUFFER_H_
#define MYBUFFER_H_

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
	T get(void) { return value; }
	T getdelta(void) { return delta; }
	void add(T ammount) { delta += ammount; }
	void remove(T ammount) { delta -= ammount; }
	void commit(void) { value += delta; delta = 0; }
	void dump(void) { printf("mybuffer[0x%zX].value[%.6f].delta[%.6f]", (long unsigned int) this, value, delta); }
	void test(void) {

		printf("MyBuffer.test: == START ==\n");
		printf("Pre : "); dump(); NL
		add(10);	printf("+10 : "); dump(); NL
		T v;
		v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f\n", v);

		remove(8);	printf("-8 : "); dump(); NL
		v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f\n", v);

		commit(); 	printf("comit : "); dump(); NL
		v = get(); printf(".. get() = %f", v);	v = getdelta(); printf(".. getdelta() = %f\n", v);
		printf("MyBuffer.test: == END ==\n");

	}

};


#endif /* MYBUFFER_H_ */
