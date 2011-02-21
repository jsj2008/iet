#ifndef  JFSDLWINDOW_H
#define  JFSDLWINDOW_H

#include <sstream>
#include <assert.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <jfCore/jfCore.hpp>
#include <jfLog/jfLogger.hpp>
#include <jfwm/jfWindow.hpp>

/*
 * =====================================================================================
 *        Class: jfSDLWindow
 *  Description:
 * =====================================================================================
 */
class jfSDLWindow : public jfWindow
{
	public:
		jfSDLWindow(jfUint32 height, jfUint32 width, jfString title);

		virtual ~jfSDLWindow();

		virtual void init();

		virtual void toggleFullscreen();
		
	protected:
		void createWindow( jfUint32 width, jfUint32 height, jfUint32 bpp, bool fullscreen, const jfString& title);
		
		SDL_Surface* m_Screen;
		jfUint32 m_Bpp;
		bool m_Fullscreen;

	private:
};


#endif   // JFSDLWINDOW_H
