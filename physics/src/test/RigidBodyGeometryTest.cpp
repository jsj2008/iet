#include <UnitTest++.h>

#include <TestCommon.hpp>

#include <dynamx/RigidBodyGeometry.hpp>

using namespace dynamx;

class RigidBodyGeometryFixture
{
	public:
		RigidBodyGeometryFixture() 
		{ 
		}

		~RigidBodyGeometryFixture() 
		{
		} 

		dynamx::RigidBodyGeometry g;
};

SUITE(RigidBodyGeometryTestSuite)
{
	TEST_FIXTURE(RigidBodyGeometryFixture, BasicTest)
	{
		/*
		Vertex v0 = g.MakeVertex();;
		v0.SetPos(Point3(0,0,0));
		Vertex v1 = g.MakeVertex();;
		v1.SetPos(Point3(1,0,0));
		Vertex v2 = g.MakeVertex();;
		v2.SetPos(Point3(1,1,0));
		Vertex v3 = g.MakeVertex();;
		v3.SetPos(Point3(0,1,0));
		Vertex v4 = g.MakeVertex();;
		v4.SetPos(Point3(0,0,1));
		Vertex v5 = g.MakeVertex();;
		v5.SetPos(Point3(1,0,1));
		Vertex v6 = g.MakeVertex();;
		v6.SetPos(Point3(1,1,1));
		Vertex v7 = g.MakeVertex();;
		v7.SetPos(Point3(0,1,1));
		Vertex v8 = g.MakeVertex();;
		v8.SetPos(Point3(0.5,0.5,0));
		Vertex v9 = g.MakeVertex();;
		v9.SetPos(Point3(0.5,0.5,1));

		Face f0 = g.MakeFace();
		g.FaceToVertex(f0.GetId(), v0.GetId());
		g.FaceToVertex(f0.GetId(), v4.GetId());
		g.FaceToVertex(f0.GetId(), v5.GetId());

		Face f1 = g.MakeFace();
		*/

	}
}
