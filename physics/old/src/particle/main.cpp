#include <ParticleSimulation.hpp>

int main()
{
	Simulation* sim = new ParticleSimulation();
	sim->VOnInit();
	sim->VOnMainLoop();
	sim->VOnShutdown();

	return 1;
}
