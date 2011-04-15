#ifndef  SIMULATION_H
#define  SIMULATION_H

#include <jfwm/jfWindowManager.hpp>
#include <jfwm/jfWindow.hpp>
#include <jfwm/jfSDLWindowManager.hpp>

class jfSimulation
{
public:
    jfSimulation();

    virtual ~jfSimulation();

    virtual void VOnInit();

    virtual void VOnMainLoop() = 0;

    virtual void VOnShutdown();

protected:
    jfWindowManager* m_WindowManager;
    jfWindow* m_Window;
private:
};


#endif   // SIMULATION_H
