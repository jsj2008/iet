#include <RigidBodyMotionSimulation.hpp>

int main()
{
	RigidBodyMotionSimulation sim;
	sim.VOnInit();
	sim.VOnMainLoop();
	sim.VOnShutdown();

	return 0;
}
