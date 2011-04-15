#include "jfSimulation.hpp"

jfSimulation::jfSimulation()
	:
		m_Window(0)
{
    m_WindowManager = new jfSDLWindowManager();
}

jfSimulation::~jfSimulation()
{
    delete m_WindowManager;
	delete m_Window;
}

void jfSimulation::VOnInit()
{
    m_WindowManager->init();
	m_Window = m_WindowManager->createWindow();
}

void jfSimulation::VOnShutdown()
{
}
