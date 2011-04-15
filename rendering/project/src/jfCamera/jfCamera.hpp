#ifndef  CAMERA_H
#define  CAMERA_H

#include <jfAlgebra/jfVector3.hpp>
#include <jfMath/jfMath.hpp>

/*
 * =====================================================================================
 *        Class: jfCamera
 *  Description:
 * =====================================================================================
 */
class jfCamera
{
	public:
		jfCamera();

		virtual ~jfCamera();

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
		 *  getters and setters
		 *-----------------------------------------------------------------------------*/
		jfVector3 getPos() const { return m_Pos; }

		void setPos(jfVector3 val) { m_Pos = val; }

		jfVector3 getRot() const { return m_Rot; }

		void setRot(jfVector3 val) { m_Rot = val; }
		
	protected:
		jfVector3 m_Pos;
		jfVector3 m_Rot;
		jfVector3 m_Force;

		float m_Speed;
		float m_LeftStrafeRot;
		float m_RightStrafeRot;
		float m_ForwardStrafeRot;
		float m_BackwardStrafeRot;
		
	private:
};


#endif   // CAMERA_H
