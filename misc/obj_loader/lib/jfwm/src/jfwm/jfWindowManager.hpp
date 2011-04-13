#ifndef  JFWINDOWMANAGER_H
#define  JFWINDOWMANAGER_H

#include <jfwm/jfWindow.hpp>

/*
 * =====================================================================================
 *        Class: jfWindowManager
 *  Description:
 * =====================================================================================
 */
class jfWindowManager
{
	public:
		virtual ~jfWindowManager()
		{
		}

		virtual void init() = 0;

		virtual jfWindow* createWindow(const jfString& title) = 0;
		
	protected:
	private:
};


#endif   // JFWINDOWMANAGER_H
