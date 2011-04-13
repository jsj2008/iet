#include "VoronoiChecker.hpp"

namespace dynamx
{

	VoronoiChecker::VoronoiChecker()
	{
	}

	VoronoiChecker::~VoronoiChecker()
	{
	}

	bool VoronoiChecker::PointAndPoint(int vertexIndex, const Point3& point, const Triangle& triangle)
	{
		Vector3 a = triangle.GetPoint(vertexIndex).ToVector3();
		Vector3 otherPoints[2];
		otherPoints[0] = triangle.GetPoint((vertexIndex+1)%3).ToVector3();
		otherPoints[1] = triangle.GetPoint((vertexIndex+2)%3).ToVector3();
		Vector3 ax = point.ToVector3().Subtract(a);
		Vector3 ba = otherPoints[0].Subtract(a);
		real dot0 = ax.DotProduct(ba);

		Vector3 bc = otherPoints[1].Subtract(a);
		real dot1 = ax.DotProduct(bc);

		if((dot0 <= 0) && (dot1 <= 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool VoronoiChecker::PointAndEdge(int vertexIndex, const Point3& point, const Triangle& triangle)
	{
		int vertexIdx0 = vertexIndex;
		int vertexIdx1 = (vertexIndex+1) % 3;
		int vertexIdx2 = (vertexIndex+2) % 3;
		Vector3 x = point.ToVector3();
		Vector3 a = triangle.GetPoint(vertexIdx0).ToVector3();
		Vector3 b = triangle.GetPoint(vertexIdx1).ToVector3();
		Vector3 c = triangle.GetPoint(vertexIdx2).ToVector3();

		Vector3 bc = c.Subtract(b);
		Vector3 ba = a.Subtract(b);
		Vector3 bx = x.Subtract(b);
		real dot0 = (bc.CrossProduct(ba)).CrossProduct(ba).DotProduct(bx);

		Vector3 ax = x.Subtract(a);
		Vector3 ab = b.Subtract(a);
		real dot1 = ax.DotProduct(ab);

		real dot2 = bx.DotProduct(ba);
		if((dot0 >= 0) && (dot1 >= 0) && (dot2 >= 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
