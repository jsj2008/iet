#ifndef  ODESOLVER_H
#define  ODESOLVER_H

namespace dynamx
{
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
			
		protected:
		private:
	};
}

#endif   // ODESOLVER_H
