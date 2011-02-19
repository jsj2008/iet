#ifndef  AABB_H
#define  AABB_H

#include <algorithm>

#include <boost/shared_ptr.hpp>

#include "SDL/SDL_opengl.h" 

#include <dynamx/Core.hpp>
#include <dynamx/Vector3.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/RigidBodyGeometry.hpp>

using namespace boost;

namespace dynamx
{
	class AABB
	{
		public:
			AABB();

			virtual ~AABB();

			void UpdateExtents(const RigidBodyGeometry& geom);

			void DebugDraw();

			void SetColliding(bool val)
			{
				m_Colliding = val;
			}

			Point3 GetPos() 
			{
				return m_Pos;
			}

			Vector3 GetExtents() 
			{
				return m_Extents;
			}

			void SetPos(const Point3& val)
			{
				m_Pos = val;
			}
			
		protected:
			Point3 m_Pos;
			Vector3 m_Extents;
			bool m_Colliding;

		private:
	};
}

#endif   // AABB_H
