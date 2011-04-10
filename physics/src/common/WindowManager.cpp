#include "WindowManager.hpp"

WindowManager::WindowManager(std::string title)
	:
		m_pScreen(0)
{
	m_Title = title;
	m_Width = 800;
	m_Height = 600;
	m_Bpp = 32;
	m_Fullscreen = false;
}

WindowManager::~WindowManager()
{
//	SDL_Delete(m_pScreen);
	SDL_Quit();
}

bool WindowManager::CreateWindow(int width, int height, int bpp, bool fullscreen, const std::string& title)
{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
        fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//all values are "at least"!
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Set the title.
	SDL_WM_SetCaption(title.c_str(), title.c_str());

	// Flags tell SDL about the type of window we are creating.
	int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWSURFACE | SDL_OPENGLBLIT | SDL_HWPALETTE;

	if(fullscreen)
	{
		flags |= SDL_FULLSCREEN;
	}

	// Create the window
	m_pScreen = SDL_SetVideoMode( width, height, bpp, flags );

    if ( m_pScreen == NULL )
	{
        fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",width,height,bpp,SDL_GetError());
        exit(1);
    }

    SDL_FillRect(m_pScreen, NULL, SDL_MapRGBA(m_pScreen->format,0,0,0,0));

	//SDL doesn't trigger off a ResizeEvent at startup, but as we need this for OpenGL, we do this ourself
	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = width;
	resizeEvent.resize.h = height;

	SDL_PushEvent(&resizeEvent);
	return true;
}

bool WindowManager::VOnInit()
{
	CreateWindow(m_Width, m_Height, m_Bpp, m_Fullscreen, m_Title);
}

void WindowManager::ToggleFullscreen()
{
	SDL_WM_ToggleFullScreen(m_pScreen);
}
