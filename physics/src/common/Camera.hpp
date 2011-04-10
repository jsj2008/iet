#ifndef  CAMERA_H
#define  CAMERA_H

#include <dynamx/Vector3.hpp>

#include <common/Math.hpp>

/*
 * =====================================================================================
 *        Class: Camera
 *  Description:
 * =====================================================================================
 */
class Camera
{
	public:
		Camera();

		virtual ~Camera();

		void StrafeLeft();
		void UnStrafeLeft();

		void StrafeRight();
		void UnStrafeRight();

		void StrafeForward();
		void UnStrafeForward();

		void StrafeBackward();
		void UnStrafeBackward();

		void UpdatePosAndRot();

		/*-----------------------------------------------------------------------------
		 *  Getters and setters
		 *-----------------------------------------------------------------------------*/
		dynamx::Vector3 GetPos() const { return m_Pos; }

		void SetPos(dynamx::Vector3 val) { m_Pos = val; }

		dynamx::Vector3 GetRot() const { return m_Rot; }

		void SetRot(dynamx::Vector3 val) { m_Rot = val; }
		
	protected:
		dynamx::Vector3 m_Pos;
		dynamx::Vector3 m_Rot;
		dynamx::Vector3 m_Force;

		float m_Speed;
		float m_LeftStrafeRot;
		float m_RightStrafeRot;
		float m_ForwardStrafeRot;
		float m_BackwardStrafeRot;
		
	private:
};


#endif   // CAMERA_H
