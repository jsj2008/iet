#include "RigidBody.hpp"

namespace dynamx
{
	RigidBody::RigidBody()
		:
			m_LinearDamping(0.8f),
			m_AngularDamping(0.8f),
			m_InverseMass(1)
	{
		m_DebugDraw = true;
		shared_ptr<AABB> aabb(new AABB());
		m_AABB = aabb;
		//m_ConstantAccel = Vector3(0,-0.3,0);
		m_ConstantAccel = Vector3(0,-9.8,0);
	}

	RigidBody::~RigidBody()
	{
	}


	void RigidBody::Integrate(float timestep)
	{
		//Euler Integration

		//F/m = a, duh.
		//Also : v(t) = P(t) / M
		Vector3 linearAccel = m_ConstantAccel;
		linearAccel.AddScaledVector(m_ForceAccum, m_InverseMass);

		//Transform torque into angular accel
		//w(t) = I(t)^-1 . L(t).
		Vector3 angularAccel;
		m_InverseInertiaTensorWorld.Multiply(m_TorqueAccum, &angularAccel);

		//Update linear and angular velocity
		m_LinearVel.AddScaledVector(linearAccel, timestep);
		m_AngularVel.AddScaledVector(angularAccel, timestep);

		//Drag
		m_LinearVel = m_LinearVel.Multiply(real_pow(m_LinearDamping, timestep));
		m_AngularVel = m_AngularVel.Multiply(real_pow(m_AngularDamping, timestep));

		//Update pos from linear vel
		m_Pos.AddScaledVector(m_LinearVel, timestep);

		//Angular velocity update to orientation
//		Vector3 scaledAngularVel = m_AngularVel.Multiply(timestep);
		m_Orientation.AddScaledVector(m_AngularVel, timestep);

		//Drag
		m_LinearVel = m_LinearVel.Multiply(real_pow(m_LinearDamping, timestep));
		m_AngularVel = m_AngularVel.Multiply(real_pow(m_AngularDamping, timestep));


		/*
		Matrix3 w_t;
		w_t.SetElem(0, 1);
		//w_t.SetElem(0, 0);
		w_t.SetElem(1, -scaledAngularVel.GetZ());
		w_t.SetElem(2, scaledAngularVel.GetY());
		w_t.SetElem(3, scaledAngularVel.GetZ());
		w_t.SetElem(4, 1);
		//w_t.SetElem(4, 0);
		w_t.SetElem(5, -scaledAngularVel.GetX());
		w_t.SetElem(6, -scaledAngularVel.GetY());
		w_t.SetElem(7, scaledAngularVel.GetX());
		w_t.SetElem(8, 1);
		//w_t.SetElem(8, 0);
		w_t.Multiply(m_Orientation, &m_Orientation);
		*/

		CalculateInternals();

		ClearAccumulators();
	}

	void RigidBody::CalculateInternals()
	{
		m_Orientation.Normalize();

		m_Transform.SetFromOrientationAndPos(m_Orientation, m_Pos);

		//Update aabb
		m_AABB->SetPos(m_Pos);
		m_Geom.TransformGeometry(m_Transform, &m_TransformedGeom);
		m_AABB->UpdateExtents(m_TransformedGeom);

		Matrix3 orientationMatrix;
		m_Transform.GetOrientationMatrix(&orientationMatrix);

		TransformInertiaTensor( &m_InverseInertiaTensorWorld,
				m_InverseInertiaTensor,
				orientationMatrix);


		//Derived Quantities
        //Vector3 angularAccel;
		//m_InverseInertiaTensorWorld.Multiply(m_TorqueAccum, &m_Omega);
		m_InverseInertiaTensor.Multiply(m_AngularVel, &m_Omega);
        m_V = m_LinearVel.Multiply(m_InverseMass);
		m_LinearMomentum = m_LinearVel.Multiply(GetMass());
		m_AngularMomentum = m_AngularVel.Multiply(GetMass());
	}

