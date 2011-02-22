#ifndef  VECTOR3_H
#define  VECTOR3_H

#include <dynamx/Core.hpp>

namespace dynamx 
{
	class Point3;

	class Vector3
	{
		public:

			Vector3();

			Vector3(real x, real y, real z);

			Vector3(const Point3& point);

			virtual ~Vector3();

			Vector3 Add(const Vector3& other) const;

			void AddScaledVector(const Vector3& other, real scale);

			Vector3 Subtract(const Vector3& other) const;

			Vector3 Multiply(const real& scalar) const;

			real DotProduct(const Vector3& other) const;

			Vector3 CrossProduct(const Vector3& other) const;

			Vector3 ComponentProduct(const Vector3& other) const;

			real Magnitude() const;

			void Normalize();

			void Clear();

			void Set(real x, real y, real z) { m_X = x; m_Y = y ; m_Z = z; }

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

#endif   // VECTOR3_H
