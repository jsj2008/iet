#ifndef  CONTACT_H
#define  CONTACT_H

#include <boost/shared_ptr.hpp>

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

			shared_ptr<RigidBody> GetA() const
			{
				return m_A;
			}

			void SetA(shared_ptr<RigidBody> val)
			{
				m_A = val;
			}

			shared_ptr<RigidBody> GetB() const
			{
				return m_B;
			}

			void SetB(shared_ptr<RigidBody> val)
			{
				m_B = val;
			}

		protected:
			Point3* m_ClosestPoint;
			Vector3* m_CollisionNormal;
			shared_ptr<RigidBody> m_A;
			shared_ptr<RigidBody> m_B;

	};

	typedef boost::shared_ptr<Contact> ContactPtr;
}

#endif   // CONTACT_H