	/*
	void RigidBody::StateToArray(real *y)
	{
		*y++ = m_Pos.GetX();
		*y++ = m_Pos.GetY();
		*y++ = m_Pos.GetZ();
		*y++ = m_Orienation.GetR();
		*y++ = m_Orienation.GetI();
		*y++ = m_Orienation.GetJ();
		*y++ = m_Orienation.GetK();
		*y++ = m_P.GetX();
		*y++ = m_P.GetY();
		*y++ = m_P.GetZ();
		*y++ = m_L.GetX();
		*y++ = m_L.GetY();
		*y++ = m_L.GetZ();
	}

	void RigidBody::ArrayToState(RigidBody *rb, double *y)
	{
		rb->GetPos().SetX(*y++);
		rb->GetPos().SetY(*y++);
		rb->GetPos().SetZ(*y++);
		m_Orienation.SetR(*y++);
		m_Orienation.SetI(*y++);
		m_Orienation.SetJ(*y++);
		m_Orienation.SetK(*y++);
		m_P.SetX(*y++);
		m_P.SetY(*y++);
		m_P.SetZ(*y++);
		m_L.SetX(*y++);
		m_L.SetY(*y++);
		m_L.SetZ(*y++);
		// Compute auxiliary variables... 
		m_V = m_P.Multiply(m_InverseMass);
		// I −1 (t) = R(t)Ibody R(t) T 
		//rb->Iinv = R * Ibodyinv * Transpose(R);
		m_InverseInertiaTensorWorld.Multiply(m_L, &m_Omega);
	}
*/

	void RigidBody::ClearAccumulators()
	{
		m_ForceAccum.Clear();
		m_TorqueAccum.Clear();
	}

	void RigidBody::GetPointInLocalSpace(const Point3& point, Point3* result) const
	{
		m_Transform.TransformInverse(point, result);
	}

	void RigidBody::GetPointInWorldSpace(const Point3& point, Point3* result) const
	{
		m_Transform.Transform(point, result);
	}

	void RigidBody::AddForceAtBodyPoint(const Vector3& force, const Point3& point)
	{
		Point3 pointInWorldSpace;
		GetPointInWorldSpace(point, &pointInWorldSpace);
		AddForceAtPoint(force, pointInWorldSpace);
	}

	void RigidBody::TransformInertiaTensor(Matrix3* iitWorld
			, const Matrix3& iitBody
			, const Matrix3& rotMat) const
	{
		//I(t) = R(t) . I_body . R(t)^T
		Matrix3 rotatedIit;
		rotMat.Multiply(iitBody, &rotatedIit);
		Matrix3 transRotMat;
		rotMat.GetTranspose(&transRotMat);
		rotatedIit.Multiply(transRotMat, iitWorld);
	}

	void RigidBody::AddForceAtPoint(const Vector3& force, const Point3& point)
	{
		Vector3 pointCrossForce;
		Vector3 posAsVec = m_Pos.ToVector3();
		Vector3 pointRelative = point.ToVector3().Subtract(posAsVec);

		m_ForceAccum = m_ForceAccum.Add(force);
		pointCrossForce = pointRelative.CrossProduct(force);
		m_TorqueAccum = m_TorqueAccum.Add(pointCrossForce);
	}

