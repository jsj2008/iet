
#include "ParticleGravityForceGenerator.hpp"

namespace dynamx
{
	ParticleGravityForceGenerator::ParticleGravityForceGenerator(const Vector3& gravity)
	{
		m_Gravity = gravity;
	}

	ParticleGravityForceGenerator::~ParticleGravityForceGenerator()
	{
	}

	void ParticleGravityForceGenerator::VUpdateForce(Particle* particle, real timestep)
	{
		particle->AddForce(m_Gravity.Multiply(particle->GetMass()));
	}
}
