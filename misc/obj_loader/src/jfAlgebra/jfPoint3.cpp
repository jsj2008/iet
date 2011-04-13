#include "jfPoint3.hpp"

jfPoint3::jfPoint3()
	:
		m_X(0),
		m_Y(0),
		m_Z(0)
{
}

jfPoint3::jfPoint3(jfReal x, jfReal y, jfReal z)
	:
		m_X(x), m_Y(y), m_Z(z)
{
}

jfPoint3::~jfPoint3()
{
}

jfPoint3 jfPoint3::add(const jfVector3& vec) const
{
	jfPoint3 result;
	result.setX(m_X + vec.getX());
	result.setY(m_Y + vec.getY());
	result.setZ(m_Z + vec.getZ());
	return result;
}

void jfPoint3::addScaledjfVector(const jfVector3& other, jfReal scale)
{
	m_X += other.getX() * scale;
	m_Y += other.getY() * scale;
	m_Z += other.getZ() * scale;
}

jfReal jfPoint3::calculateDistance(const jfPoint3& other) const
{
	return jfRealSqrt(((other.getX() - m_X) * (other.getX() - m_X)) +
			((other.getY() - m_Y) * (other.getY() - m_Y)) +
			((other.getZ() - m_Z) * (other.getZ() - m_Z)));
}

jfVector3 jfPoint3::toVector3() const
{
	return jfVector3(m_X, m_Y, m_Z);
}
