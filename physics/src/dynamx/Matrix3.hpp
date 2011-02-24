#ifndef  MATRIX3_H
#define  MATRIX3_H

#include <dynamx/Core.hpp>
#include <dynamx/Vector3.hpp>

namespace dynamx
{

	/*
	 * =====================================================================================
	 *        Class: Matrix3
	 *  Description:
	 * =====================================================================================
	 */
	class Matrix3
	{
		public:
			Matrix3();

			Matrix3(real e0, real e1, real e2,
					real e3, real e4, real e5,
					real e6, real e7, real e8);

			virtual ~Matrix3();

			void Multiply(const Matrix3& other, Matrix3* result) const;

			void Multiply(const Vector3& other, Vector3* result) const;

			Vector3 Multiply(const Vector3& other) const;

			void Add(const Matrix3& other, Matrix3* result) const;

			void SetInverse(const Matrix3& other);

			void GetInverse(Matrix3* result) const;

			void SetTranspose(const Matrix3& other);

			void GetTranspose(Matrix3* result) const;

			//For inertia tensor
			void SetBlockInertiaTensor(const Vector3& halfSizes, real mass);
			void SetInertiaTensorCoeffs(real ix, real iy, real iz, real ixy=0, real ixz=0, real iyz=0);

			//For matrix rotations
			void CreateRotationMatrixAboutXAxis(real degrees, Matrix3* result);
			void CreateRotationMatrixAboutYAxis(real degrees, Matrix3* result);
			void CreateRotationMatrixAboutZAxis(real degrees, Matrix3* result);

			Vector3 GetColumnVector(int i) const;

			//Orthogonalizing avoids drift
			void ReOrthorgonalize();

			/*-----------------------------------------------------------------------------
			 *  Getters and Setters
			 *-----------------------------------------------------------------------------*/
			virtual real GetElem(int index) const { return m_Elems[index]; }

			virtual void SetElem(int index, real val) { m_Elems[index] = val; }

		protected:
			real m_Elems[9];
		private:
	};

}

#endif   // MATRIX3_H
