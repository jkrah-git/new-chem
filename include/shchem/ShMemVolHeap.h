/*
 * ShMemVolHeap.h
 *
 *  Created on: Aug 1, 2019
 *      Author: jkrah
 */

#ifndef SHMEMVOLHEAP_H_
#define SHMEMVOLHEAP_H_
//#include "ipc/myshm.h"
//#include "ipc/ShMemBlockHeap.h"
//#define SHMEMHEAP_NODUMP
#define SHMEMHEAP_NODUMP
#include "ShMemMoleHeap.h"
#include "chem/Concentration.h"

//-----------------------------
/**********
class ShMemConcentration {
	int				vol_id;
	int				mole_id;
	ConcLevelType	val;
	ShMemConcentration(){ mole_id = -1; val = 0; };
	void	dump(void) { printf("ShMemConcentration[0x%zX]. mole_id[%d]. val[%f]\n", (PTR) this, mole_id, val); };
};
***************/
//-----------------------------
//-----------------------------
struct ShMemConcentration {
	int				parent;
	int				child;
	int				mole_id;
	int				val_index;

	ShMemConcentration(){
		parent = -1;
		child = -1;
		mole_id = -1;
		val_index = -1;
	};

	void dump(void){
		printf("ShMemConcentration[0z%zX] parent[%d] child[%d] mole_id[%d] val_index[%d].",
				(PTR) this, parent, child, mole_id, val_index);
	};
};
//-----------------------------
//-----------------------------
struct ShMemVolume {
	int				head_conc;
	int				tail_conc;

	ShMemVolume(){
		head_conc = -1;
		tail_conc = -1;
	};
	void	dump(void){ printf("ShMemVolune[0x%zX].head_conc[%d] tail_conc[%d].", (PTR) this, head_conc, tail_conc); };
};
//-----------------------------
//-----------------------------
class ShMemVolHeap {

private:
	ShMemMoleHeap						*mole_heap;
	ShMemArray<ShMemVolume>				vol_heap;		// framed = vol.id
	ShMemArray<ShMemConcentration>		conc_heap;		// framed = conc.id
	ShMemArray<ConcLevelType>			conc_val_heap;	// unframed[val_index]
	ShMemArray<ConcLevelType>			conc_delta_heap;// unframed[val_index]

	ItemFrame<ShMemConcentration> *get_conc(int vol_id, int mole_id);		// return conc_id
	ItemFrame<ShMemConcentration> *add_conc(int vol_id, int mole_id);		// return conc_id
	int			del_conc(int vol_id, int mole_id);		// return - ok, or -1 err


public:
	ShMemVolHeap(ShMemMoleHeap *_mole_heap){ mole_heap = _mole_heap; };
	//virtual ~ShMemVolHeap();
	void	dump(void);
	int		create(char *name, int vol_page_size, int conc_page_size, int val_page_size);
	int		open(char *name);
	void	destroy(void);

	// to start with you need get a vol_id
	int				new_vol(void);
	int				del_vol(int vol_id);
	int				set(int vol_id, int mole_id, ConcLevelType val, ConcLevelType delta);
	int				adj(int vol_id, int mole_id, ConcLevelType adj);
	ConcLevelType	get(int vol_id, int mole_id);
	ConcLevelType	getdelta(int vol_id, int mole_id);

	// todo: max_commits?

};
//-----------------------------


#endif /* SHMEMVOLHEAP_H_ */
