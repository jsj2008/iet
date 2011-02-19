#include <UnitTest++.h>

#include <TestCommon.hpp>

class Vector3Fixture
{
	public:
		Vector3Fixture() 
		{ 
		}

		~Vector3Fixture() 
		{
		} 

		dynamx::Vector3 vectorA;
		dynamx::Vector3 vectorB;
};

SUITE(Vector3TestSuite)
{
	TEST_FIXTURE(Vector3Fixture, DotProductTest)
	{
		vectorA.Set(13.24f, 0.98f, -400.32f);
		vectorB.Set(-130.24f, 0.001f, -4.32f);
		dynamx::real dot = vectorA.DotProduct(vectorB);
		CHECK_CLOSE(5.0058, dot, DN_CLOSE_FLOAT);
	}

	TEST_FIXTURE(Vector3Fixture, CrossProductTest)
	{
		vectorA.Set(1,2,3);
		vectorB.Set(4,5,6);
		dynamx::Vector3 vectorC = vectorA.CrossProduct(vectorB);
		CHECK_CLOSE(-3, vectorC.GetX(), DN_CLOSE_FLOAT);
		CHECK_CLOSE(6, vectorC.GetY(), DN_CLOSE_FLOAT);
		CHECK_CLOSE(-3, vectorC.GetZ(), DN_CLOSE_FLOAT);
	}
}
