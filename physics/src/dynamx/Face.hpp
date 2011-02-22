#ifndef  FACE_H
#define  FACE_H

#include <vector>

#include <dynamx/Core.hpp>

using namespace std;

namespace dynamx
{

	/*
	 * =====================================================================================
	 *        Class: Face
	 *  Description:
	 * =====================================================================================
	 */
	class Face
	{
		public:
			Face();

			virtual ~Face();

			void AddVertexId(VertexId vid)
			{
				m_VertexIds.push_back(vid);
			}

			vector<VertexId> GetVertexIds() const
			{
				return m_VertexIds;
			}

			FaceId GetId() const
			{
				return m_Id;
			}

			void SetId(FaceId val)
			{
				m_Id = val;
			}

		protected:
			vector<VertexId> m_VertexIds;
			FaceId m_Id;

		private:
	};
}

#endif   // FACE_H
