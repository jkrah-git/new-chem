/*
 * ShMemBufArray.h
 *
 *  Created on: Aug 1, 2019
 *      Author: jkrah
 */

#ifndef SHMEMBUFARRAY_H_
#define SHMEMBUFARRAY_H_

#include "ShMemArray.h"

// --------------------------------------------
template <class T> class ShMemBufArray {
private:
public:
	ShMemArray<T>	val_heap;
	ShMemArray<T>	delta_heap;

	//------
	ShMemBufArray();
	virtual ~ShMemBufArray();
	void	dump(void);


	// add_item (framed=true)
	ItemFrame<T> 		*add_item(T *item);
	int					del_item(int id);
	ItemFrame<T> 		*get_item(int id);
	ItemFrame<T> 		*get_delta(int id);

	void				dump_page(int _page);
	int					close_page(int _page);
	int					destroy_page(int _page);
	int					destroy(void);

	//-------
};
//----------------------------------------------

//----------------------------------------------
template <class T> ItemFrame<T> * ShMemBufArray<T>::add_item(T *item){

}

#endif /* SHMEMBUFARRAY_H_ */
