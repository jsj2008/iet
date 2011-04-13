#ifndef  COLLISIONDETECTOR_H
#define  COLLISIONDETECTOR_H

#include <dynamx/Core.hpp>
#include <dynamx/Contact.hpp>

namespace dynamx
{

	class Point3;
	class Edge;
	class CollisionPlane;
	class Triangle;
	class RigidBody;

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
					Point3* result) const;

			real PointAndPlane(const Point3& point,
					const CollisionPlane& plane,
					Point3* result) const;

			bool LineAndPlane(const Point3& point0,
					const Point3& point1, 
					shared_ptr<CollisionPlane> plane,
					real& t,
					Point3& q) const;

			bool PointAndPlane(const Point3& point,
					const CollisionPlane& plane,
					real* dist) const;

            bool RigidBodyAndPlane(shared_ptr<RigidBody> body,
                    shared_ptr<CollisionPlane> plane,
                    ContactPtr contact) const;

			bool RigidBodyAndPlane(shared_ptr<RigidBody> body,
					shared_ptr<CollisionPlane> plane,
					shared_ptr<vector<ContactPtr> > contacts) const;

			bool TriangleAndPlane(const Triangle& body,
					const CollisionPlane& plane,
					ContactPtr contact) const;
			
		protected:
		private:
	};

}
#endif   // COLLISIONDETECTOR_H
