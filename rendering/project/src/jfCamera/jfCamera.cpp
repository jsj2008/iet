#include "jfCamera.hpp"

jfCamera::jfCamera()
	:
		m_LeftStrafeRot(0),
		m_RightStrafeRot(0),
		m_ForwardStrafeRot(0),
		m_BackwardStrafeRot(0)
{
	m_Speed = 1.02;
}

jfCamera::~jfCamera()
{
}


void jfCamera::StrafeLeft()
{
	m_LeftStrafeRot = m_Rot.getY() * PI_OVER_180;
	m_Force = m_Force.add(jfVector3( - (cos(m_LeftStrafeRot) * m_Speed)
			, 0
			, - (sin(m_LeftStrafeRot) * m_Speed)
			));
}

void jfCamera::UnStrafeLeft()
{
	m_Force = m_Force.subtract(jfVector3( - (cos(m_LeftStrafeRot) * m_Speed)
			, 0
			, - (sin(m_LeftStrafeRot) * m_Speed)
			));
}

void jfCamera::StrafeRight()
{
	m_RightStrafeRot = m_Rot.getY() * PI_OVER_180;
	m_Force = m_Force.add(jfVector3( (cos(m_RightStrafeRot) * m_Speed)
			, 0
			, (sin(m_RightStrafeRot) * m_Speed)
			));
}

void jfCamera::UnStrafeRight()
{
	m_Force = m_Force.subtract(jfVector3( (cos(m_RightStrafeRot) * m_Speed)
			, 0
			, (sin(m_RightStrafeRot) * m_Speed)
			));
}

void jfCamera::StrafeForward()
{
	m_ForwardStrafeRot = m_Rot.getY() * PI_OVER_180;
	m_Force = m_Force.add(jfVector3( (sin(m_ForwardStrafeRot) * m_Speed)
			, 0
			, (-cos(m_RightStrafeRot) * m_Speed)
			));
}

void jfCamera::UnStrafeForward()
{
	m_Force = m_Force.subtract(jfVector3( (sin(m_ForwardStrafeRot) * m_Speed)
			, 0
			, (-cos(m_RightStrafeRot) * m_Speed)
			));
}

void jfCamera::StrafeBackward()
{
	m_BackwardStrafeRot = m_Rot.getY() * PI_OVER_180;
	m_Force = m_Force.add(jfVector3( (-sin(m_BackwardStrafeRot) * m_Speed)
			, 0
			, (cos(m_RightStrafeRot) * m_Speed)
			));
}

void jfCamera::UnStrafeBackward()
{
	m_Force = m_Force.subtract(jfVector3( (-sin(m_BackwardStrafeRot) * m_Speed)
			, 0
			, (cos(m_RightStrafeRot) * m_Speed)
			));
}

void jfCamera::UpdatePosAndRot()
{
	m_Pos = m_Pos.add(m_Force);
}
