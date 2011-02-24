#include "OdeSolver.hpp"

#include <dynamx/RigidBody.hpp>

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
	*/

	void OdeSolver::EulerStep(RigidBody* body, real timestep)
	{
		real bodyAsArray[STATE_SIZE];
//		body->StateToArray(bodyAsArray);
		DdtStateToArray(body, bodyAsArray);
		ScaleArray(bodyAsArray, timestep, STATE_SIZE);
		body->ArrayToState(bodyAsArray);
	}

	void OdeSolver::DdtStateToArray(RigidBody *rb, real *xdot)
	{
		*xdot++ = rb->GetLinearVel().GetX();
		*xdot++ = rb->GetLinearVel().GetY();
		*xdot++ = rb->GetLinearVel().GetZ();
		//Quaternion qdot = (rb->GetOrientation().Multiply(rb->GetAngularVel())).Multiply(.5);
		Quaternion qdot = rb->GetOrientation();
	   	qdot.AddScaledVector(rb->GetAngularVel(), 1.0);
		*xdot++ = qdot.GetR();
		*xdot++ = qdot.GetI();
		*xdot++ = qdot.GetJ();
		*xdot++ = qdot.GetK();
		*xdot++ = rb->GetForceAccum().GetX(); 
		*xdot++ = rb->GetForceAccum().GetY();  
		*xdot++ = rb->GetForceAccum().GetZ();  
		*xdot++ = rb->GetTorqueAccum().GetX();
		*xdot++ = rb->GetTorqueAccum().GetY();
		*xdot++ = rb->GetTorqueAccum().GetZ();
	}

	void OdeSolver::ScaleArray(real* array, real scale, int size)
	{
		for(int i = 0 ; i < size ; i++)
		{
			array[i] = array[i] * scale;
		}
	}

}
