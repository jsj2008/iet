#ifndef  PARTICLEFORCEREGISTRY_H
#define  PARTICLEFORCEREGISTRY_H

#include <vector>

#include <dynamx/ParticleForceRegistration.hpp>
#include <dynamx/Particle.hpp>

using namespace std;

namespace dynamx
{
	class ParticleForceRegistry
	{
		public:
			ParticleForceRegistry();

			virtual ~ParticleForceRegistry();

			void Add(Particle* particle, IParticleForceGenerator* forceGen);

			void Remove(Particle* particle, IParticleForceGenerator* forceGen);

			void Clear();

			void Update(real timestep);
			
		protected:
			vector<ParticleForceRegistration> m_ForceRegistrations;

		private:
	};
}

#endif   // PARTICLEFORCEREGISTRY_H
