#ifndef  POINT3_H
#define  POINT3_H

#include <dynamx/Core.hpp>

namespace dynamx 
{

	class Vector3;

	class Point3
	{
		public:

			Point3();

			Point3(real x, real y, real z);

			virtual ~Point3();

			Point3 Add(const Vector3&) const;

			void AddScaledVector(const Vector3& other, real scale);

			real CalculateDistance(const Point3&) const;

			void Set(real x, real y, real z) { m_X = x; m_Y = y ; m_Z = z; }

			Vector3 ToVector3() const;

			/*----------------------
			 *  Getters and Setters
			 *----------------------*/
			real GetX() const { return m_X; }

			void SetX(real val) { m_X = val; }

			real GetY() const { return m_Y; }

			void SetY(real val) { m_Y = val; }

			real GetZ() const { return m_Z; }

			void SetZ(real val) { m_Z = val; }

		protected:
			real m_X, m_Y, m_Z;

	};
}

#endif   // POINT3_H
