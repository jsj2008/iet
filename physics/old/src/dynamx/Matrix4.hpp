#ifndef  MATRIX4_H
#define  MATRIX4_H

#include <dynamx/Core.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/Vector3.hpp>
#include <dynamx/Matrix3.hpp>
#include <dynamx/Quaternion.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: Matrix4
	 *  Description:
	 * =====================================================================================
	 */
	class Matrix4
	{
		public:
			Matrix4();

			virtual ~Matrix4();

			virtual void Multiply(const Vector3& vec, Vector3* result) const;

			virtual void Multiply(const Point3& vec, Point3* result) const;

			virtual void Multiply(const Matrix4& other, Matrix4* result) const;

			virtual real GetDeterminant() const;

			virtual void SetInverse(const Matrix4& other);

			virtual void GetInverse(Matrix4* result) const;

			virtual void Invert();

			virtual void SetFromOrientationAndPos(const Quaternion& q, const Point3& pos);

			virtual void SetOrientationAndPos(const Matrix3& m, const Vector3& pos);

			virtual void Transform(const Vector3& vec, Vector3* result) const;

			virtual void Transform(const Point3& vec, Point3* result) const;

			virtual void TransformInverse(const Vector3& vec, Vector3* result) const;

			virtual void TransformInverse(const Point3& vec, Point3* result) const;

			virtual void TransformDirection(const Vector3& vec, Vector3* result) const;

			virtual void TransformInverseDirection(const Vector3& vec, Vector3* result) const;

			virtual void FillColumnMajorArray(float array[16]) const;

			virtual void GetAxisVector(unsigned index, Vector3* result) const;

			/*-----------------------------------------------------------------------------
			 *  Getters and Setters
			 *-----------------------------------------------------------------------------*/
			virtual real GetElem(int index) const { return m_Elems[index]; }

			virtual void SetElem(int index, real val) { m_Elems[index] = val; }

			virtual void GetOrientationMatrix(Matrix3* mat) const;

		protected:
			real m_Elems[16];
		private:
	};

}

#endif   // MATRIX4_H
