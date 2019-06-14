/*
 * mystring.h
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_

class MyString {
	char	*data;
public:

	//--------------------
	MyString();
	virtual ~MyString();
	char 	*get(void){ return data; };
	//--------------------
	void	dump(void);
	void	set(const char *_str);
	int		len(void);
	MyString& operator =(const char *p);
	bool	operator ==(const char *p);



};

#endif /* MYSTRING_H_ */
