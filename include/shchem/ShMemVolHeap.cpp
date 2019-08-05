/*
 * ShMemVolHeap.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: jkrah
 */

#include "ShMemVolHeap.h"


//-----------------------------------
/*
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
*/
//-----------------------------------
//ShMemVolHeap::ShMemVolHeap() {}
//ShMemVolHeap::~ShMemVolHeap() {}
//-----------------------------------
void ShMemVolHeap::dump(void){
	 printf("ShMemVolHeap[0x%zX].mole_heap[0x%zX]\n", (PTR) this, (PTR) mole_heap);
	 printf("-- conc_val_heap --\n");  conc_val_heap.dump();
	 printf("-- conc_delta_heap --\n");  conc_delta_heap.dump();

}
//-----------------------------------
int	ShMemVolHeap::create(char *name, int vol_page_size, int conc_page_size){
	if ((name==NULL)||(vol_page_size<1)||(conc_page_size<1)) return -1;

	char	valheap_name[128];
	sprintf(valheap_name, "%s.conc.val", name);
	char	deltaheap_name[128];
	sprintf(deltaheap_name, "%s.conc.delta", name);


	int r = conc_val_heap.create(valheap_name, vol_page_size, conc_page_size);
	//PRINT("conc_val_heap.create(name[%s], vol_page_size[%d], conc_page_size[%d]) returned [%d]\n",	name, vol_page_size, conc_page_size, r);
	if (r<0) {
		PRINT("ERR: conc_val_heap.create(name[%s], vol_page_size[%d], conc_page_size[%d]) returned [%d]\n",
				valheap_name, vol_page_size, conc_page_size, r);
		return r;
	}

	r = conc_delta_heap.create(deltaheap_name, vol_page_size, conc_page_size);
	if (r<0) {
		PRINT("ERR: conc_delta_heap.create(name[%s], vol_page_size[%d], conc_page_size[%d]) returned [%d]\n",
				deltaheap_name, vol_page_size, conc_page_size, r);
		return r;
	}

	return 0;
}
//-----------------------------------
int	ShMemVolHeap::open(char *name){
	// 	return pep_heap.open(name);
	char	valheap_name[128];
	sprintf(valheap_name, "%s.conc.val", name);
	char	deltaheap_name[128];
	sprintf(deltaheap_name, "%s.conc.delta", name);

	int r = conc_val_heap.open(valheap_name);
	if (r<0) {	PRINT("ERR: conc_val_heap.open(name[%s]) returned [%d]\n", valheap_name, r);  return r;	}
	r = conc_delta_heap.open(deltaheap_name);
	if (r<0) {	PRINT("ERR: conc_delta_heap.open(name[%s]) returned [%d]\n", deltaheap_name, r); return r;	}

	return 0;
}
//-----------------------------------
void ShMemVolHeap::destroy(void){
	conc_val_heap.destroy();
	conc_delta_heap.destroy();
}
//	int			get_conc(int vol_id, int mole_id);
//int			add_conc(int vol_id, int mole_id);
//int			del_conc(int vol_id, int mole_id);


//-----------------------------------
//int ShMemVolHeap::get_conc(int vol_id, int mole_id){};
//-----------------------------------


