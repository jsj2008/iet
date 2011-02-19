#ifndef  CONTACT_H
#define  CONTACT_H

//#include <dynamx/Vector3.hpp>
//#include <dynamx/Point3.hpp>
#include <dynamx/RigidBody.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: Contact
	 *  Description:
	 * =====================================================================================
	 */
	class Contact
	{
		public:
			Contact();

			virtual ~Contact();
			
			Point3& GetClosestPoint()
			{
				return (*m_ClosestPoint);
			}

			void SetClosestPoint(const Point3& val)
			{
				(*m_ClosestPoint) = val;
			}

			Vector3& GetCollisionNormal()
			{
				return (*m_CollisionNormal);
			}

			void SetCollisionNormal(const Vector3& val)
			{
				(*m_CollisionNormal) = val;
			}

		protected:
			Point3* m_ClosestPoint;
			Vector3* m_CollisionNormal;

	};
}

#endif   // CONTACT_H
