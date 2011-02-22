#ifndef  COLLISIONPLANE_H
#define  COLLISIONPLANE_H

#include "SDL/SDL_opengl.h" 

#include <dynamx/Vector3.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/RigidBody.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: CollisionPlane
	 *  Description:
	 * =====================================================================================
	 */
	class CollisionPlane : public RigidBody
	{
		public:
			CollisionPlane();

			virtual ~CollisionPlane();

			Vector3 GetNormal() const
			{
				return m_Normal;
			}

			void SetNormal(const Vector3& val)
			{
				m_Normal = val;
			}

			Point3 GetPoint() const
			{
				return m_Point;
			}

			void SetPoint(const Point3& val)
			{
				m_Point = val;
			}

			virtual void VDraw();
			
		protected:
			Vector3 m_Normal;
			Point3 m_Point; //A point on the plane
		private:
	};

}

#endif   // COLLISIONPLANE_H
