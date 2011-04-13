#include "ParticleForceRegistry.hpp"

namespace dynamx
{
	ParticleForceRegistry::ParticleForceRegistry()
	{
	}

	ParticleForceRegistry::~ParticleForceRegistry()
	{
	}

	void ParticleForceRegistry::Add(Particle* particle, IParticleForceGenerator* forceGen)
	{
		ParticleForceRegistration reg;		
		reg.particle = particle;
		reg.forceGen = forceGen;
		m_ForceRegistrations.push_back(reg);
	}

	void ParticleForceRegistry::Remove(Particle* particle, IParticleForceGenerator* forceGen)
	{
		vector<ParticleForceRegistration>::iterator it, itEnd;
		for(it = m_ForceRegistrations.begin(), itEnd = m_ForceRegistrations.end();
				it != itEnd;
				it++)
		{
			if(((*it).particle == particle) && ((*it).forceGen == forceGen))
			{
				m_ForceRegistrations.erase(it);
				return;
			}
		}
	}

	void ParticleForceRegistry::Clear()
	{
		m_ForceRegistrations.clear();
	}

	void ParticleForceRegistry::Update(real timestep)
	{
		vector<ParticleForceRegistration>::iterator it, itEnd;
		for(it = m_ForceRegistrations.begin(), itEnd = m_ForceRegistrations.end();
				it != itEnd;
				it++)
		{
			(*it).forceGen->VUpdateForce((*it).particle, timestep);
		}
	}
}
