#include "RigidBodyGeometry.hpp"

namespace dynamx
{

	RigidBodyGeometry::RigidBodyGeometry()
		:
			m_CurrentVertexId(1),
			m_CurrentFaceId(1)
	{
	}

	RigidBodyGeometry::~RigidBodyGeometry()
	{
	}

	void RigidBodyGeometry::Reset()
	{

		while( !m_Vertices.empty() ) 
		{
			m_Vertices.erase( m_Vertices.begin() );
		}

		while( !m_Faces.empty() ) 
		{
			m_Faces.erase( m_Faces.begin() );
		}
	}

	void RigidBodyGeometry::TransformGeometry(const Matrix4& transformMat, RigidBodyGeometry* result) const
	{
		typedef map<VertexId, Vertex> VertexMap;
		VertexMap vertices = m_Vertices;
		VertexMap::const_iterator end = vertices.end(); 
		for (VertexMap::const_iterator it = vertices.begin(); it != end; ++it)
		{
			Vertex transformedVertex;
			transformedVertex.SetId((*it).second.GetId());
			Point3 transformedVertexPos;
			transformMat.Transform((*it).second.GetPos(), &transformedVertexPos);
			transformedVertex.SetPos(transformedVertexPos);
			result->AddVertex(transformedVertex);
		}
	}

}
