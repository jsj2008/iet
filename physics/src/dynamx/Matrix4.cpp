#include "Matrix4.hpp"

namespace dynamx
{

	Matrix4::Matrix4()
	{
		int i;
		for(i=0;i<16;i++)
		{
			m_Elems[i] = (real)0.0;
		}
		//Create Identity Matrix
		m_Elems[0] = 1;
		m_Elems[5] = 1;
		m_Elems[10] = 1;
		m_Elems[15] = 1;
	}

	Matrix4::~Matrix4()
	{
	}

	void Matrix4::Multiply(const Vector3& vec, Vector3* result) const
	{
		Vector3 tempResult;
		tempResult.SetX((vec.GetX() * m_Elems[0]) +
						 (vec.GetY() * m_Elems[1]) +
						 (vec.GetZ() * m_Elems[2]) + m_Elems[3]);
		tempResult.SetY((vec.GetX() * m_Elems[4]) +
						 (vec.GetY() * m_Elems[5]) +
						 (vec.GetZ() * m_Elems[6]) + m_Elems[7]);
		tempResult.SetZ((vec.GetX() * m_Elems[8]) +
						 (vec.GetY() * m_Elems[9]) +
						 (vec.GetZ() * m_Elems[10]) + m_Elems[11]);
		(*result) = tempResult;
	}

	void Matrix4::Multiply(const Point3& vec, Point3* result) const
	{
		Point3 tempResult;
		tempResult.SetX((vec.GetX() * m_Elems[0]) +
						 (vec.GetY() * m_Elems[1]) +
						 (vec.GetZ() * m_Elems[2]) + m_Elems[3]);
		tempResult.SetY((vec.GetX() * m_Elems[4]) +
						 (vec.GetY() * m_Elems[5]) +
						 (vec.GetZ() * m_Elems[6]) + m_Elems[7]);
		tempResult.SetZ((vec.GetX() * m_Elems[8]) +
						 (vec.GetY() * m_Elems[9]) +
						 (vec.GetZ() * m_Elems[10]) + m_Elems[11]);
		(*result) = tempResult;
	}

