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

	// return number of lines
	//int		lines(void);
	//char *getline(char *ptr);

};

#endif /* MYSTRING_H_ */
