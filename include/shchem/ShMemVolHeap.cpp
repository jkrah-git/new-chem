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
	ShMemArray<ShMemVolune>				vol_heap;		// framed = vol.id
	ShMemArray<ShMemConcentration>		conc_heap;		// framed = conc.id
	ShMemBlockHeap<ConcLevelType>		conc_val_heap;	// unframed[val_index]
	ShMemBlockHeap<ConcLevelType>		conc_delta_heap;// unframed[val_index]

	int			get_conc(int vol_id, int mole_id);		// return conc_id
	int			add_conc(int vol_id, int mole_id);		// return conc_id
	int			del_conc(int vol_id, int mole_id);		// return - ok, or -1 err


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

	// todo: max_commits?

};
//-----------------------------
*/
//-----------------------------------
//ShMemVolHeap::ShMemVolHeap() {}
//ShMemVolHeap::~ShMemVolHeap() {}
//-----------------------------------
void ShMemVolHeap::dump(void){
	 printf("ShMemVolHeap[0x%zX].mole_heap[0x%zX]\n", (PTR) this, (PTR) mole_heap);
	 printf("-- vol_heap --\n");  vol_heap.dump();
	 printf("-- conc_heap --\n");  conc_heap.dump();
	 printf("-- conc_val_heap --\n");  conc_val_heap.dump();
	 printf("-- conc_delta_heap --\n");  conc_delta_heap.dump();

}
//-----------------------------------
int	ShMemVolHeap::create(char *name, int vol_page_size, int conc_page_size, int val_page_size){
	if ((name==NULL)||(vol_page_size<1)||(conc_page_size<1)) return -1;

	PRINT("name(%s) vol_page_size[%d], conc_page_size[%d], val_page_size[%d]\n", name, vol_page_size, conc_page_size, val_page_size);
	char	volheap_name[128];		sprintf(volheap_name, "%s.vol", name);
	char	concheap_name[128];		sprintf(concheap_name, "%s.conc", name);
	char	valheap_name[128];		sprintf(valheap_name, "%s.val", name);
	char	deltaheap_name[128];	sprintf(deltaheap_name, "%s.delta", name);
	//int r;
	ShMemArrayInfo *info;

	info = vol_heap.create(volheap_name, vol_page_size, true);
	if (info==NULL) {	PRINT("ERR: vol_heap.create(name[%s], vol_page_size[%d], framed=y) returned NULL\n", volheap_name, vol_page_size);		return -10; 	}

	info  = conc_heap.create(concheap_name, conc_page_size, true);
	if (info==NULL) {	PRINT("ERR: conc_heap.create(name[%s], conc_page_size[%d], framed=y) returned NULL\n", concheap_name, conc_page_size);	return -11;		}


	info  = conc_val_heap.create(valheap_name, val_page_size, false);
	if (info==NULL) {	PRINT("ERR: conc_val_heap.create(name[%s], val_page_size[%d], framed=n) returned NULL\n", valheap_name, val_page_size);		return -12;	}

	info = conc_delta_heap.create(deltaheap_name, val_page_size, false);
	if (info==NULL) {	PRINT("ERR: conc_delta_heap.create(name[%s], val_page_size[%d], framed=n) returned NULL\n", deltaheap_name, val_page_size); 	return -13;		}

	return 0;
}
//-----------------------------------
int	ShMemVolHeap::open(char *name){
	// 	return pep_heap.open(name);
	char	volheap_name[128];		sprintf(volheap_name, "%s.vol", name);
	char	concheap_name[128];		sprintf(concheap_name, "%s.conc", name);
	char	valheap_name[128];		sprintf(valheap_name, "%s.val", name);
	char	deltaheap_name[128];	sprintf(deltaheap_name, "%s.delta", name);

	ShMemArrayInfo *info;
	info = vol_heap.open(volheap_name); 		if (info==NULL) {	PRINT("ERR: vol_heap.open(name[%s]) returned NULL\n", volheap_name);  return -10;	}
	info = conc_heap.open(concheap_name);		if (info==NULL) {	PRINT("ERR: conc_heap.open(name[%s]) returned NULL\n", concheap_name);  return -11;	}
	info = conc_val_heap.open(valheap_name);	if (info==NULL) {	PRINT("ERR: conc_val_heap.open(name[%s]) returned NULL\n", valheap_name);  return -12;	}
	info = conc_delta_heap.open(deltaheap_name);	if (info==NULL) {	PRINT("ERR: conc_delta_heap.open(name[%s]) returned NULL\n", valheap_name);  return -13;	}

	return 0;
}
//-----------------------------------
void ShMemVolHeap::destroy(void){
	vol_heap.destroy();
	conc_heap.destroy();
	conc_val_heap.destroy();
	conc_delta_heap.destroy();
}
//-----------------------------------
// to start with you need get a vol_id
int ShMemVolHeap::new_vol(void){
	ShMemVolume v;
	ItemFrame<ShMemVolume> *vf = vol_heap.add_item(&v);
	if (vf==NULL) return -1;
	return vf->id;
}
//-----------------------------------
int ShMemVolHeap::del_vol(int vol_id){
	return vol_heap.del_item(vol_id);
}
//-----------------------------------
//-----------------------------------
ItemFrame<ShMemConcentration> *ShMemVolHeap::get_conc(int vol_id, int mole_id){
	if (mole_heap==NULL) return NULL;
	if ((vol_id<0)||(mole_id<0)) return NULL;
	//-----------
	ItemFrame<ShMemVolume> *vol_frame = vol_heap.get_item(vol_id);	if (vol_frame==NULL) return NULL;
	ShMemBlock *mole_block = mole_heap->get_mole(mole_id);			if (mole_block==NULL) return NULL;
	//-----------

	int	 conc_id =  vol_frame -> item.head_conc;
	while (conc_id >0) {
		ItemFrame<ShMemConcentration> *conc_frame = conc_heap.get_item(conc_id);
		if (conc_frame==NULL) break;
		if (conc_frame->item. mole_id == mole_id)
			return conc_frame;
		//--------
		conc_id = conc_frame->item.child;
	}

	return NULL;
}
//-----------------------------------
ItemFrame<ShMemConcentration> *ShMemVolHeap::add_conc(int vol_id, int mole_id){
	if (mole_heap==NULL) return NULL;
	if ((vol_id<0)||(mole_id<0)) return NULL;
	//-----------
	ItemFrame<ShMemVolume> 	*vol_frame = vol_heap.get_item(vol_id);			if (vol_frame==NULL) return NULL;
	ShMemBlock 				*mole_block = mole_heap->get_mole(mole_id);		if (mole_block==NULL) return NULL;

	//------ test
	if (get_conc(vol_id, mole_id)!=NULL) return NULL;
	//------ new conc
	ShMemConcentration new_conc;
	ItemFrame<ShMemConcentration> *conc_frame = conc_heap.add_item(&new_conc);
	if (conc_frame==NULL) return NULL;
	conc_frame->item.mole_id = mole_id;

	// TODO  add val/delta items

	//---  update list details (vol.head/tail conc.parent/child)
	if ((vol_frame->item.head_conc <0) || (vol_frame->item.tail_conc <0)) {
		conc_frame->item.parent = -1;
		conc_frame->item.child = -1;
		vol_frame->item.head_conc = conc_frame->id;
		vol_frame->item.tail_conc = conc_frame->id;
	} else {
		ItemFrame<ShMemConcentration> *tail_conc_frame = conc_heap.get_item(vol_frame->item.tail_conc);
		if (tail_conc_frame==NULL) { PRINT("ERR: NULL tail_conc_frame\n"); return NULL; }
		tail_conc_frame->item.child =  conc_frame->id;
		conc_frame->item.parent = tail_conc_frame->id;
		conc_frame->item.child = -1;
		vol_frame->item.tail_conc =  conc_frame->id;
	}


	return conc_frame;
}
//-----------------------------------
int ShMemVolHeap::del_conc(int vol_id, int mole_id){
	return -1;
}
//-----------------------------------



//-----------------------------------
//int ShMemVolHeap::get_conc(int vol_id, int mole_id){};
//-----------------------------------


