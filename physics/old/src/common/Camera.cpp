#include "Camera.hpp"

Camera::Camera()
	:
		m_LeftStrafeRot(0),
		m_RightStrafeRot(0),
		m_ForwardStrafeRot(0),
		m_BackwardStrafeRot(0)
{
	m_Speed = 1.02;
}

Camera::~Camera()
{
}


void Camera::StrafeLeft()
{
	m_LeftStrafeRot = m_Rot.GetY() * PI_OVER_180;
	m_Force = m_Force.Add(dynamx::Vector3( - (cos(m_LeftStrafeRot) * m_Speed)
			, 0
			, - (sin(m_LeftStrafeRot) * m_Speed)
			));
}

void Camera::UnStrafeLeft()
{
	m_Force = m_Force.Subtract(dynamx::Vector3( - (cos(m_LeftStrafeRot) * m_Speed)
			, 0
			, - (sin(m_LeftStrafeRot) * m_Speed)
			));
}

void Camera::StrafeRight()
{
	m_RightStrafeRot = m_Rot.GetY() * PI_OVER_180;
	m_Force = m_Force.Add(dynamx::Vector3( (cos(m_RightStrafeRot) * m_Speed)
			, 0
			, (sin(m_RightStrafeRot) * m_Speed)
			));
}

void Camera::UnStrafeRight()
{
	m_Force = m_Force.Subtract(dynamx::Vector3( (cos(m_RightStrafeRot) * m_Speed)
			, 0
			, (sin(m_RightStrafeRot) * m_Speed)
			));
}

void Camera::StrafeForward()
{
	m_ForwardStrafeRot = m_Rot.GetY() * PI_OVER_180;
	m_Force = m_Force.Add(dynamx::Vector3( (sin(m_ForwardStrafeRot) * m_Speed)
			, 0
			, (-cos(m_RightStrafeRot) * m_Speed)
			));
}

void Camera::UnStrafeForward()
{
	m_Force = m_Force.Subtract(dynamx::Vector3( (sin(m_ForwardStrafeRot) * m_Speed)
			, 0
			, (-cos(m_RightStrafeRot) * m_Speed)
			));
}

void Camera::StrafeBackward()
{
	m_BackwardStrafeRot = m_Rot.GetY() * PI_OVER_180;
	m_Force = m_Force.Add(dynamx::Vector3( (-sin(m_BackwardStrafeRot) * m_Speed)
			, 0
			, (cos(m_RightStrafeRot) * m_Speed)
			));
}

void Camera::UnStrafeBackward()
{
	m_Force = m_Force.Subtract(dynamx::Vector3( (-sin(m_BackwardStrafeRot) * m_Speed)
			, 0
			, (cos(m_RightStrafeRot) * m_Speed)
			));
}

void Camera::UpdatePosAndRot()
{
	m_Pos = m_Pos.Add(m_Force);
}
