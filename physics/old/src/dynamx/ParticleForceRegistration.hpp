#ifndef  PARTICLEFORCEREGISTRATION_H
#define  PARTICLEFORCEREGISTRATION_H

#include <dynamx/Particle.hpp>
#include <dynamx/IParticleForceGenerator.hpp>

namespace dynamx
{

	class ParticleForceRegistration
	{
		public:
			Particle* particle;
			IParticleForceGenerator* forceGen;
	};
}

#endif   // PARTICLEFORCEREGISTRATION_H
