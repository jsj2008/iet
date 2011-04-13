#ifndef  RIGIDBODYGEOMETRY_H
#define  RIGIDBODYGEOMETRY_H

#include <vector>
#include <map>

#include <dynamx/Matrix4.hpp>
#include <dynamx/Point3.hpp>
#include <dynamx/Face.hpp>
#include <dynamx/Vertex.hpp>

using namespace std;

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: RigidBodyGeometry
	 *  Description:
	 * =====================================================================================
	 */
	class RigidBodyGeometry
	{
		public:
			RigidBodyGeometry();

			virtual ~RigidBodyGeometry();

			//Factory Methods
			Vertex MakeVertex()
			{
				Vertex v;
				v.SetId(m_CurrentVertexId++);
				return v;
			}

			Face MakeFace()
			{
				Face f;
				f.SetId(m_CurrentFaceId++);
				return f;
			}
			//End Factory Methods
			
			void AddVertex(Vertex& v)
			{
				m_Vertices[v.GetId()] = v;
			}

			Vertex GetVertex(VertexId vid) const
			{
				return (*m_Vertices.find(vid)).second;
			}

			map<VertexId, Vertex> GetVertices() const
			{
				return m_Vertices;
			}

			/*
			vector<FaceId> GetFaceIds() const
			{
				return m_Faces;
			}
			*/

			void FaceToVertex(Face) const
			{
				//TODO
			}

			void AddFace(Face& face)
			{
				m_Faces[face.GetId()] = face;
			}

			map<FaceId, Face> GetFaces()
			{
				return m_Faces;
			}

			void TransformGeometry(const Matrix4& transformMat, RigidBodyGeometry* result) const;

			void Reset();
			
		protected:
			int m_CurrentVertexId;
			int m_CurrentFaceId;

			map<FaceId, Face> m_Faces;
			map<VertexId, Vertex> m_Vertices;

		private:
	};
}

#endif   // RIGIDBODYGEOMETRY_H
