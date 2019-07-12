/*
 * LogPipe.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: jkrah
 */

#include "LogPipe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"
#include "debug.h"
// -------------------------------
/*
// -------------------------------
class LogPipe {
	char	*path;
	int		size;
	char	*buf;

public:
	//--------
	LogPipe();
	virtual ~LogPipe();
	void	dump(void);
	int		start(char *_path, int size);
	int		flush(void);
	char	*get_buf(void);
	void	tail(void);
};
// -------------------------------
*/
// -------------------------------
LogPipe::LogPipe() {
	PRINT("=====\n");
	path = NULL;
	size = 0;
	buf = NULL;
}
// -------------------------------
LogPipe::~LogPipe() {
//	if (fd>=0) { close(fd); 	}
	if (buf!=NULL) { free(buf); }
}
// -------------------------------
void LogPipe::dump(void) {
	printf("LogPipe[0x%zX]: Path[%s] Buf[0x%zX] Size[%d] (current[%d])\n", (PTR) this, path, (PTR) buf, size, -1);
	printf("buf ==>\n%s", buf);
}
// -------------------------------
int LogPipe::start(char *_path, int _size) {
	if ((_path==NULL)||(_size<1)) return -1;
	if (mkfifo(_path, 0666) <0) ; //{ PRINT("mkfifo failed\n"); return -2; }

	if (buf!=NULL)  free(buf);
	buf = (char*) malloc(sizeof(char)*_size);
	if (buf==NULL){ PRINT("buf allocation failed\n"); return -3; }
	buf[0] = '\0';
	// else
	size = _size;
	//current_pos = 0;
	path = _path;
	return 0;
}
// -------------------------------
int LogPipe::flush(void){
	if ((path==NULL)||(size<1)||(buf==NULL)) return -1;

	int len = strlen(buf);
	int fd = open(path, O_WRONLY);
	if (fd<0) { PRINT("fd = open() failed[%d]\n", fd); return -2; }
	write(fd, buf, len+1);
	close(fd);
	return len;
}
// -------------------------------
char	*LogPipe::get_buf(void){
	flush();
	return buf;
}
// -------------------------------
//void	tail(void);
// -------------------------------
