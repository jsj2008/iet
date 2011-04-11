#include "jfVector3.hpp"

#include <jfAlgebra/jfPoint3.hpp>

jfVector3::jfVector3()
	:
		m_X(0), m_Y(0), m_Z(0)
{
}

jfVector3::jfVector3(const jfPoint3& point)
	:
		m_X(point.getX()),
		m_Y(point.getY()),
		m_Z(point.getZ())
{
}

jfVector3::jfVector3(jfReal x, jfReal y, jfReal z)
	:
		m_X(x), m_Y(y), m_Z(z)
{
}

jfVector3::~jfVector3()
{
}

jfVector3 jfVector3::add(const jfVector3& other) const
{
	jfVector3 result;
	result.setX(m_X + other.getX());
	result.setY(m_Y + other.getY());
	result.setZ(m_Z + other.getZ());
	return result;
}

void jfVector3::addScaledVector(const jfVector3& other, jfReal scale)
{
	m_X += other.getX() * scale;
	m_Y += other.getY() * scale;
	m_Z += other.getZ() * scale;
}

jfVector3 jfVector3::subtract(const jfVector3& other) const
{
	jfVector3 result;
	result.setX(m_X - other.getX());
	result.setY(m_Y - other.getY());
	result.setZ(m_Z - other.getZ());
	return result;
}

jfVector3 jfVector3::multiply(const jfReal& scaler) const
{
	jfVector3 result;
	result.setX(m_X * scaler);
	result.setY(m_Y * scaler);
	result.setZ(m_Z * scaler);
	return result;
}

jfReal jfVector3::dotProduct(const jfVector3& other) const
{
	jfReal result = 0.0f;
	result += (m_X * other.getX());
	result += (m_Y * other.getY());
	result += (m_Z * other.getZ());
	return result;
}

jfVector3 jfVector3::componentProduct(const jfVector3& other) const
{
	jfVector3 result;
	result.setX(m_X * other.getX());
	result.setY(m_Y * other.getY());
	result.setZ(m_Z * other.getZ());
	return result;
}

jfVector3 jfVector3::crossProduct(const jfVector3& other) const
{
	jfVector3 result;
	result.setX( (m_Y * other.getZ()) - (m_Z * other.getY()) );
	result.setY( (m_Z * other.getX()) - (m_X * other.getZ()) );
	result.setZ( (m_X * other.getY()) - (m_Y * other.getX()) );
	return result;
}

void jfVector3::clear()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

jfReal jfVector3::magnitude() const
{
	return jfRealSqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
}

void jfVector3::normalize()
{
	jfReal mag = magnitude();
	if(mag>0)
	{
		jfReal magInv = 1/mag;
		m_X *= magInv;
		m_Y *= magInv;
		m_Z *= magInv;
	}
	else
	{
		assert("Mag is less than 0");
	}
}
