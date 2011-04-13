#ifndef  PARTICLEDRAGFORCEGENERATOR_H
#define  PARTICLEDRAGFORCEGENERATOR_H

#include <dynamx/Core.hpp>
#include <dynamx/Particle.hpp>
#include <dynamx/IParticleForceGenerator.hpp>

namespace dynamx
{
	class ParticleDragForceGenerator : public IParticleForceGenerator
	{
		public:
			ParticleDragForceGenerator(real k1, real k2);

			virtual ~ParticleDragForceGenerator();

			virtual void VUpdateForce(Particle* particle, real timestep);
			
		protected:
			real m_K1, m_K2;
		private:
	};
}

#endif   // PARTICLEDRAGFORCEGENERATOR_H
