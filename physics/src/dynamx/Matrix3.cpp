#include "Matrix3.hpp"

namespace dynamx
{
	Matrix3::Matrix3()
	{
		int i;
		for(i=0;i<9;i++)
		{
			m_Elems[i] = (real)0.0;
		}
		//Create Identity Matrix
		m_Elems[0] = 1;
		m_Elems[4] = 1;
		m_Elems[8] = 1;
	}

	Matrix3::Matrix3(real e0, real e1, real e2,
			real e3, real e4, real e5,
			real e6, real e7, real e8)
	{
		m_Elems[0] = e0;
		m_Elems[1] = e1;
		m_Elems[2] = e2;
		m_Elems[3] = e3;
		m_Elems[4] = e4;
		m_Elems[5] = e5;
		m_Elems[6] = e6;
		m_Elems[7] = e7;
		m_Elems[8] = e8;
	}

	Matrix3::~Matrix3()
	{
	}

	void Matrix3::Multiply(const Matrix3& other, Matrix3* result) const
	{
		Matrix3 tempResult;
		tempResult.SetElem(0, (m_Elems[0] * other.GetElem(0)) +
							   (m_Elems[1] * other.GetElem(3)) +
							   (m_Elems[2] * other.GetElem(6)));
		tempResult.SetElem(1, (m_Elems[0] * other.GetElem(1)) +
							   (m_Elems[1] * other.GetElem(4)) +
							   (m_Elems[2] * other.GetElem(7)));
		tempResult.SetElem(2, (m_Elems[0] * other.GetElem(2)) +
							   (m_Elems[1] * other.GetElem(5)) +
							   (m_Elems[2] * other.GetElem(8)));
		tempResult.SetElem(3, (m_Elems[3] * other.GetElem(0)) +
							   (m_Elems[4] * other.GetElem(3)) +
							   (m_Elems[5] * other.GetElem(6)));
		tempResult.SetElem(4, (m_Elems[3] * other.GetElem(1)) +
							   (m_Elems[4] * other.GetElem(4)) +
							   (m_Elems[5] * other.GetElem(7)));
		tempResult.SetElem(5, (m_Elems[3] * other.GetElem(2)) +
							   (m_Elems[4] * other.GetElem(5)) +
							   (m_Elems[5] * other.GetElem(8)));
		tempResult.SetElem(6, (m_Elems[6] * other.GetElem(0)) +
							   (m_Elems[7] * other.GetElem(3)) +
							   (m_Elems[8] * other.GetElem(6)));
		tempResult.SetElem(7, (m_Elems[6] * other.GetElem(1)) +
							   (m_Elems[7] * other.GetElem(4)) +
							   (m_Elems[8] * other.GetElem(7)));
		tempResult.SetElem(8, (m_Elems[6] * other.GetElem(2)) +
							   (m_Elems[7] * other.GetElem(5)) +
							   (m_Elems[8] * other.GetElem(8)));
		(*result) = tempResult;
	}

	void Matrix3::Multiply(const Vector3& other, Vector3* result) const
	{
		//@REF: Transform the matrix by the vector
		result->SetX((other.GetX()*m_Elems[0]) +
						(other.GetY()*m_Elems[1]) +
						(other.GetZ()*m_Elems[2]));
		result->SetY((other.GetX()*m_Elems[3]) +
						(other.GetY()*m_Elems[4]) +
						(other.GetZ()*m_Elems[5]));
		result->SetZ((other.GetX()*m_Elems[6]) +
						(other.GetY()*m_Elems[7]) +
						(other.GetZ()*m_Elems[8]));
	}

	Vector3 Matrix3::Multiply(const Vector3& other) const
	{
		Vector3 result;
		//@REF: Transform the matrix by the vector
		result.SetX((other.GetX()*m_Elems[0]) +
						(other.GetY()*m_Elems[1]) +
						(other.GetZ()*m_Elems[2]));
		result.SetY((other.GetX()*m_Elems[3]) +
						(other.GetY()*m_Elems[4]) +
						(other.GetZ()*m_Elems[5]));
		result.SetZ((other.GetX()*m_Elems[6]) +
						(other.GetY()*m_Elems[7]) +
						(other.GetZ()*m_Elems[8]));
		return result;
	}

	void Matrix3::Add(const Matrix3& other, Matrix3* result) const
	{
		result->SetElem(0, m_Elems[0] + other.GetElem(0));
		result->SetElem(1, m_Elems[1] + other.GetElem(1));
		result->SetElem(2, m_Elems[2] + other.GetElem(2));
		result->SetElem(3, m_Elems[3] + other.GetElem(3));
		result->SetElem(4, m_Elems[4] + other.GetElem(4));
		result->SetElem(5, m_Elems[5] + other.GetElem(5));
		result->SetElem(6, m_Elems[6] + other.GetElem(6));
		result->SetElem(7, m_Elems[7] + other.GetElem(7));
		result->SetElem(8, m_Elems[8] + other.GetElem(8));
	}

