#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "ipc/myshm.h"
#include "ipc/ShMemHeap.h"
#include "chem/Molecule.h"
#include "shchem/ShMemMoleHeap.h"

//---------------------------------------------------


ShMemMoleHeap mole_heap;

int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if ((argc==2) && (strcmp(argv[1], "create")==0)) {
		int r = mole_heap.create("mole_heap", 3, 5);
		PRINT(" mole_heap.create = [%d]\n", r);
	} else {
		int r = mole_heap.open("mole_heap");
		PRINT(" mole_heap.open = [%d]\n", r);
	}


	if (argc<2) {
		mole_heap.dump();
		//printf("args: create, destroy, open, close, read, write\n");
		return 0;
	}

	if (argc>1) {
		if (strcmp(argv[1], "destroy")==0) 	{	mole_heap.destroy(); }
		//-------------
	}
	return 0;
}

//------------------------------------
