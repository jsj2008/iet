#include <UnitTest++.h>

#include <TestCommon.hpp>

#include <dynamx/Particle.hpp>

class ParticleFixture
{
	public:
		ParticleFixture() 
		{ 
		}

		~ParticleFixture() 
		{
		} 

		dynamx::Particle particle;
};

SUITE(ParticleTestSuite)
{
	TEST_FIXTURE(ParticleFixture, IntegrationAccuracyTest)
	{
		float h = 0.01;
		dynamx::Point3 pos(1.0f, 5.0f, -3.0f);
		dynamx::Vector3 force(0.0f, -10.0f, 0.4f);
		particle.SetPos(pos);
		particle.ClearForces();
		particle.AddForce(force);
		particle.Integrate(h);
		/*
		 * TODO : Runge kutta 4th order.
		//Particle should have travelled
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

		//Euler integration.		
		CHECK_CLOSE(pos.GetX() + (h * force.GetX()), 
				particle.GetPos().GetX(), 
				DN_CLOSE_FLOAT);

		CHECK_CLOSE(pos.GetY() + (h * force.GetY()), 
				particle.GetPos().GetY(), 
				DN_CLOSE_FLOAT);

		CHECK_CLOSE(pos.GetZ() + (h * force.GetZ()), 
				particle.GetPos().GetZ(), 
				DN_CLOSE_FLOAT);

	}
}
