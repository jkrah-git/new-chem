/*
 * LogPipe.h
 *
 *  Created on: Jul 12, 2019
 *      Author: jkrah
 */

#ifndef LOGPIPE_H_
#define LOGPIPE_H_


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




#endif /* LOGPIPE_H_ */
