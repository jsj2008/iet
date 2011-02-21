#include "jfSDLWindow.hpp"

jfSDLWindow::jfSDLWindow(jfUint32 width, jfUint32 height, jfString title)
	:
		jfWindow(width, height, title),
		m_Screen(0),
		m_Bpp(32),
		m_Fullscreen(false)
{
}

jfSDLWindow::~jfSDLWindow()
{
	JF_SAFE_DELETE(m_Screen);
}

void jfSDLWindow::init()
{
	createWindow(m_Width, m_Height, m_Bpp, m_Fullscreen, m_Title);
}

void jfSDLWindow::toggleFullscreen()
{
	SDL_WM_ToggleFullScreen(m_Screen);
}

void jfSDLWindow::createWindow( jfUint32 width, 
		jfUint32 height, 
		jfUint32 bpp, 
		bool fullscreen, 
		const jfString& title)
{

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		std::stringstream out;
		out<<"Couldn't initialize SDL:"<< SDL_GetError();
        jfLog(JF_LOG_ERROR, out.str());
		assert(0 && "Couldn't initialize SDL");
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

	m_Screen = SDL_SetVideoMode( width, height, bpp, flags );

    if ( m_Screen == NULL )
	{
		std::stringstream out;
		out<<"Couldn't set %dx%dx%d video mode:"<<width<<height<<bpp<< SDL_GetError();
        jfLog(JF_LOG_ERROR, out.str());
		assert(0 && "Couldn't set %dx%dx%d video mode:");
    }

    SDL_FillRect(m_Screen, NULL, SDL_MapRGBA(m_Screen->format,0,0,0,0));

	//SDL doesn't trigger off a ResizeEvent at startup, but as we need this for OpenGL, we do this ourself
	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = width;
	resizeEvent.resize.h = height;

	SDL_PushEvent(&resizeEvent);

	//Init glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::stringstream out;
		out<<"Couldn't initialize GLEW:"<< glewGetErrorString(err);
        jfLog(JF_LOG_ERROR, out.str());
		assert(0 && "Couldn't initialize GLEW");
	}
}

