#ifndef  ODESOLVER_H
#define  ODESOLVER_H

#include <dynamx/Core.hpp>
#include <dynamx/Quaternion.hpp>

namespace dynamx
{
	class RigidBody;
	/*
	 * =====================================================================================
	 *        Class: OdeSolver
	 *  Description:
	 * =====================================================================================
	 */
	class OdeSolver
	{
		public:
			OdeSolver();

			virtual ~OdeSolver();

			void EulerStep(RigidBody* body, real timestep);

			void DdtStateToArray(RigidBody* rb, real *xdot);

			void ScaleArray(real* array, real scale, int size);
			
		protected:
		private:
	};
}

#endif   // ODESOLVER_H
