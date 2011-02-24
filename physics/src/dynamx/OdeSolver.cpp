#include "OdeSolver.hpp"

#define STATE_SIZE 13

namespace dynamx
{
	OdeSolver::OdeSolver()
	{
	}

	OdeSolver::~OdeSolver()
	{
	}
	/*

	void OdeSolver::EulerStep(RigidBody* body, real timestep)
	{
		real p[STATE_SIZE];
		DdtStateToArray(p);
	}

	void ArrayToBodies(double x[], int nBodies)
	{
		for(int i = 0; i < nBodies; i++)
			ArrayToState(&Bodies[i], &x[i * STATE_SIZE]);
	}

	void BodiesToArray(RigidBody** bodies, double x[], int nBodies)
	{
		for(int i = 0; i < nBodies; i++)
			StateToArray(&bodies[i], &x[i * STATE_SIZE]);
	}

	void DdtStateToArray(RigidBody *rb, real *xdot)
	{
		*xdot++ = rb->GetPos().GetX();
		*xdot++ = rb->GetPos().GetY();
		*xdot++ = rb->GetPos().GetZ();
		quaternion qdot = .5 * (rb->GetOrientation().Multiply(rb->GetOmega()));
		*xdot++ = qdot.GetR();
		*xdot++ = qdot.GetI();
		*xdot++ = qdot.GetJ();
		*xdot++ = qdot.GetJ();

		*xdot++ = rb->GetForce().GetX(); 
		*xdot++ = rb->GetForce().GetY();  
		*xdot++ = rb->GetForce().GetZ();  
		*xdot++ = rb->GetTorque().GetX();
		*xdot++ = rb->GetTorque().GetY();
		*xdot++ = rb->GetTorque().GetZ();
	}
*/


}
