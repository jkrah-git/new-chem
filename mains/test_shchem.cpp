#include <stdio.h>
#include <string.h>
#include "debug.h"
//#include "ipc/myshm.h"
//#include "ipc/ShMemBlockHeap.h"
//#include "chem/Molecule.h"

//#include "ipc/ShMemBlockBufHeap.h"
#include "shchem/ShMemMoleHeap.h"

//---------------------------------------------------
void	build_moles(Molecule *m1, Molecule *m2, Molecule *m3) {
	if (m1!=NULL) {
		PepSig array[] = { 0x01, 0x02, 0x03 };
		m1-> build(array, 3);
	//	PRINT("m1.build = [%d]\n",r );
	//	m1-> dump();
	}
	if (m2!=NULL) {
		PepSig array[] = { 0x11, 0x12 };
		m2-> build(array, 2);
	//	PRINT("m2.build = [%d]\n",r );
	//	m2-> dump();
	}
	if (m3!=NULL) {
		PepSig array[] = { 0x20 };
		m3-> build(array, 1);
	//	PRINT("m3.build = [%d]\n",r );
	//	m3-> dump();
	}

}
//---------------------------------------------------
//---------------------------------------------------
			ShMemMoleHeap mole_heap;
			Molecule m1,m2,m3;
//			ShMemBlockBufHeap<float>	 buf_heap;
//---------------------------------------------------
char  **get_possible_args(void){ return NULL; };
// --------------------------
char 	**build_args(void){
	build_moles(&m1, &m2, &m3);
	return NULL;
};
//-----------------------------------
int 	run(int argc, char **argv){


	if (argc==0) {	mole_heap.dump();	return 0;	}

	if (argc==1) {
		if (strcmp(argv[0], "dump")==0) 	{	mole_heap.dump(); return 0;	}
		if (strcmp(argv[0], "create")==0) 	{	int r = mole_heap.create("mole_heap", 2, 4);  PRINT(" mole_heap.create = [%d]\n", r);	 return r; }
		if (strcmp(argv[0], "open")==0) 	{	int r = mole_heap.open("mole_heap");		  PRINT(" mole_heap.open = [%d]\n", r);	}
		if (strcmp(argv[0], "destroy")==0) 	{	mole_heap.destroy();  PRINT(" mole_heap.destroy.\n"); return 0; }
	}
	if (argc>=1) {
		//-------------
		if (strcmp(argv[0], "add_mole")==0)	{
			if (argc==1) {
				printf("usage: add_mole m1 | m2 | m3\n");
				return 0;
			}
			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[1], "m1")==0) block_frame = mole_heap.new_mole(&m1);
			if (strcmp(argv[1], "m2")==0) block_frame = mole_heap.new_mole(&m2);
			if (strcmp(argv[1], "m3")==0) block_frame = mole_heap.new_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.new_mole(%s) = [0x%zX]\n", argv[2], (PTR) block_frame );
			DUMP(block_frame);
			PRINT("===========\n");
			mole_heap.dump();
			PRINT("===========\n");
			return 0;
		}
		//-------------
		//-------------
		if (strcmp(argv[0], "find_mole")==0)	{
			if (argc==1) {
				printf("usage: find_mole m1 | m2 | m3\n");
				return 0;
			}

			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[1], "m1")==0) block_frame = mole_heap.find_mole(&m1);
			if (strcmp(argv[1], "m2")==0) block_frame = mole_heap.find_mole(&m2);
			if (strcmp(argv[1], "m3")==0) block_frame = mole_heap.find_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.find_mole = [0x%zX]\n", (PTR) block_frame );
			PRINT("block_frame: \n    "); DUMP(block_frame);
			PRINT("===========\n");

			if (block_frame!=NULL) {
				//ShMemBlock				*get_mole(int id);
				PRINT("===========\n");
				PRINT("mole_heap.get_mole(%d)...\n", block_frame->id);
				ShMemBlock *block = mole_heap.get_mole(block_frame->id);
				PRINT("===========\n");
				PRINT("mole_heap.get_mole = [0x%zX]\n", (PTR) block );
				PRINT("===========\n");
				DUMP(block);

				Peptide	 *peps = mole_heap.get_peps(block);
				PRINT("mole_heap.get_peps = [0x%zX]\n", (PTR) peps );
				PRINT("===========\n");
				if (peps!=NULL) {
					for (int i=0; i<block->size; i++) {
						peps[i].dump(); NL
					}
				}

			}
		} // end find mole
		//-------------
		//-------------
		if (strcmp(argv[0], "del_mole")==0)	{
			if (argc==1) {
				printf("usage: find_mole m1 | m2 | m3\n");
				return 0;
			}

			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[1], "m1")==0) block_frame = mole_heap.find_mole(&m1);
			if (strcmp(argv[1], "m2")==0) block_frame = mole_heap.find_mole(&m2);
			if (strcmp(argv[1], "m3")==0) block_frame = mole_heap.find_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.del_mole = [0x%zX]\n", (PTR) block_frame );
			DUMP(block_frame);
			if (block_frame!=NULL) {
				int r = mole_heap.del_mole(block_frame->id);
				PRINT("mole_heap.del_mole = [%d]\n", r);

			}
		} // end del_mole
		//-------------

	}


	return -10;
}
//-----------------------------------
//---------------------------------------------------


