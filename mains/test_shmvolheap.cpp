#include <stdio.h>
#include <string.h>
#include "debug.h"
//#include "ipc/myshm.h"
//#include "ipc/ShMemBlockHeap.h"
//#include "chem/Molecule.h"

#include "shchem/ShMemVolHeap.h"
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
/*
struct buftest {
	float 	val;
	buftest() { val = 0; };
	void dump(void) { printf("val[%f]", val); };
};
*/
//---------------------------------------------------
	Molecule 		m1,m2,m3;
	ShMemMoleHeap	mole_heap;
	ShMemVolHeap	vol_heap(&mole_heap);
//---------------------------------------------------
void	dump_pep_block(ShMemBlock *block) {
	if (block!=NULL) {
		Peptide	 *peps = mole_heap.get_peps(block);
		PRINT("(block).peps = [0x%zX]\n", (PTR) peps );
		PRINT("===========\n");
		if (peps!=NULL) {
			for (int i=0; i<block->size; i++) {
				peps[i].dump(); NL
			}
		}
		PRINT("===========\n");
	}
}




char  **get_possible_args(void){ return NULL; };
// --------------------------
char 	**build_args(void){
	build_moles(&m1, &m2, &m3);
	return NULL;
};
//-----------------------------------
int 	run(int argc, char **argv){
	if (argc==0) {	vol_heap.dump();	return 0;	}


	if (argc==1) {
		//-----------------------------------
		if (strcmp(argv[0], "dump")==0) 	{
			mole_heap.dump();
			vol_heap.dump();
			return 0;
		}
		//-----------------------------------
		//-----------------------------------
		if (strcmp(argv[0], "moles")==0) 	{
			mole_heap.dump();
			return 0;
		}
		//-----------------------------------
		//-----------------------------------
		if (strcmp(argv[0], "vols")==0) 	{
			vol_heap.dump();
			return 0;
		}
		//-----------------------------------
		if (strcmp(argv[0], "create")==0) 	{
			int r;
			r = mole_heap.create("mole_heap", 2, 4);	PRINT(" mole_heap.create = [%d]\n", r);
			//int		create(*name, vol_page_size, conc_page_size, val_page_size);
			r = vol_heap.create("vol_heap", 2, 3, 4);	PRINT(" vol_heap.create = [%d]\n", r);
			return 0;
		}
		//-----------------------------------
		if (strcmp(argv[0], "open")==0) 	{
			int r;
			r = mole_heap.open("mole_heap");			PRINT(" mole_heap.open = [%d]\n", r);
			r = vol_heap.open("vol_heap");				PRINT(" vol_heap.open = [%d]\n", r);
			return 0;
		}
		//-----------------------------------
		if (strcmp(argv[0], "destroy")==0) 	{
			vol_heap.destroy();							PRINT(" vol_heap.destroy.\n");
			mole_heap.destroy();						PRINT(" mole_heap.destroy.\n");
			return 0;
		}
		//-----------------------------------
		//-----------------------------------
	}
	if (argc>0) {
	//-------------
		//-----------------------------------
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

				dump_pep_block(block);
				/*
				Peptide	 *peps = mole_heap.get_peps(block);
				PRINT("mole_heap.get_peps = [0x%zX]\n", (PTR) peps );
				PRINT("===========\n");
				if (peps!=NULL) {
					for (int i=0; i<block->size; i++) {
						peps[i].dump(); NL
					}
				}
				*/

			}
		} // end find mole
		//-------------
		//-------------
		if (strcmp(argv[0], "get_mole")==0)	{
			if (argc==1) {
				printf("usage: get_mole ID\n");
				return 0;
			}
			//ShMemBlock				*get_mole(int id){ return pep_heap.get_block(id); };
			int id;
			if (sscanf(argv[1], "%d", &id)<1) { printf("Bad id [%s]\n", argv[1]); return -5; }
			ShMemBlock *block = mole_heap.get_mole(id);
			if (block==NULL) { printf(" mole_heap.get_mole(%d) failed..\n", id); return -4; }
			dump_pep_block(block);


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
		//===============================
		//-------------
		if (strcmp(argv[0], "add_vol")==0)	{
			int v = vol_heap.new_vol();
			PRINT("vol_heap.new_vol() = [%d]\n", v);
		}
		//-------------
		if (strcmp(argv[0], "del_vol")==0)	{
			if (argc<2) {
				printf("usage: del_vol ID\n");
				return 0;
			}
			int v;
			if (sscanf(argv[1], "%d", &v)<1) { printf("Bad data[%s]\n", argv[1]); return -5; }
			int r = vol_heap.del_vol(v);
			PRINT("vol_heap.del_vol(%d) = [%d]\n", v, r);
		}
		//-------------
		//===============================


	}

	return -10;
}

//------------------------------------
