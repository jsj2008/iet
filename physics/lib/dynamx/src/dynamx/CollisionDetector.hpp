#ifndef  COLLISIONDETECTOR_H
#define  COLLISIONDETECTOR_H

#include <dynamx/Triangle.hpp>
#include <dynamx/Core.hpp>
#include <dynamx/CollisionPlane.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/Contact.hpp>
#include <dynamx/RigidBody.hpp>
#include <dynamx/Edge.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: CollisionDetector
	 *  Description:
	 * =====================================================================================
	 */
	class CollisionDetector
	{
		public:
			CollisionDetector();

			virtual ~CollisionDetector();

			real PointAndPoint(const Point3& a,
					const Point3& b) const;

			real PointAndEdge(const Point3& point,
					const Edge& edge,
					Point3* result);

			real PointAndPlane(const Point3& point,
					const CollisionPlane& plane,
					Point3* result);
					
			bool PointAndPlane(const Point3& point,
					const CollisionPlane& plane,
					real* dist) const;

			bool RigidBodyAndPlane(shared_ptr<RigidBody> body,
					const CollisionPlane& plane,
					Contact* contact) const;

			bool TriangleAndPlane(const Triangle& body,
					const CollisionPlane& plane,
					Contact* contact) const;
			
		protected:
		private:
	};

}
#endif   // COLLISIONDETECTOR_H