	void Matrix4::Multiply(const Matrix4& other, Matrix4* result) const
	{
		Matrix4 tempResult;
		//Row by columns
		tempResult.SetElem(0,
							   (m_Elems[0] * other.GetElem(0)) +
							   (m_Elems[1] * other.GetElem(4)) +
							   (m_Elems[2] * other.GetElem(8)) +
							   (m_Elems[3] * other.GetElem(12)));
		tempResult.SetElem(1,
							   (m_Elems[0] * other.GetElem(1)) +
							   (m_Elems[1] * other.GetElem(5)) +
							   (m_Elems[2] * other.GetElem(9)) +
							   (m_Elems[3] * other.GetElem(12)));
		tempResult.SetElem(2,
							   (m_Elems[0] * other.GetElem(2)) +
							   (m_Elems[1] * other.GetElem(6)) +
							   (m_Elems[2] * other.GetElem(10)) +
							   (m_Elems[3] * other.GetElem(14)));
		tempResult.SetElem(3,
							   (m_Elems[0] * other.GetElem(3)) +
							   (m_Elems[1] * other.GetElem(7)) +
							   (m_Elems[2] * other.GetElem(11)) +
							   (m_Elems[3] * other.GetElem(15)));
		tempResult.SetElem(4,
							   (m_Elems[4] * other.GetElem(0)) +
							   (m_Elems[5] * other.GetElem(4)) +
							   (m_Elems[6] * other.GetElem(8)) +
							   (m_Elems[7] * other.GetElem(12)));
		tempResult.SetElem(5,
							   (m_Elems[4] * other.GetElem(1)) +
							   (m_Elems[5] * other.GetElem(5)) +
							   (m_Elems[6] * other.GetElem(9)) +
							   (m_Elems[7] * other.GetElem(13)));
		tempResult.SetElem(6,
							   (m_Elems[4] * other.GetElem(2)) +
							   (m_Elems[5] * other.GetElem(6)) +
							   (m_Elems[6] * other.GetElem(10)) +
							   (m_Elems[7] * other.GetElem(14)));
		tempResult.SetElem(7,
							   (m_Elems[4] * other.GetElem(3)) +
							   (m_Elems[5] * other.GetElem(7)) +
							   (m_Elems[6] * other.GetElem(11)) +
							   (m_Elems[7] * other.GetElem(15)));
		tempResult.SetElem(8,
							   (m_Elems[8] * other.GetElem(0)) +
							   (m_Elems[9] * other.GetElem(4)) +
							   (m_Elems[10] * other.GetElem(8)) +
							   (m_Elems[11] * other.GetElem(12)));
		tempResult.SetElem(9,
							   (m_Elems[8] * other.GetElem(1)) +
							   (m_Elems[9] * other.GetElem(5)) +
							   (m_Elems[10] * other.GetElem(9)) +
							   (m_Elems[11] * other.GetElem(13)));
		tempResult.SetElem(10,
							   (m_Elems[8] * other.GetElem(2)) +
							   (m_Elems[9] * other.GetElem(6)) +
							   (m_Elems[10] * other.GetElem(10)) +
							   (m_Elems[11] * other.GetElem(14)));
		tempResult.SetElem(11,
							   (m_Elems[8] * other.GetElem(3)) +
							   (m_Elems[9] * other.GetElem(7)) +
							   (m_Elems[10] * other.GetElem(11)) +
							   (m_Elems[11] * other.GetElem(15)));
		tempResult.SetElem(12,
							   (m_Elems[12] * other.GetElem(0)) +
							   (m_Elems[13] * other.GetElem(4)) +
							   (m_Elems[14] * other.GetElem(8)) +
							   (m_Elems[15] * other.GetElem(12)));
		tempResult.SetElem(13,
							   (m_Elems[12] * other.GetElem(1)) +
							   (m_Elems[13] * other.GetElem(5)) +
							   (m_Elems[14] * other.GetElem(9)) +
							   (m_Elems[15] * other.GetElem(13)));
		tempResult.SetElem(14,
							   (m_Elems[12] * other.GetElem(2)) +
							   (m_Elems[13] * other.GetElem(6)) +
							   (m_Elems[14] * other.GetElem(10)) +
							   (m_Elems[15] * other.GetElem(14)));
		tempResult.SetElem(15,
							   (m_Elems[12] * other.GetElem(3)) +
							   (m_Elems[13] * other.GetElem(7)) +
							   (m_Elems[14] * other.GetElem(11)) +
							   (m_Elems[15] * other.GetElem(15)));
		(*result) = tempResult;
	}

	real Matrix4::GetDeterminant() const
	{
		//Make copy so we don't overwrite our elements
		real a11 = GetElem(0);
		real a12 = GetElem(1);
		real a13 = GetElem(2);
		real a14 = GetElem(3);
		real a21 = GetElem(4);
		real a22 = GetElem(5);
		real a23 = GetElem(6);
		real a24 = GetElem(7);
		real a31 = GetElem(8);
		real a32 = GetElem(9);
		real a33 = GetElem(10);
		real a34 = GetElem(11);
		real a41 = GetElem(12);
		real a42 = GetElem(13);
		real a43 = GetElem(14);
		real a44 = GetElem(15);
		return ( ( a11 * a22 * a33 * a44 )
				+ ( a11 * a23 * a34 * a42 )
				+ ( a11 * a24 * a32 * a43 )

				+ ( a12 * a21 * a34 * a43 )
				+ ( a12 * a23 * a31 * a44 )
				+ ( a12 * a24 * a33 * a41 )

				+ ( a13 * a21 * a32 * a44 )
				+ ( a13 * a22 * a34 * a41 )
				+ ( a13 * a24 * a31 * a42 )

				+ ( a14 * a21 * a33 * a42 )
				+ ( a14 * a22 * a31 * a43 )
				+ ( a14 * a23 * a32 * a41 )

				- ( a11 * a22 * a34 * a43 )
				- ( a11 * a23 * a32 * a44 )
				- ( a11 * a24 * a33 * a42 )

				- ( a12 * a21 * a33 * a44 )
				- ( a12 * a23 * a34 * a41 )
				- ( a12 * a24 * a31 * a43 )

				- ( a13 * a21 * a34 * a42 )
				- ( a13 * a22 * a31 * a44 )
				- ( a13 * a24 * a32 * a41 )

				- ( a14 * a21 * a32 * a43 )
				- ( a14 * a22 * a33 * a41 )
				- ( a14 * a23 * a31 * a42 )
				);
	}

