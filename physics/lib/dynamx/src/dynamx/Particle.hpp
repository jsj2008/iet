#ifndef  PARTICLE_H
#define  PARTICLE_H

#include <assert.h>

#include <dynamx/Point3.hpp>
#include <dynamx/Vector3.hpp>

namespace dynamx 
{
	class Particle
	{
		public:
			Particle();

			virtual ~Particle();

			void Integrate(float timestep);

			void AddForce(Vector3 force);

			void ClearForces();

			void SetPos(real x, real y, real z) { m_Pos.Set(x,y,z); }
			/*----------------------
			 *  Getters and Setters
			 *----------------------*/
			Point3 GetPos() const { return m_Pos; }

			void SetPos(Point3 val) { m_Pos = val; }

			void SetVel(Vector3 val) { m_Vel = val; }

			Vector3 GetVel() const { return m_Vel; }

			void SetMass(real mass) { assert(mass > 0); m_InvMass = 1/mass; }

			real GetMass() const { return 1/m_InvMass; }


		protected:
			Point3 m_Pos;
			Vector3 m_Vel;
			real m_InvMass;

			Vector3 m_ForceAccum;
	};
}

#endif   // PARTICLE_H
