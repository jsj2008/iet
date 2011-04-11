#ifndef  JFSDLWINDOWMANAGER_H
#define  JFSDLWINDOWMANAGER_H

#include <jfCore/jfCore.hpp>
#include <jfwm/jfSDLWindow.hpp>
#include <jfwm/jfWindow.hpp>
#include <jfwm/jfWindowManager.hpp>

/*
 * =====================================================================================
 *        Class: jfSDLWindowManager
 *  Description:
 * =====================================================================================
 */
class jfSDLWindowManager : public jfWindowManager
{
	public:
		jfSDLWindowManager();

		virtual ~jfSDLWindowManager();

		virtual void init();

		virtual jfWindow* createWindow(const jfString& title);
		
	protected:
		jfWindow* m_Window;

	private:
};


#endif   // JFSDLWINDOWMANAGER_H
