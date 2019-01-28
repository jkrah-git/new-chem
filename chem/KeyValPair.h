/*
 * KeyValPair.h
 *
 *  Created on: Jan 28, 2019
 *      Author: jkrah
 */

#ifndef KEYVALPAIR_H_
#define KEYVALPAIR_H_
//------------------------------
#define KEYVAL_MAX_KEY		32
#define KEYVAL_MAX_VAL		128
#include "../include/mylist.h"

//-------------------------------
class KeyValPair {
public:
	char	key[KEYVAL_MAX_KEY];
	char	val[KEYVAL_MAX_VAL];
	KeyValPair();
	virtual ~KeyValPair(){}
	void dump();
};
//-------------------------------
class KeyValList {
public:
	mylist<KeyValPair>	keyvalues;

	//------
	KeyValList(){}
	~KeyValList(){}
	void dump();
	//------
	mylist<KeyValPair>::mylist_item<KeyValPair>  *search(char *searchkey);
	char 	*get(char *searchkey);
};
//-------------------------------


//-------------------------------//-------------------------------
#endif /* KEYVALPAIR_H_ */