//---------------------------------------------------
/******************************
int main2(int argc, char **argv) {
	//-------
	 PRINT(": argc[%d]", argc);
	 for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	 return 0;

	if ((argc==2) && (strcmp(argv[1], "create")==0)) {	int r = mole_heap.create("mole_heap", 2, 4); 	PRINT(" mole_heap.create = [%d]\n", r);	}
	else {												int r = mole_heap.open("mole_heap");					PRINT(" mole_heap.open = [%d]\n", r);	}


	if (argc<2) {
		mole_heap.dump();
		return 0;
	}

	Molecule m1,m2,m3;
	build_moles(&m1, &m2, &m3);

	if (argc>1) {
		if (strcmp(argv[1], "destroy")==0) 	{	mole_heap.destroy(); }
		//-------------
		//if (strcmp(argv[1], "table")==0) 	{	dump_peptide_table(); }
		//-------------
		if (strcmp(argv[1], "add_mole")==0)	{
			if (argc==2) {
				printf("usage: add_mole m1 | m2 | m3\n");
				return 0;
			}
			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[2], "m1")==0) block_frame = mole_heap.new_mole(&m1);
			if (strcmp(argv[2], "m2")==0) block_frame = mole_heap.new_mole(&m2);
			if (strcmp(argv[2], "m3")==0) block_frame = mole_heap.new_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.new_mole(%s) = [0x%zX]\n", argv[2], (PTR) block_frame );
			DUMP(block_frame);
			PRINT("===========\n");
			mole_heap.dump();
			PRINT("===========\n");
		}
		//-------------
		//-------------
		if (strcmp(argv[1], "find_mole")==0)	{
			if (argc==2) {
				printf("usage: find_mole m1 | m2 | m3\n");
				return 0;
			}

			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[2], "m1")==0) block_frame = mole_heap.find_mole(&m1);
			if (strcmp(argv[2], "m2")==0) block_frame = mole_heap.find_mole(&m2);
			if (strcmp(argv[2], "m3")==0) block_frame = mole_heap.find_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.find_mole = [0x%zX]\n", (PTR) block_frame );
			PRINT("block_frame: \n    "); DUMP(block_frame);
			PRINT("===========\n");

			if (block_frame!=NULL) {
				//ShMemBlock				*get_mole(int id);
				PRINT("===========\n");
				PRINT("mole_heap.get_mole(%d)...\n", block_frame->id);
				ShMemBlock *block = mole_heap.get_mole(block_frame->id);
				PRINT("===========\n");
				PRINT("mole_heap.get_mole = [0x%zX]\n", (PTR) block );
				PRINT("===========\n");
				DUMP(block);

				Peptide	 *peps = mole_heap.get_peps(block);
				PRINT("mole_heap.get_peps = [0x%zX]\n", (PTR) peps );
				PRINT("===========\n");
				if (peps!=NULL) {
					for (int i=0; i<block->size; i++) {
						peps[i].dump(); NL
					}
				}

			}
		} // end find mole
		//-------------
		//-------------
		if (strcmp(argv[1], "del_mole")==0)	{
			if (argc==2) {
				printf("usage: find_mole m1 | m2 | m3\n");
				return 0;
			}

			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[2], "m1")==0) block_frame = mole_heap.find_mole(&m1);
			if (strcmp(argv[2], "m2")==0) block_frame = mole_heap.find_mole(&m2);
			if (strcmp(argv[2], "m3")==0) block_frame = mole_heap.find_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.del_mole = [0x%zX]\n", (PTR) block_frame );
			DUMP(block_frame);
			if (block_frame!=NULL) {
				int r = mole_heap.del_mole(block_frame->id);
				PRINT("mole_heap.del_mole = [%d]\n", r);

			}
		} // end del_mole
		//-------------




	}


	return 0;
}
******************************/
//------------------------------------
