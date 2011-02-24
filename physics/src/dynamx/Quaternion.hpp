#ifndef  QUATERNION_H
#define  QUATERNION_H

#include <dynamx/Core.hpp>
#include <dynamx/Vector3.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: Quaternion
	 *  Description:
	 * =====================================================================================
	 */
	class Quaternion
	{
		public:
			Quaternion();

			Quaternion(real r
							,real i
							,real j
							,real k);

			virtual ~Quaternion();

			/*
			 * ===  FUNCTION  ======================================================================
			 *         Name:  Normalize
			 *  Description:  Makes this a unit length quaternion.
			 * =====================================================================================
			 */
			virtual void Normalize();

			/*
			 * ===  FUNCTION  ======================================================================
			 *         Name:  operator*=
			 *  Description:  Multiplies this quaternion by the one passed in.
			 * =====================================================================================
			 */
			virtual void operator*=(const Quaternion& other);

			/*
			 * ===  FUNCTION  ======================================================================
			 *         Name:  RotateByVector
			 *  Description:  Rotates the quaternion by the passed in vector.
			 * =====================================================================================
			 */
			virtual void RotateByVector(const Vector3& vec);


			/*
			 * ===  FUNCTION  ======================================================================
			 *         Name:  AddScaledVector
			 *  Description:  Adds the vector scaled to this quaternion.
			 * =====================================================================================
			 */
			virtual void AddScaledVector(const Vector3& vec, real scale);

			virtual Quaternion Multiply(const Vector3& vec) const;

			/*-----------------------------------------------------------------------------
			 *  Getters and Setters
			 *-----------------------------------------------------------------------------*/
			virtual real GetR() const { return m_R; }
			virtual real GetI() const { return m_I; }
			virtual real GetJ() const { return m_J; }
			virtual real GetK() const { return m_K; }
		protected:
			real m_R,m_I,m_J,m_K;
			
		private:
	};
}

#endif   // QUATERNION_H
