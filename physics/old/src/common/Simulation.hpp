#ifndef  SIMULATION_H
#define  SIMULATION_H

#include <common/WindowManager.hpp>

class Simulation
{
	public:
		Simulation();

		virtual ~Simulation();

		virtual void VOnInit();

		virtual void VOnMainLoop() = 0;

		virtual void VOnShutdown();
		
	protected:
		WindowManager* m_WindowManager;
	private:
};


#endif   // SIMULATION_H
