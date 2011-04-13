#include "CollisionDetector.hpp"

#include <float.h>

#include <dynamx/Triangle.hpp>
#include <dynamx/Core.hpp>
#include <dynamx/CollisionPlane.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/RigidBody.hpp>
#include <dynamx/Edge.hpp>

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
			Point3* result) const
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
			Point3* result) const
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

	bool CollisionDetector::LineAndPlane(const Point3& point0,
			const Point3& point1, 
			shared_ptr<CollisionPlane> plane,
			real& t,
			Point3& q) const
	{
		Vector3 a = point0.ToVector3();
		Vector3 b = point1.ToVector3();
		Vector3 ab = b.Subtract(a);
		real d = plane->GetNormal().DotProduct(plane->GetPoint().ToVector3());
		t = (d - ( plane->GetNormal().DotProduct(a) )) / plane->GetNormal().DotProduct(ab);

		if( (t >= 0.0f) && (t <= 1.0f) )
		{
			Vector3 qVec;
			qVec = a.Add( ab.Multiply(t) );
			q.SetX(qVec.GetX());
			q.SetY(qVec.GetY());
			q.SetZ(qVec.GetZ());
			return true;
		}
		return false;
	}

	bool CollisionDetector::RigidBodyAndPlane(shared_ptr<RigidBody> body,
			shared_ptr<CollisionPlane> plane,
			ContactPtr contact) const
	{
		Point3 furthest;
		real furthestDist = 0;
		bool collision = false;

		map<VertexId, Vertex> vertexMap = body->GetTransformedGeom().GetVertices();
		map<VertexId, Vertex>::const_iterator it, itEnd;
		for(it = vertexMap.begin(), itEnd = vertexMap.end() ; it != itEnd ; it++)
		{
			real dist;
			if(PointAndPlane((*it).second.GetPos(), (*plane), &dist) )
			{
				collision = true;
				if((dist*dist) > furthestDist)
				{
					furthest = (*it).second.GetPos();
					furthestDist = (dist*dist);
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
			contact->SetClosestPoint(furthest);
			contact->SetCollisionNormal(plane->GetNormal());
			contact->SetA(body);
			contact->SetB(plane);
			return true;
		}
	}

	bool CollisionDetector::RigidBodyAndPlane(shared_ptr<RigidBody> body,
			shared_ptr<CollisionPlane> plane,
			shared_ptr<vector<ContactPtr> > contacts) const
	{
		Point3 furthest;
		real furthestDist = 0;
		bool collision = false;

		map<VertexId, Vertex> vertexMap = body->GetTransformedGeom().GetVertices();
		map<VertexId, Vertex>::const_iterator it, itEnd;
		for(it = vertexMap.begin(), itEnd = vertexMap.end() ; it != itEnd ; it++)
		{
			real dist;
			if(PointAndPlane((*it).second.GetPos(), (*plane), &dist) )
			{
				ContactPtr newContact(new Contact);
				newContact->SetClosestPoint((*it).second.GetPos());
				newContact->SetCollisionNormal(plane->GetNormal());
				newContact->SetA(body);
				newContact->SetB(plane);
				contacts->push_back(newContact);
				collision = true;
				/*
				if((dist*dist) > furthestDist)
				{
					furthest = (*it).second.GetPos();
					furthestDist = (dist*dist);
				}
				*/
			}
		}

		//Now check all edges.
		map<FaceId, Face> faceMap = body->GetTransformedGeom().GetFaces();
		map<FaceId, Face>::const_iterator itFace, itFaceEnd;
		for(itFace = faceMap.begin(), itFaceEnd = faceMap.end() ; itFace != itFaceEnd ; itFace++)
		{
			Face face = (*itFace).second;
			vector<VertexId> faceVertices = face.GetVertexIds();
			vector<VertexId>::const_iterator itVertex, itVertexEnd;

			assert(0);
			for(itVertex = faceVertices.begin(), itVertexEnd = faceVertices.end() ; 
					itVertex != itVertexEnd ; 
					itVertex++)
			{
				vector<VertexId>::const_iterator itVertex2 = itVertex + 1;
				for(; 
						itVertex2 != itVertexEnd ; 
						itVertex2++)
				{
					real t;
					Point3 contactPoint;
					if(LineAndPlane(body->GetTransformedGeom().GetVertex(*itVertex).GetPos(), body->GetTransformedGeom().GetVertex(*itVertex2).GetPos(), plane, t, contactPoint) )
					{
						ContactPtr newContact(new Contact);
						newContact->SetClosestPoint(contactPoint);
						newContact->SetCollisionNormal(plane->GetNormal());
						newContact->SetA(body);
						newContact->SetB(plane);
						contacts->push_back(newContact);
						collision = true;
					}
				}
			}
		}

		return collision;
		/*
		if(!collision)
		{
			return false;
		}
		else
		{
			//TODO:Backtrack to collision time or move object back by d along -n.
			contact->SetClosestPoint(furthest);
			contact->SetCollisionNormal(plane->GetNormal());
			contact->SetA(body);
			contact->SetB(plane);
			return true;
		}
		*/
	}

	bool CollisionDetector::TriangleAndPlane(const Triangle& body,
			const CollisionPlane& plane,
			ContactPtr contact) const
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
