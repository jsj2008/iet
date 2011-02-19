#ifndef  TRIANGLE_H
#define  TRIANGLE_H

#include "SDL/SDL_opengl.h" 

#include <dynamx/Point3.hpp>
#include <dynamx/CollisionPlane.hpp>
#include <dynamx/Edge.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: Triangle
	 *  Description:
	 * =====================================================================================
	 */
	class Triangle
	{
		public:
			Triangle();

			virtual ~Triangle();

			Point3 GetPoint(int index) const
			{
				return m_Points[index];
			}
			
			void SetPoint(const Point3& val, int index)
			{
				m_Points[index] = val;
				m_LocalPoints[index] = val;
			}

			void ChooseColour(int i);

			void VDraw();

			void SetClosestFeature(int i, const Point3& point);

			Point3 GetClosestFeaturePos();

			void CreateEdges();

			Edge GetEdge(int index) const
			{
				return m_Edges[index];
			}

			void DrawEdge(int i);

			CollisionPlane GetPlane() const;

			void SetGlobalPos(const Point3& pos);

			void SetColliding(bool val)
			{
				m_Colliding = val;
			}

		protected:
			Point3 m_Points[3];
			Point3 m_LocalPoints[3];
			Edge m_Edges[3];

			GLUquadric* m_Quadric;
			GLuint m_NormalSphereList;

			int m_ClosestFeature;

			Point3 m_ClosestPoint;

			bool m_Colliding;

		private:
	};

}

#endif   // TRIANGLE_H
