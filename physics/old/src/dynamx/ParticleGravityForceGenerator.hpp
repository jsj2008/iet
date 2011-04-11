#ifndef  PARTICLEGRAVITYFORCEGENERATOR_H
#define  PARTICLEGRAVITYFORCEGENERATOR_H

#include <dynamx/IParticleForceGenerator.hpp>
#include <dynamx/Vector3.hpp>

namespace dynamx
{
	class ParticleGravityForceGenerator : public IParticleForceGenerator
	{
		public:
			ParticleGravityForceGenerator(const Vector3& gravity);

			virtual ~ParticleGravityForceGenerator();

			virtual void VUpdateForce(Particle* particle, real timestep);
			
		protected:
			Vector3 m_Gravity;
		private:
	};

}

#endif   // PARTICLEGRAVITYFORCEGENERATOR_H
