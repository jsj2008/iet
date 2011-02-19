#include "ParticleDragForceGenerator.hpp"

namespace dynamx
{
	ParticleDragForceGenerator::ParticleDragForceGenerator(real k1, real k2)
		:
			m_K1(k1),
			m_K2(k2)
	{
	}

	ParticleDragForceGenerator::~ParticleDragForceGenerator()
	{
	}

	void ParticleDragForceGenerator::VUpdateForce(Particle* particle, real timestep)
	{
		Vector3 force = particle->GetVel();

		real dragCoeff = force.Magnitude();
		dragCoeff = m_K1 * dragCoeff + m_K2 * dragCoeff * dragCoeff; 

		force.Normalize();
		force = force.Multiply(-dragCoeff);
		particle->AddForce(force);
	}
}
