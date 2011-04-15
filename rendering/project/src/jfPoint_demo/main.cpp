#include <jfwm/jfWindowManager.hpp>
#include <jfwm/jfSDLWindowManager.hpp>
#include <jfSimulation/jfSimulation.hpp>
#include <jfPoint_demo/jfPointSimulation.hpp>

int main(void)
{
    jfSimulation* sim = new jfPointSimulation();
    sim->VOnInit();
    
	sim->VOnMainLoop();

    sim->VOnShutdown();
    return 0;
}