	void RigidBody::DrawMesh()
	{
		/*
		//Cube!
		glBegin(GL_QUADS);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f( 1.0f, 1.0f,-1.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f( 1.0f, 1.0f, 1.0f);
			glColor3f(1.0f,0.5f,0.0f);	
			glVertex3f( 1.0f,-1.0f, 1.0f);
			glVertex3f(-1.0f,-1.0f, 1.0f);
			glVertex3f(-1.0f,-1.0f,-1.0f);
			glVertex3f( 1.0f,-1.0f,-1.0f);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f( 1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f,-1.0f, 1.0f);
			glVertex3f( 1.0f,-1.0f, 1.0f);
			glColor3f(1.0f,1.0f,0.0f);
			glVertex3f( 1.0f,-1.0f,-1.0f);
			glVertex3f(-1.0f,-1.0f,-1.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);
			glVertex3f( 1.0f, 1.0f,-1.0f);
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);
			glVertex3f(-1.0f,-1.0f,-1.0f);
			glVertex3f(-1.0f,-1.0f, 1.0f);
			glColor3f(1.0f,0.0f,1.0f);
			glVertex3f( 1.0f, 1.0f,-1.0f);
			glVertex3f( 1.0f, 1.0f, 1.0f);
			glVertex3f( 1.0f,-1.0f, 1.0f);
			glVertex3f( 1.0f,-1.0f,-1.0f);
		glEnd();
		*/

		typedef map<VertexId, Vertex> VertexMap;
		VertexMap vertices = m_Geom.GetVertices();
		VertexMap::const_iterator end = vertices.end(); 

		/*
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
		for (VertexMap::const_iterator it = vertices.begin(); it != end; ++it)
		{
			glPushMatrix();
			glVertex3f((*it).second.GetPos().GetX(), 
					(*it).second.GetPos().GetY(),
					(*it).second.GetPos().GetZ());
			glPopMatrix();
		}
		glEnd();
		*/

		glCallList(m_RigidBodyList);


		/*
		glColor3f(1.0,1.0,0.0);

		typedef map<FaceId, Face> FaceMap;
		FaceMap faces = m_Geom.GetFaces();
		FaceMap::const_iterator itFaceEnd = faces.end(); 

		for (FaceMap::const_iterator itFace = faces.begin(); itFace != itFaceEnd; ++itFace)
		{
			glBegin(GL_POLYGON);
			vector<VertexId> vertexIds = (*itFace).second.GetVertexIds();
			vector<VertexId>::iterator vItEnd = vertexIds.end();
			for(vector<VertexId>::iterator vIt = vertexIds.begin() ; 
					vIt != vItEnd ;
					vIt++)
			{
				Vertex vertex = m_Geom.GetVertex((*vIt));
				glPushMatrix();
				glVertex3f(vertex.GetPos().GetX(), 
						vertex.GetPos().GetY(),
						vertex.GetPos().GetZ());
				glPopMatrix();
			}
			glEnd();
		}
		*/

	}

	void RigidBody::VDraw()
	{
		//Simple draw, just a cube.

		GLfloat mat[16];
		m_Transform.FillColumnMajorArray(mat);

		//TODO : Transform all points in mesh rather than just doing a mult matrix
		glPushMatrix();
			glMultMatrixf(mat);
			DrawMesh();
		glPopMatrix();

		/*
		if(m_DebugDraw)
		{
			m_AABB->DebugDraw();	
		}
		*/
	}

	void RigidBody::CreateList()
	{

		m_RigidBodyList = glGenLists(1);
		glNewList(m_RigidBodyList, GL_COMPILE);

//		glColor3f(1.0,1.0,0.0);

		typedef map<FaceId, Face> FaceMap;
		FaceMap faces = m_Geom.GetFaces();
		FaceMap::const_iterator itFaceEnd = faces.end(); 

		for (FaceMap::const_iterator itFace = faces.begin(); itFace != itFaceEnd; ++itFace)
		{
//			glBegin(GL_POLYGON);
			glBegin(GL_LINE_LOOP);
			vector<VertexId> vertexIds = (*itFace).second.GetVertexIds();
			vector<VertexId>::iterator vItEnd = vertexIds.end();
			for(vector<VertexId>::iterator vIt = vertexIds.begin() ; 
					vIt != vItEnd ;
					vIt++)
			{
				Vertex vertex = m_Geom.GetVertex((*vIt));
				glPushMatrix();
				glVertex3f(vertex.GetPos().GetX(), 
						vertex.GetPos().GetY(),
						vertex.GetPos().GetZ());
				glPopMatrix();
			}
			glEnd();
		}
		glEndList();
	}

	void RigidBody::LoadModel(std::string filename)
	{
		ObjLoader objLoader;
		objLoader.LoadFile(filename, &m_Geom);
		CreateList();
	}
}