	void Matrix4::SetInverse(const Matrix4& other)
	{
		//Make copy so we don't overwrite our elements
		real a11 = other.GetElem(0);
		real a12 = other.GetElem(1);
		real a13 = other.GetElem(2);
		real a14 = other.GetElem(3);
		real a21 = other.GetElem(4);
		real a22 = other.GetElem(5);
		real a23 = other.GetElem(6);
		real a24 = other.GetElem(7);
		real a31 = other.GetElem(8);
		real a32 = other.GetElem(9);
		real a33 = other.GetElem(10);
		real a34 = other.GetElem(11);
		real a41 = other.GetElem(12);
		real a42 = other.GetElem(13);
		real a43 = other.GetElem(14);
		real a44 = other.GetElem(15);
		real det = other.GetDeterminant();

		if ((real)det == 0)
		{
			return;
		}
		real detInv = ((real)1.0) / det;

		m_Elems[0] = ( detInv * ( (a22*a33*a44)
									+ (a23*a34*a42)
									+ (a24*a32*a43)
									- (a22*a34*a43)
									- (a23*a32*a44)
									- (a24*a33*a42)
					));
		m_Elems[1] = ( detInv * ( (a12*a34*a43)
									+ (a13*a32*a44)
									+ (a14*a33*a42)
									- (a12*a33*a44)
									- (a13*a34*a42)
									- (a14*a32*a43)
					));
		m_Elems[2] = ( detInv * ( (a12*a23*a44)
									+ (a13*a24*a42)
									+ (a14*a22*a43)
									- (a12*a24*a43)
									- (a13*a22*a44)
									- (a14*a23*a42)
					));
		m_Elems[3] = ( detInv * ( (a12*a24*a33)
									+ (a13*a22*a34)
									+ (a14*a23*a32)
									- (a12*a23*a34)
									- (a13*a24*a32)
									- (a14*a22*a33)
					));
		m_Elems[4] = ( detInv * ( (a21*a34*a43)
									+ (a23*a31*a44)
									+ (a24*a33*a41)
									- (a21*a33*a44)
									- (a23*a34*a41)
									- (a24*a31*a43)
					));
		m_Elems[5] = ( detInv * ( (a11*a33*a44)
									+ (a13*a34*a41)
									+ (a14*a31*a43)
									- (a11*a34*a43)
									- (a13*a31*a44)
									- (a14*a33*a41)
					));
		m_Elems[6] = ( detInv * ( (a11*a24*a43)
									+ (a13*a21*a44)
									+ (a14*a23*a41)
									- (a11*a23*a44)
									- (a13*a24*a41)
									- (a14*a21*a43)
					));
		m_Elems[7] = ( detInv * ( (a11*a23*a34)
									+ (a13*a24*a31)
									+ (a14*a21*a33)
									- (a11*a24*a33)
									- (a13*a21*a34)
									- (a14*a23*a31)
					));
		m_Elems[8] = ( detInv * ( (a21*a32*a44)
									+ (a22*a34*a41)
									+ (a24*a31*a42)
									- (a21*a34*a42)
									- (a22*a31*a44)
									- (a24*a32*a41)
					));
		m_Elems[9] = ( detInv * ( (a11*a34*a42)
									+ (a12*a31*a44)
									+ (a14*a32*a41)
									- (a11*a32*a44)
									- (a12*a34*a41)
									- (a14*a31*a42)
					));
		m_Elems[10] = ( detInv * ( (a11*a22*a44)
									+ (a12*a24*a41)
									+ (a14*a21*a42)
									- (a11*a24*a42)
									- (a12*a21*a44)
									- (a14*a22*a41)
					));
		m_Elems[11] = ( detInv * ( (a11*a24*a32)
									+ (a12*a21*a34)
									+ (a14*a22*a31)
									- (a11*a22*a34)
									- (a12*a24*a31)
									- (a14*a21*a32)
					));
		m_Elems[12] = ( detInv * ( (a21*a33*a42)
									+ (a22*a31*a43)
									+ (a23*a32*a41)
									- (a21*a32*a43)
									- (a22*a33*a41)
									- (a23*a31*a42)
					));
		m_Elems[13] = ( detInv * ( (a11*a32*a43)
									+ (a12*a33*a41)
									+ (a13*a31*a42)
									- (a11*a33*a42)
									- (a12*a31*a43)
									- (a13*a32*a41)
					));
		m_Elems[14] = ( detInv * ( (a11*a23*a42)
									+ (a12*a21*a43)
									+ (a13*a22*a41)
									- (a11*a22*a43)
									- (a12*a23*a41)
									- (a13*a31*a42)
					));
		m_Elems[15] = ( detInv * ( (a11*a22*a33)
									+ (a12*a23*a31)
									+ (a13*a21*a32)
									- (a11*a23*a32)
									- (a12*a21*a33)
									- (a13*a22*a31)
					));
	}

