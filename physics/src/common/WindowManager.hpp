#ifndef  WINDOWMANAGER_H
#define  WINDOWMANAGER_H

#include <string>

#include <SDL/SDL.h>

/*
 * =====================================================================================
 *        Class: WindowManager
 *  Description:
 * =====================================================================================
 */
class WindowManager
{
	public:
		WindowManager(std::string title);

		virtual ~WindowManager();

		bool VOnInit();

		void ToggleFullscreen();

		/*-----------------------------------------------------------------------------
		 *  Getters and setters
		 *-----------------------------------------------------------------------------*/
		int GetScreenWidth() { return m_Width; }
		
		int GetScreenHeight() { return m_Height; }

	protected:

		bool CreateWindow(int width, int height, int bpp, bool fullscreen, const std::string& title);

		int m_Width;
		int	m_Height;
	   	int	m_Bpp;
	   	bool m_Fullscreen;
	   	std::string m_Title;

		SDL_Surface* m_pScreen;
	private:
};


#endif   // WINDOWMANAGER_H
