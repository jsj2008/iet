#include <ObjTestSimulation.hpp>

int main()
{
	Simulation* sim = new ObjTestSimulation();
	sim->VOnInit();
	sim->VOnMainLoop();
	sim->VOnShutdown();

	return 1;
}