	void Matrix3::CreateRotationMatrixAboutXAxis(real degrees, Matrix3* result)
	{
		result->SetElem(4, cos(dtr(degrees)));
		result->SetElem(5, -sin(dtr(degrees)));
		result->SetElem(7, sin(dtr(degrees)));
		result->SetElem(8, cos(dtr(degrees)));
	}

	void Matrix3::CreateRotationMatrixAboutYAxis(real degrees, Matrix3* result)
	{
		result->SetElem(0, cos(dtr(degrees)));
		result->SetElem(2, sin(dtr(degrees)));
		result->SetElem(6, -sin(dtr(degrees)));
		result->SetElem(8, cos(dtr(degrees)));
	}

	void Matrix3::CreateRotationMatrixAboutZAxis(real degrees, Matrix3* result)
	{
		result->SetElem(0, cos(dtr(degrees)));
		result->SetElem(2, sin(dtr(degrees)));
		result->SetElem(6, -sin(dtr(degrees)));
		result->SetElem(8, cos(dtr(degrees)));
	}

	void Matrix3::SetTranspose(const Matrix3& other)
	{
		real a11 = other.GetElem(0);
		real a12 = other.GetElem(1);
		real a13 = other.GetElem(2);
		real a21 = other.GetElem(3);
		real a22 = other.GetElem(4);
		real a23 = other.GetElem(5);
		real a31 = other.GetElem(6);
		real a32 = other.GetElem(7);
		real a33 = other.GetElem(8);

		m_Elems[0] = a11;
		m_Elems[1] = a21;
		m_Elems[2] = a31;
		m_Elems[3] = a12;
		m_Elems[4] = a22;
		m_Elems[5] = a32;
		m_Elems[6] = a13;
		m_Elems[7] = a23;
		m_Elems[8] = a33;
	}

	void Matrix3::GetTranspose(Matrix3* result) const
	{
		result->SetTranspose(*this);
	}


	void Matrix3::SetBlockInertiaTensor(const Vector3& halfSizes, real mass)
	{
		Vector3 squares = halfSizes.ComponentProduct(halfSizes);
		SetInertiaTensorCoeffs(0.3f*mass*(squares.GetY() + squares.GetZ()),
				0.3f*mass*(squares.GetX() + squares.GetZ()),
				0.3f*mass*(squares.GetX() + squares.GetY()));
	}

	void Matrix3::SetInertiaTensorCoeffs(real ix, real iy, real iz, real ixy, real ixz, real iyz)
	{
		m_Elems[0] = ix;
		m_Elems[1] = -ixy;
		m_Elems[2] = -ixz;
		m_Elems[3] = -ixy;
		m_Elems[4] = iy;
		m_Elems[5] = -iyz;
		m_Elems[6] = -ixz;
		m_Elems[7] = -iyz;
		m_Elems[8] = iz;
	}

	void Matrix3::SetInverse(const Matrix3& other)
	{
		//@REF: Eberly p.636 (A.31)
		//@REF: Millington (p.173)
		real a11 = other.GetElem(0);
		real a12 = other.GetElem(1);
		real a13 = other.GetElem(2);
		real a21 = other.GetElem(3);
		real a22 = other.GetElem(4);
		real a23 = other.GetElem(5);
		real a31 = other.GetElem(6);
		real a32 = other.GetElem(7);
		real a33 = other.GetElem(8);

		real det = ( (a11*a22*a33) + (a12*a23*a31) + (a13*a21*a32) - (a13*a22*a31) - (a12*a21*a33) - (a11*a23*a32) );
		if (det == real(0.0))
		{
			//undefined division
			return;
		}
		real detInv = real(1.0)/det;

		m_Elems[0] = (detInv * ((a22*a33) - (a23*a32)));
		m_Elems[1] = (detInv * ((a13*a32) - (a12*a33)));
		m_Elems[2] = (detInv * ((a12*a23) - (a13*a22)));
		m_Elems[3] = (detInv * ((a23*a31) - (a21*a33)));
		m_Elems[4] = (detInv * ((a11*a33) - (a13*a31)));
		m_Elems[5] = (detInv * ((a13*a21) - (a11*a23)));
		m_Elems[6] = (detInv * ((a21*a32) - (a22*a31)));
		m_Elems[7] = (detInv * ((a12*a31) - (a11*a32)));
		m_Elems[8] = (detInv * ((a11*a22) - (a12*a21)));
	}

	void Matrix3::GetInverse(Matrix3* result) const
	{
		result->SetInverse(*this);
	}

	Vector3 Matrix3::GetColumnVector(int i) const
	{
		Vector3 result;
		result.SetX(m_Elems[i]);
		result.SetY(m_Elems[i + 3]);
		result.SetZ(m_Elems[i + 6]);
		return result;
	}

	void Matrix3::ReOrthorgonalize()
	{
		Vector3 r1_dash = GetColumnVector(0);
		//TODO
	}
}
