#ifndef  RIGIDBODY_H
#define  RIGIDBODY_H

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

#include "SDL/SDL_opengl.h" 

#include <dynamx/Core.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/Vector3.hpp>
#include <dynamx/Matrix3.hpp>
#include <dynamx/Matrix4.hpp>
#include <dynamx/RigidBodyGeometry.hpp>
#include <dynamx/ObjLoader.hpp>
#include <dynamx/Vertex.hpp>
#include <dynamx/Face.hpp>
#include <dynamx/AABB.hpp>

using namespace std;
using namespace boost;

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: RigidBody
	 *  Description:
	 * =====================================================================================
	 */
	class RigidBody
	{
		public:
			RigidBody();

			virtual ~RigidBody();

			void Integrate(real timestep);

			void CalculateInternals();

			void ClearAccumulators();

			void AddForceAtBodyPoint(const Vector3& force, const Point3& point);

			void AddForceAtPoint(const Vector3& force, const Point3& point);

			void TransformInertiaTensor(Matrix3* iitWorld
					, const Matrix3& iitBody
					, const Matrix3& rotMat) const;

			//Util fns.
			void GetPointInLocalSpace(const Point3& point, Point3* result) const;
			void GetPointInWorldSpace(const Point3& point, Point3* result) const;

			//Drawing functions
			void LoadModel(std::string filename);
			void DrawMesh();
			virtual void VDraw();

			/*-----------------------------------------------------------------------------
			 *  Getters and Setters
			 *-----------------------------------------------------------------------------*/
			Point3& GetPos() { return m_Pos; }
			//Matrix3& GetOrientation() { return m_Orientation; }
			Quaternion& GetOrientation() { return m_Orientation; }
			RigidBodyGeometry GetTransformedGeom() const { return m_TransformedGeom; }
			Vector3& GetLinearVel() { return m_LinearVel; }
			Vector3& GetAngularVel() { return m_AngularVel; }
			shared_ptr<AABB> GetAABB() { return m_AABB; }

//			void SetOrientation(const Matrix3& val) { m_Orientation = val; }
			void SetOrientation(const Quaternion& val) { m_Orientation = val; }
			void SetLinearVel(const Vector3& val) { m_LinearVel = val; }
			void SetPos(const Point3& val) { m_Pos = val; }
			void SetAngularVel(const Vector3& val) { m_AngularVel = val; }

			//These are a bit different, we are setting their inverses as they are more useful.
			void SetMass(real mass) { assert(mass>0); m_InverseMass = 1/mass; }
			void SetInertiaTensor(const Matrix3& val) { val.GetInverse(&m_InverseInertiaTensor); }

			void CreateList();

		protected:
			//State vals
			Point3 m_Pos;
//			Matrix3 m_Orientation;
			Quaternion m_Orientation;
			Vector3 m_LinearVel;
			Vector3 m_AngularVel;

			real m_InverseMass;

			//Inverse of inertia tensor
			Matrix3 m_InverseInertiaTensor;

			//Internal vals calculated at every loop, basically cached values.
			Matrix4 m_Transform;
			Matrix3 m_InverseInertiaTensorWorld;

			//Will use these to work out Linear and angular momentum at the next integration step
			Vector3 m_ForceAccum;
			Vector3 m_TorqueAccum;

			//Damping
			real m_LinearDamping;
			real m_AngularDamping;

			//Geometry
			RigidBodyGeometry m_Geom;
			RigidBodyGeometry m_TransformedGeom;

			//Collision Detection
			//Broadphase
			shared_ptr<AABB> m_AABB;

			//Debug
			bool m_DebugDraw;

			//Drawing
			GLuint m_RigidBodyList;

		private:
	};
}

#endif   // RIGIDBODY_H
