#ifndef  JFPOINTSIMULATION_H
#define  JFPOINTSIMULATION_H

#include <boost/shared_ptr.hpp>

#include "jfSimulation/jfSimulation.hpp"
#include "jfCamera/jfCamera.hpp"
#include "jfAlgebra/jfVector3.hpp"

/*
 * =====================================================================================
 *        Class: jfPointSimulation
 *  Description:
 * =====================================================================================
 */
class jfPointSimulation : public jfSimulation
{
	public:
		jfPointSimulation();

		virtual ~jfPointSimulation();

        virtual void VOnInit();

        virtual void VOnUpdate();

        virtual void VOnMainLoop();
		
	protected:
		void setupLighting();

		void InitGL();

		void HandleInput();

		void DoCamera();

		void VOnRender();
		
		jfCamera m_Camera;

		bool m_Finished;

	private:
};

#endif   // JFPOINTSIMULATION_H
