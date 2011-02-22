#ifndef  PARTICLEATTRACTIONFORCEGENERATOR_H
#define  PARTICLEATTRACTIONFORCEGENERATOR_H

#include <dynamx/IParticleForceGenerator.hpp>
#include <dynamx/Point3.hpp>

namespace dynamx
{

	class ParticleAttractionForceGenerator : public IParticleForceGenerator
	{
		public:
			ParticleAttractionForceGenerator(Point3 attractionPos, real mass);

			virtual ~ParticleAttractionForceGenerator();

			virtual void VUpdateForce(Particle* particle, real timestep);

		protected:
			Point3 m_Pos;
			real m_Mass;
		private:
	};


}

#endif   // PARTICLEATTRACTIONFORCEGENERATOR_H