	void Matrix4::GetInverse(Matrix4* result) const
	{
		result->SetInverse(*this);
	}

	void Matrix4::Invert()
	{
		SetInverse(*this);
	}

	void Matrix4::SetFromOrientationAndPos(const Quaternion& q, const Point3& pos)
	{
		m_Elems[0] = 1.0 - ((2.0*q.GetJ()*q.GetJ()) + (2.0*q.GetK()*q.GetK()));
		m_Elems[1] = (2.0*q.GetI()*q.GetJ()) + (2.0*q.GetK()*q.GetR());
		m_Elems[2] = (2.0*q.GetI()*q.GetK()) - (2.0*q.GetJ()*q.GetR());
		m_Elems[3] = pos.GetX();
		m_Elems[4] = (2.0*q.GetI()*q.GetJ()) - (2.0*q.GetK()*q.GetR());
		m_Elems[5] = 1.0 - ((2.0*q.GetI()*q.GetI()) + (2.0*q.GetK()*q.GetK()));
		m_Elems[6] = (2.0*q.GetJ()*q.GetK()) + (2.0*q.GetI()*q.GetR());
		m_Elems[7] = pos.GetY();
		m_Elems[8] = (2.0*q.GetI()*q.GetK()) + (2.0*q.GetJ()*q.GetR());
		m_Elems[9] = (2.0*q.GetJ()*q.GetK()) - (2.0*q.GetI()*q.GetR());
		m_Elems[10] = 1.0 - ((2.0*q.GetI()*q.GetI()) + (2.0*q.GetJ()*q.GetJ()));
		m_Elems[11] = pos.GetZ();
		m_Elems[12] = 0;
		m_Elems[13] = 0;
		m_Elems[14] = 0;
		m_Elems[15] = 1;
	}

