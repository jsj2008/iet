#ifndef  JFLOGGER_H
#define  JFLOGGER_H

#include <iostream>

#define DEBUG
#define ERROR

enum JF_LOG_LEVEL
{
	JF_LOG_DEBUG
	, JF_LOG_WARN
	, JF_LOG_ERROR
};

inline void jfLog(JF_LOG_LEVEL logLevel, std::string str)
{
	switch(logLevel)
	{
		case JF_LOG_DEBUG:
		{
#ifdef DEBUG
			std::cout<<"DEBUG:"<<str<<std::endl;	
			std::cout.flush();
#endif   //DEBUG

			break;
		}
		case JF_LOG_ERROR:
		{
#ifdef ERROR
			std::cout<<"ERROR:"<<str<<std::endl;	
			std::cout.flush();
#endif   //ERROR
			break;
		}

	}
}


#endif   // JFLOGGER_H
