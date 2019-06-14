/*
 * mystring.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "MyString.h"

MyString::MyString() {	data = NULL;	}
MyString::~MyString() {	if (data!=NULL) free(data);	}
//--------------------------------

void MyString::set(const char *_str){
	if (data!=NULL) free(data);
	if (_str!=NULL) {
		int len = strlen(_str);
		if (len>0) {
			data = (char*) malloc(sizeof(char)*len);
			if (data!=NULL)
				strcpy(data, _str);

		}
	}
}
int	MyString::len(void){ return strlen(data); };
void MyString::dump(void){	printf("MyString[0x%zX].[%s]", (long unsigned int) this, data);}

//------------------------
MyString& MyString::operator =(const char *p){
	set(p);
	return *this;
}

#include <string.h>
bool MyString::operator ==(const char *p){
	if ((data==NULL) &&(p==NULL)) return true;
	if ((data==NULL) || (p==NULL)) return false;
	if (strcmp(data,p)==0)  return true;
	return false;

}