	void Matrix4::SetOrientationAndPos(const Matrix3& m, const Vector3& pos)
	{
		m_Elems[0] = m.GetElem(0);
		m_Elems[1] = m.GetElem(1);
		m_Elems[2] = m.GetElem(2);
		m_Elems[3] = pos.GetX();
		m_Elems[4] = m.GetElem(3);
		m_Elems[5] = m.GetElem(4);
		m_Elems[6] = m.GetElem(5);
		m_Elems[7] = pos.GetY();
		m_Elems[8] = m.GetElem(6);
		m_Elems[9] = m.GetElem(7);
		m_Elems[10] = m.GetElem(8);
		m_Elems[11] = pos.GetZ();
		m_Elems[12] = 0;
		m_Elems[13] = 0;
		m_Elems[14] = 0;
		m_Elems[15] = 1;
	}

	void Matrix4::Transform(const Vector3& vec, Vector3* result) const
	{
		Multiply(vec,result);
	}

	void Matrix4::Transform(const Point3& vec, Point3* result) const
	{
		Multiply(vec,result);
	}

	void Matrix4::TransformInverse(const Vector3& vec, Vector3* result) const
	{
		Matrix4 tempResult;
		GetInverse(&tempResult);
		tempResult.Multiply(vec,result);
	}
	
	void Matrix4::TransformInverse(const Point3& vec, Point3* result) const
	{
		Matrix4 tempResult;
		GetInverse(&tempResult);
		tempResult.Multiply(vec,result);
	}

	void Matrix4::TransformDirection(const Vector3& vec, Vector3* result) const
	{
		Vector3 tempResult;
		tempResult.SetX((vec.GetX() * m_Elems[0]) +
						(vec.GetY() * m_Elems[1]) +
						(vec.GetZ() * m_Elems[2]));
		tempResult.SetY((vec.GetX() * m_Elems[4]) +
						(vec.GetY() * m_Elems[5]) +
						(vec.GetZ() * m_Elems[6]));
		tempResult.SetZ((vec.GetX() * m_Elems[8]) +
						(vec.GetY() * m_Elems[9]) +
						(vec.GetZ() * m_Elems[10]));
		(*result) = tempResult;
	}

	void Matrix4::TransformInverseDirection(const Vector3& vec, Vector3* result) const
	{
		Vector3 tempResult;
		tempResult.SetX((vec.GetX() * m_Elems[0]) +
						(vec.GetY() * m_Elems[4]) +
						(vec.GetZ() * m_Elems[8]));
		tempResult.SetY((vec.GetX() * m_Elems[1]) +
						(vec.GetY() * m_Elems[5]) +
						(vec.GetZ() * m_Elems[9]));
		tempResult.SetZ((vec.GetX() * m_Elems[2]) +
						(vec.GetY() * m_Elems[6]) +
						(vec.GetZ() * m_Elems[10]));
		(*result) = tempResult;
	}

	void Matrix4::FillColumnMajorArray(float array[16]) const
	{
		array[0] = (float)m_Elems[0];
		array[1] = (float)m_Elems[4];
		array[2] = (float)m_Elems[8];
		array[3] = (float)0;

		array[4] = (float)m_Elems[1];
		array[5] = (float)m_Elems[5];
		array[6] = (float)m_Elems[9];
		array[7] = (float)0;

		array[8] = (float)m_Elems[2];
		array[9] = (float)m_Elems[6];
		array[10] = (float)m_Elems[10];
		array[11] = (float)0;

		array[12] = (float)m_Elems[3];
		array[13] = (float)m_Elems[7];
		array[14] = (float)m_Elems[11];
		array[15] = (float)1;
	}

	void Matrix4::GetAxisVector(unsigned index, Vector3* result) const
	{
		result->SetX(m_Elems[index]);
		result->SetY(m_Elems[index+4]);
		result->SetZ(m_Elems[index+8]);
	}


	void Matrix4::GetOrientationMatrix(Matrix3* mat) const
	{
		int i;
		for(i=0; i < 9 ; i++)
		{
			mat->SetElem(i, m_Elems[i]);
		}
	}
}
