#include "CollisionDetector.hpp"

#include <float.h>

namespace dynamx
{
	CollisionDetector::CollisionDetector()
	{
	}

	CollisionDetector::~CollisionDetector()
	{
	}


	real CollisionDetector::PointAndPoint(const Point3& a,
			const Point3& b) const
	{
		return real_sqrt( (a.GetX() - b.GetX()) * (a.GetX() - b.GetX()) +
			   (a.GetY() - b.GetY()) * (a.GetY() - b.GetY()) +
			   (a.GetZ() - b.GetZ()) * (a.GetZ() - b.GetZ())); 
	}

	//Calc closest point on edge and return dist from original point.
	real CollisionDetector::PointAndEdge(const Point3& point,
			const Edge& edge,
			Point3* result)
	{
		Vector3 resultVec;
		Vector3 pointVec = point.ToVector3();
		Vector3 originVec = edge.GetOrigin().ToVector3();
		real distAlongEdge = (pointVec.Subtract(originVec)).DotProduct(edge.GetDirection());

		if(distAlongEdge < 0)
		{
			resultVec = edge.GetOrigin();
		}
		else if(distAlongEdge > edge.GetLength())
		{
			resultVec = edge.GetOrigin().Add(edge.GetDirection().Multiply(edge.GetLength()));;
		}
		else
		{
			resultVec = edge.GetOrigin().Add(edge.GetDirection().Multiply(distAlongEdge));
		}
		result->SetX(resultVec.GetX());
		result->SetY(resultVec.GetY());
		result->SetZ(resultVec.GetZ());
		return PointAndPoint(point, (*result));
	}

	real CollisionDetector::PointAndPlane(const Point3& point,
			const CollisionPlane& plane,
			Point3* result)
	{
		Vector3 resultVec;
		Vector3 pointVec = point.ToVector3();
		Vector3 planePointVec = plane.GetPoint();
		Vector3 planeNormal = plane.GetNormal();
		resultVec = pointVec.Subtract(planeNormal.Multiply(pointVec.Subtract(planePointVec).DotProduct(planeNormal)));
		result->SetX(resultVec.GetX());
		result->SetY(resultVec.GetY());
		result->SetZ(resultVec.GetZ());
		return PointAndPoint(point, (*result));
	}

	bool CollisionDetector::PointAndPlane(const Point3& point,
			const CollisionPlane& plane,
			real* dist) const
	{
		Vector3 v(point);
		Vector3 f(plane.GetPoint());
		real d = (v.Subtract(f)).DotProduct(plane.GetNormal());
		(*dist) = d;
		if(d < 0)
		{
			return true;			
		}
		else
		{
			return false;
		}
	}

	bool CollisionDetector::RigidBodyAndPlane(shared_ptr<RigidBody> body,
			shared_ptr<CollisionPlane> plane,
			Contact* contact) const
	{
		Point3 closest;
		real closestDist = FLT_MAX;
		bool collision = false;

		map<VertexId, Vertex> vertexMap = body->GetTransformedGeom().GetVertices();
		map<VertexId, Vertex>::const_iterator it, itEnd;
		for(it = vertexMap.begin(), itEnd = vertexMap.end() ; it != itEnd ; it++)
		{
			real dist;
			if(PointAndPlane((*it).second.GetPos(), (*plane), &dist) )
			{
				if((dist*dist) < closestDist)
				{
					closest = (*it).second.GetPos();
					closestDist = (dist*dist);
					collision = true;
				}
			}
		}
		if(!collision)
		{
			return false;
		}
		else
		{
			//TODO:Backtrack to collision time or move object back by d along -n.
			contact->SetClosestPoint(closest);
			contact->SetCollisionNormal(plane->GetNormal());
			contact->SetA(body);
			contact->SetB(plane);
			return true;
		}
	}

	bool CollisionDetector::TriangleAndPlane(const Triangle& body,
			const CollisionPlane& plane,
			Contact* contact) const
	{
		int sides[3];

		//Point3 closest = body.GetPoint(0);
		Point3 closest;
		real closestDist = FLT_MAX;
		real greatestD;
		real d;
		bool isCollision = false;
		for(int i = 0 ; i < 3 ;i++)
		{
			if(PointAndPlane(body.GetPoint(i),
				plane,
				&d))
			{
				sides[i] = 0;
				isCollision = true;

				if((d*d) < closestDist)
				{
					closest = body.GetPoint(i);
					closestDist = (d*d);
				}
			}
			else 
			{
				sides[i] = 1;
			}
		}
		//All points on same side of plane, then collision
//		if( isCollision && (sides[0] == sides[1]) && (sides[0] == sides[2]))
		if(isCollision)
		{
			contact->SetClosestPoint(closest);
			contact->SetCollisionNormal(plane.GetNormal());
			return true;
		}
		else
		{
			return false;
		}
	}

}
