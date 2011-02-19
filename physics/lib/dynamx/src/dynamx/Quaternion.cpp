#include "Quaternion.hpp"

namespace dynamx
{

	Quaternion::Quaternion()
		:
			m_R(1),
			m_I(0),
			m_J(0),
			m_K(0)
	{
	}

	Quaternion::Quaternion(real r
			,real i
			,real j
			,real k)
		:
			m_R(r),
			m_I(i),
			m_J(j),
			m_K(k)
	{
	}

	Quaternion::~Quaternion()
	{
	}

	void Quaternion::Normalize()
	{
		real d = (m_R*m_R) + (m_I*m_I) + (m_J*m_J) + (m_K*m_K);

		//Zero length quaternion, so give no-rotation quaternion.
		if(d==0)
		{
			m_R = 1;
			return;
		}

		d = ((real)1.0/real_sqrt(d));
		m_R *= d;
		m_I *= d;
		m_J *= d;
		m_K *= d;
	}

	void Quaternion::operator*=(const Quaternion& other)
	{
		real oldR = m_R;
		real oldI = m_I;
		real oldJ = m_J;
		real oldK = m_K;
		m_R = (oldR*other.GetR()) - (oldI*other.GetI()) - (oldJ*other.GetJ()) - (oldK*other.GetK());
		m_I = (oldR*other.GetI()) + (oldI*other.GetR()) + (oldJ*other.GetK()) - (oldK*other.GetJ());
		m_J = (oldR*other.GetJ()) + (oldJ*other.GetR()) + (oldK*other.GetI()) - (oldI*other.GetK());
		m_K = (oldR*other.GetK()) + (oldK*other.GetR()) + (oldI*other.GetJ()) - (oldJ*other.GetI());
	}

	void Quaternion::RotateByVector(const Vector3& vec)
	{
		Quaternion q(0, vec.GetX(), vec.GetY(), vec.GetZ());
		(*this) *= q;
	}

	void Quaternion::AddScaledVector(const Vector3& vec, real scale)
	{
		Quaternion q(0,
							vec.GetX() * scale,
							vec.GetY() * scale,
							vec.GetZ() * scale);
		q *= *this;
		m_R += q.GetR() * ((real)0.5);
		m_I += q.GetI() * ((real)0.5);
		m_J += q.GetJ() * ((real)0.5);
		m_K += q.GetK() * ((real)0.5);
	}
}
