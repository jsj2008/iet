#include "Particle.hpp"

#include <assert.h>

namespace dynamx
{
	Particle::Particle()
	{
	}

	Particle::~Particle()
	{
	}

	void Particle::Integrate(float timestep)
	{
		//Euler Integration
		//Update pos from vel
		Vector3 scaledVel = m_Vel.Multiply(timestep);
		m_Pos = m_Pos.Add(scaledVel);

		//Work out accel from force
		Vector3 accel = m_ForceAccum.Multiply(m_InvMass);
		
		//Update vel from accel.
		Vector3 scaledAccel = accel.Multiply(timestep);
		m_Vel = m_Vel.Add(scaledAccel);

		//TODO: Midpoint method here.
		
		//Forces already updated velocity, don't need them anymore.
		ClearForces();
	}

	void Particle::AddForce(Vector3 force)
	{
		m_ForceAccum = m_ForceAccum.Add(force);
	}

	void Particle::ClearForces()
	{
		m_ForceAccum.Clear();
	}
}
