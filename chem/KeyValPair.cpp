/*
 * KeyValPair.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: jkrah
 */

#include "KeyValPair.h"
 #include <string.h>

/*
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
 */
KeyValPair::KeyValPair() {
	memset(key, '\0', KEYVAL_MAX_KEY);
	memset(val, '\0', KEYVAL_MAX_VAL);
}
//-------------------------------
void KeyValPair::dump(){
	printf("KeyValPair[0x%zX].. [%s]=>[%s]",	(long unsigned int) this, key, val);
}


/*
//-------------------------------
class KeyValList {
public:
	mylist<KeyValPair>	keyvalues;
	KeyValList(){}
	~KeyValList(){}
	void dump();
	mylist<KeyValPair>::mylist_item<KeyValPair>  search(char *keyname);
};
//-------------------------------
*/
//-------------------------------//-------------------------------
//-------------------------------
void KeyValList::dump(){
	printf("KeyValList[0x%zX].. ",	(long unsigned int) this);
	keyvalues.dump();
}
//-------------------------------
mylist<KeyValPair>::mylist_item<KeyValPair>  *KeyValList::search(char *searchkey){
  if (strlen(searchkey)<1)	return NULL;

  mylist<KeyValPair>::mylist_item<KeyValPair>  *result = NULL;
  mylist<KeyValPair>::mylist_item<KeyValPair>  *item = keyvalues.gethead();

  while ((item!=NULL) && (item->item!=NULL)){
	  if (strcmp(item-> item->key, searchkey)==0) {
		  result = item;
		  break;
	  }
	  //----------------------
	  item = item->next;
  }
  return result;
}
//-------------------------------
char 	*KeyValList::get(char *searchkey){
	  mylist<KeyValPair>::mylist_item<KeyValPair>  *item = search(searchkey);
	  if ((item==NULL) ||  (item-> item ==NULL)) return NULL;
	  return item-> item-> val;
}
mylist<KeyValPair>::mylist_item<KeyValPair>  *KeyValList::set(char *searchkey, char *newval){
		if (searchkey==NULL) return NULL;

		mylist<KeyValPair>::mylist_item<KeyValPair>  *item = search(searchkey);
		if (item==NULL) {
		  item = keyvalues.add();		  if ((item==NULL) ||  (item-> item ==NULL)) return NULL;
		  strncpy(item-> item-> key, searchkey, KEYVAL_MAX_KEY);
		}
		if ((item==NULL) ||  (item-> item ==NULL)) return NULL;

		strncpy(item-> item-> val, newval, KEYVAL_MAX_VAL);
		return item;
}
