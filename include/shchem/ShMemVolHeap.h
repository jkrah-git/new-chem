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
#define SHMEMHEAP_NODUMP
#include "ShMemMoleHeap.h"
#include "chem/Concentration.h"

//-----------------------------
class ShMemConcentration {
	int				vol_id;
	int				mole_id;
	ConcLevelType	val;
	ShMemConcentration(){ mole_id = -1; val = 0; };
	void	dump(void) { printf("ShMemConcentration[0x%zX]. mole_id[%d]. val[%f]\n", (PTR) this, mole_id, val); };
};

//-----------------------------
class ShMemVolHeap {

private:
	ShMemMoleHeap						*mole_heap;
	ShMemBlockHeap<ConcLevelType>		conc_val_heap;
	ShMemBlockHeap<ConcLevelType>		conc_delta_heap;

	int			get_conc(int vol_id, int mole_id);
	int			add_conc(int vol_id, int mole_id);
	int			del_conc(int vol_id, int mole_id);


public:
	ShMemVolHeap(ShMemMoleHeap *_mole_heap){ mole_heap = _mole_heap; };
	//virtual ~ShMemVolHeap();
	void	dump(void);
	int		create(char *name, int vol_page_size, int conc_page_size);
	int		open(char *name);
	void	destroy(void);

	// to start with you need get a vol_id
	int				new_vol(void);
	int				del_vol(int vol_id);
	int				set(int vol_id, int mole_id, ConcLevelType val, ConcLevelType delta);
	int				adj(int vol_id, int mole_id, ConcLevelType adj);
	ConcLevelType	get(int vol_id, int mole_id);
	ConcLevelType	getdelta(int vol_id, int mole_id);

};
//-----------------------------


#endif /* SHMEMVOLHEAP_H_ */
