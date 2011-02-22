#include <UnitTest++.h>

#include <TestCommon.hpp>

#include <dynamx/RigidBody.hpp>

class RigidBodyFixture
{
	public:
		RigidBodyFixture() 
		{ 
		}

		~RigidBodyFixture() 
		{
		} 

		dynamx::RigidBody rigidbody;
};

SUITE(RigidBodyTestSuite)
{
	TEST_FIXTURE(RigidBodyFixture, IntegrationAccuracyTest)
	{
//		DN_NOT_IMPLEMENTED;

		float h = 0.01;
		dynamx::Point3 pos(1.0f, 5.0f, -3.0f);
		dynamx::Vector3 force(0.0f, -10.0f, 0.4f);
/*
		rigidbody.SetPos(pos);
		rigidbody.ClearForces();
		rigidbody.AddForce(force);
*/
		rigidbody.Integrate(h);
		/*
		 * TODO : Runge kutta 4th order.
		//RigidBody should have travelled
		//Using 4th Order Runge Kutta method:
		//x(t0 + h) = x0 + 1/6(k1) + 1/3(k2) + 1/3(k3) + 1/6(k4)
		// where:
		// 	h is stepsize
		// 	k1 = h * f (x0, t0)
		// 	k2 = h * f (x0 + (k1/2), t0 + (h/2))
		// 	k3 = h * f (x0 + (k2/2), t0 + (h/2))
		// 	k4 = h * f (x0 + k3, t0 + h)
		//Error is :
		//	O(h^3)
		*/

/*
		//Euler integration.		
		CHECK_CLOSE(pos.GetX() + (h * force.GetX()), 
				rigidbody.GetPos().GetX(), 
				DN_CLOSE_FLOAT);

		CHECK_CLOSE(pos.GetY() + (h * force.GetY()), 
				rigidbody.GetPos().GetY(), 
				DN_CLOSE_FLOAT);

		CHECK_CLOSE(pos.GetZ() + (h * force.GetZ()), 
				rigidbody.GetPos().GetZ(), 
				DN_CLOSE_FLOAT);
*/

	}
}
