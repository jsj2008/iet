#ifndef  JFFACE_H
#define  JFFACE_H

#include <jfCore/jfCore.hpp>
#include <jfModel/jfVertex.hpp>

/*
 * =====================================================================================
 *        Class: jfFace
 *  Description:
 * =====================================================================================
 */
class jfFace
{
	public:
		jfFace();

		virtual ~jfFace();

		void addVertexId(jfVertexId vid)
		{
			m_VertexIds.push_back(vid);
		}

		void addNormalId(jfNormalId vid)
		{
			m_NormalIds.push_back(vid);
		}

		void addVertexTextureId(jfVertexTextureId vid)
		{
			m_VertexTextureIds.push_back(vid);
		}

		vector<jfVertexId> getVertexIds() const
		{
			return m_VertexIds;
		}

		jfFaceId getId() const
		{
			return m_Id;
		}

		void setId(jfFaceId val)
		{
			m_Id = val;
		}

	protected:
		vector<jfVertexId> m_VertexIds;
		vector<jfNormalId> m_NormalIds;
		vector<jfVertexTextureId> m_VertexTextureIds;
		jfFaceId m_Id;
};

#endif   // JFFACE_H
