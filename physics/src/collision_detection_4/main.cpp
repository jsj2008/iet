#include <RigidBodyMotionSimulation.hpp>

int main()
{
	/*
	Simulation* sim = new RigidBodyMotionSimulation();
	sim->VOnInit();
	sim->VOnMainLoop();
	sim->VOnShutdown();
	*/
	RigidBodyMotionSimulation sim;
	sim.VOnInit();
	sim.VOnMainLoop();
	sim.VOnShutdown();

	return 0;
}
