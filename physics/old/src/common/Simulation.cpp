#include "Simulation.hpp"

Simulation::Simulation()
{
	m_WindowManager = new WindowManager("Simulation");
}

Simulation::~Simulation()
{
	delete m_WindowManager;
}

void Simulation::VOnInit()
{
	m_WindowManager->VOnInit();
}

void Simulation::VOnShutdown()
{
}
