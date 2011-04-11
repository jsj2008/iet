#include "ParticleAttractionForceGenerator.hpp"

namespace dynamx
{
	ParticleAttractionForceGenerator::ParticleAttractionForceGenerator(Point3 pos, real mass)
	{
		m_Pos = pos;
		m_Mass = mass;
	}

	ParticleAttractionForceGenerator::~ParticleAttractionForceGenerator()
	{
	}

	void ParticleAttractionForceGenerator::VUpdateForce(Particle* particle, real timestep)
	{
		real epsilon = 0.1;
		real distance = m_Pos.CalculateDistance(particle->GetPos());
		if(distance < epsilon)
		{
			return;
		}
		real forceMag = m_Mass * particle->GetMass() / (distance*distance);

		Vector3 posVec(m_Pos);
		Vector3 particlePosVec(particle->GetPos());
		Vector3 forceDir = posVec.Subtract(particlePosVec);
		Vector3 force = forceDir.Multiply(forceMag);
		particle->AddForce(force);
	}
}
