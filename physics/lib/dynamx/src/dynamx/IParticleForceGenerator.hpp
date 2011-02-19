#ifndef  IPARTICLEFORCEGENERATOR_H
#define  IPARTICLEFORCEGENERATOR_H

#include <dynamx/Particle.hpp>
#include <dynamx/Core.hpp>

namespace dynamx
{
	class IParticleForceGenerator
	{
		public:

			virtual void VUpdateForce(Particle* particle, real timestep) = 0;
			
		protected:
		private:
	};
}

#endif   // IPARTICLEFORCEGENERATOR_H
