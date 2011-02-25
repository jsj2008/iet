#include "Vector3.hpp"

#include <dynamx/Point3.hpp>
#include <assert.h>

namespace dynamx
{
	Vector3::Vector3()
		:
			m_X(0), m_Y(0), m_Z(0)
	{
	}

	Vector3::Vector3(const Point3& point)
		:
			m_X(point.GetX()), 
			m_Y(point.GetY()), 
			m_Z(point.GetZ())
	{
	}

	Vector3::Vector3(real x, real y, real z)
		:
			m_X(x), m_Y(y), m_Z(z)
	{
	}

	Vector3::~Vector3()
	{
	}

	Vector3 Vector3::Add(const Vector3& other) const
	{
		Vector3 result;
		result.SetX(m_X + other.GetX());
		result.SetY(m_Y + other.GetY());
		result.SetZ(m_Z + other.GetZ());
		return result;
	}

	Vector3 Vector3::Add(const real& scalar) const
	{
		Vector3 result;
		result.SetX(m_X + scalar);
		result.SetY(m_Y + scalar);
		result.SetZ(m_Z + scalar);
		return result;
	}

	void Vector3::AddScaledVector(const Vector3& other, real scale)
	{
		m_X += other.GetX() * scale;
		m_Y += other.GetY() * scale;
		m_Z += other.GetZ() * scale;
	}

	Vector3 Vector3::Subtract(const Vector3& other) const
	{
		Vector3 result;
		result.SetX(m_X - other.GetX());
		result.SetY(m_Y - other.GetY());
		result.SetZ(m_Z - other.GetZ());
		return result;
	}

	Vector3 Vector3::Multiply(const real& scaler) const
	{
		Vector3 result;
		result.SetX(m_X * scaler);
		result.SetY(m_Y * scaler);
		result.SetZ(m_Z * scaler);
		return result;
	}

	real Vector3::DotProduct(const Vector3& other) const
	{
		real result = 0.0f;
		result += (m_X * other.GetX());
		result += (m_Y * other.GetY());
		result += (m_Z * other.GetZ());
		return result;
	}

	Vector3 Vector3::ComponentProduct(const Vector3& other) const
	{
		Vector3 result;
		result.SetX(m_X * other.GetX());
		result.SetY(m_Y * other.GetY());
		result.SetZ(m_Z * other.GetZ());
		return result;
	}

	Vector3 Vector3::CrossProduct(const Vector3& other) const
	{
		Vector3 result;
		result.SetX( (m_Y * other.GetZ()) - (m_Z * other.GetY()) );
		result.SetY( (m_Z * other.GetX()) - (m_X * other.GetZ()) );
		result.SetZ( (m_X * other.GetY()) - (m_Y * other.GetX()) );
		return result;
	}

	void Vector3::Clear()
	{
		m_X = 0.0f;
		m_Y = 0.0f;
		m_Z = 0.0f;
	}

	real Vector3::Magnitude() const
	{
		return real_sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
	}

	void Vector3::Normalize()
	{
		real mag = Magnitude();
		if(mag>0)
		{
			real magInv = 1/mag;
			m_X *= magInv;
			m_Y *= magInv;
			m_Z *= magInv;
		}
		else
		{
			assert("Mag is less than 0");
		}
	}
}
