#include "Point3.hpp"

#include <dynamx/Vector3.hpp>

namespace dynamx
{
	Point3::Point3()
		:
			m_X(0),
			m_Y(0),
			m_Z(0)
	{
	}

	Point3::Point3(real x, real y, real z)
		:
			m_X(x), m_Y(y), m_Z(z)
	{
	}

	Point3::~Point3()
	{
	}

	Point3 Point3::Add(const Vector3& vec) const
	{
		Point3 result;
		result.SetX(m_X + vec.GetX());
		result.SetY(m_Y + vec.GetY());
		result.SetZ(m_Z + vec.GetZ());
		return result;
	}

	void Point3::AddScaledVector(const Vector3& other, real scale)
	{
		m_X += other.GetX() * scale;
		m_Y += other.GetY() * scale;
		m_Z += other.GetZ() * scale;
	}

	real Point3::CalculateDistance(const Point3& other) const
	{
		return real_sqrt(((other.GetX() - m_X) * (other.GetX() - m_X)) + 
				((other.GetY() - m_Y) * (other.GetY() - m_Y)) +
				((other.GetZ() - m_Z) * (other.GetZ() - m_Z)));
	}

	Vector3 Point3::ToVector3() const
	{
		return Vector3(m_X, m_Y, m_Z);
	}
}
