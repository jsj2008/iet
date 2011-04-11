#ifndef  VERTEX_H
#define  VERTEX_H

#include <dynamx/Point3.hpp>

#include <vector>

using namespace std;

namespace dynamx
{
	
	/*
	 * =====================================================================================
	 *        Class: Vertex
	 *  Description:
	 * =====================================================================================
	 */
	class Vertex
	{
		public:
			Vertex();

			virtual ~Vertex();

			void AddFaceId(FaceId val)
			{
				m_FaceIds.push_back(val);
			}

			vector<FaceId> GetFaceIds() const
			{
				return m_FaceIds;
			}

			void SetPos(const Point3& val)
			{
				m_Pos = val;
			}

			Point3 GetPos() const
			{
				return m_Pos;
			}

			VertexId GetId() const
			{
				return m_Id;
			}

			void SetId(VertexId val)
			{
				m_Id = val;
			}

		protected:
			Point3 m_Pos;
			vector<FaceId> m_FaceIds;
			VertexId m_Id;

		private:
	};

}

#endif   // VERTEX_H
