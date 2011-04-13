#ifndef  VORONOICHECKER_H
#define  VORONOICHECKER_H

#include <dynamx/Triangle.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/Vector3.hpp>

namespace dynamx
{

	/*
	 * =====================================================================================
	 *        Class: VoronoiChecker
	 *  Description:
	 * =====================================================================================
	 */
	class VoronoiChecker
	{
		public:
			VoronoiChecker();

			virtual ~VoronoiChecker();

			bool PointAndPoint(int vertexIndex, const Point3& point, const Triangle& triangle);

			bool PointAndEdge(int vertexIndex, const Point3& point, const Triangle& triangle);
			
		protected:
		private:
	};

}

#endif   // VORONOICHECKER_H
