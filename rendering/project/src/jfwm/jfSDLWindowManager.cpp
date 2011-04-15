#include "jfSDLWindowManager.hpp"

jfSDLWindowManager::jfSDLWindowManager()
	:
		m_Window(0),
		jfWindowManager()
{
}

jfSDLWindowManager::~jfSDLWindowManager()
{
	JF_SAFE_DELETE(m_Window);
}

void jfSDLWindowManager::init()
{
}

jfWindow* jfSDLWindowManager::createWindow(const jfString& title)
{
	m_Window = JF_NEW jfSDLWindow(800, 600, title);
	m_Window->init();
	return m_Window;
}
