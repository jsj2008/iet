#include <UnitTest++.h>

#include <TestCommon.hpp>

#include <dynamx/RigidBodyGeometry.hpp>
#include <dynamx/ObjLoader.hpp>

using namespace dynamx;

class Fixture
{
	public:
		Fixture() 
		{ 
		}

		~Fixture() 
		{
		} 

		dynamx::ObjLoader oLoader;
};

SUITE(ObjLoaderTestSuite)
{
	TEST_FIXTURE(Fixture, BasicTest)
	{
		RigidBodyGeometry geom;
		oLoader.LoadFile(std::string("cube.obj"), &geom);
	}
}
