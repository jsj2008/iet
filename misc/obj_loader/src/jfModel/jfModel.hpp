#ifndef  JFMODEL_H
#define  JFMODEL_H

#include <GL/glu.h>

#include <jfCore/jfCore.hpp>
#include <jfModel/jfFace.hpp>
#include <jfModel/jfVertex.hpp>
#include <jfModel/jfNormal.hpp>
#include <jfModel/jfVertexTexture.hpp>

/*
 * =====================================================================================
 *        Class: jfModel
 *  Description:
 * =====================================================================================
 */
class jfModel
{
	public:
		jfModel();

		virtual ~jfModel();

		//Factory Methods
		jfVertex makeVertex()
		{
			jfVertex v;
			v.setId(m_CurrentVertexId++);
			return v;
		}

		jfFace makeFace()
		{
			jfFace f;
			f.setId(m_CurrentFaceId++);
			return f;
		}

		jfNormal makeNormal()
		{
			jfNormal n;
			n.setId(m_CurrentNormalId++);
			return n;
		}

		jfVertexTexture makeVertexTexture()
		{
			jfVertexTexture t;
			t.setId(m_CurrentVertexTextureId++);
			return t;
		}
		//End Factory Methods

		void addVertex(jfVertex& v)
		{
			m_Vertices[v.getId()] = v;
		}

		void addVertexTexture(jfVertexTexture& v)
		{
			m_VertexTextures[v.getId()] = v;
		}

		void addNormal(jfNormal& v)
		{
			m_Normals[v.getId()] = v;
		}

		jfVertex getVertex(jfVertexId vid) const
		{
			return (*m_Vertices.find(vid)).second;
		}

		jfNormal getNormal(jfNormalId id) const
		{
			return (*m_Normals.find(id)).second;
		}

		jfVertexTexture getVertexTexture(jfVertexTextureId id) const
		{
			return (*m_VertexTextures.find(id)).second;
		}

		map<jfVertexId, jfVertex> getVertices() const
		{
			return m_Vertices;
		}

		void addFace(jfFace& face)
		{
			m_Faces[face.getId()] = face;
		}

		map<jfFaceId, jfFace> getFaces()
		{
			return m_Faces;
		}	

		void createList();

		GLuint getList() const
		{
			return m_List;
		}

		void draw() const;

	protected:
		int m_CurrentVertexId;
		int m_CurrentFaceId;
		int m_CurrentVertexTextureId;
		int m_CurrentNormalId;

		map<jfFaceId, jfFace> m_Faces;
		map<jfVertexId, jfVertex> m_Vertices;
		map<jfVertexTextureId, jfVertexTexture> m_VertexTextures;
		map<jfNormalId, jfNormal> m_Normals;

		GLuint m_List;

	private:
};


#endif   // JFMODEL_H
