#include "jfModel.hpp"

#include <iostream>
using namespace std;

jfModel::jfModel()
	:
		m_CurrentVertexId(1),
		m_CurrentFaceId(1),
		m_CurrentNormalId(1),
		m_CurrentVertexTextureId(1),
		m_List(0)

{
}

jfModel::~jfModel()
{
}

void jfModel::createList()
{
	m_List = glGenLists(1);
	glNewList(m_List, GL_COMPILE);

	typedef map<jfFaceId, jfFace> jfFaceMap;
	jfFaceMap::const_iterator itFaceEnd = m_Faces.end(); 
	for (jfFaceMap::const_iterator itFace = m_Faces.begin(); itFace != itFaceEnd; ++itFace)
	{
		glBegin(GL_POLYGON);
//		glBegin(GL_TRIANGLES);

//		glBegin(GL_LINE_LOOP);
		vector<jfVertexId> vertexIds = (*itFace).second.getVertexIds();

		jfVector3 v0 = jfVector3(getVertex(vertexIds[0]).getPos());
		jfVector3 v1 = jfVector3(getVertex(vertexIds[1]).getPos());
		jfVector3 v2 = jfVector3(getVertex(vertexIds[2]).getPos());
		jfVector3 normal = v1.subtract(v0).crossProduct(v2.subtract(v0));
//		jfVector3 normal = v2.subtract(v0).crossProduct(v1.subtract(v0));
		normal.normalize();
//		glNormal3f(normal.getX(), normal.getY(), normal.getZ());
		cout<<"normal x is "<<normal.getX()<<endl;
		cout<<"normal y is "<<normal.getY()<<endl;
		cout<<"normal z is "<<normal.getZ()<<endl;

		glColor3f(0.3,0.3,0.3);

		vector<jfVertexId>::iterator vItEnd = vertexIds.end();
		for(vector<jfVertexId>::iterator vIt = vertexIds.begin() ; 
				vIt != vItEnd ;
				vIt++)
		{
			jfVertex vertex = getVertex((*vIt));
			glPushMatrix();

//			jfVector3 normal = getNormal((*vIt)).getVector();
			glNormal3f(normal.getX(), normal.getY(), normal.getZ());

	//		jfVertexTexture tex = getVertexTexture((*vIt));
	//		glTexCoord2f(tex.getU(), tex.getV());

//			glNormal3f(normal.getX(), normal.getY(), normal.getZ());

			glVertex3f(vertex.getPos().getX(),
					vertex.getPos().getY(),
					vertex.getPos().getZ());
			glPopMatrix();
		}
		glEnd();

		/*
		glBegin(GL_LINES);
			glPushMatrix();
			glVertex3f(v0.getX(), 
					v0.getY(),
					v0.getZ());
			glVertex3f(v0.getX() + normal.getX(), 
					v0.getY() + normal.getY(),
					v0.getZ() + normal.getZ());
			glPopMatrix();	
		glEnd();
		*/
	}
	glEndList();
}

void jfModel::draw() const
{
	glCallList(m_List);
}
