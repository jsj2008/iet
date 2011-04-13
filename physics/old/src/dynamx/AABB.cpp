#include "AABB.hpp"

#include <float.h>

namespace dynamx
{
	AABB::AABB()
	{
		m_Colliding = false;
		m_Extents.SetX(0);
		m_Extents.SetY(0);
		m_Extents.SetZ(0);
	}

	AABB::~AABB()
	{
	}

	void AABB::UpdateExtents(const RigidBodyGeometry& geom)
	{
		//TODO : Maybe better values for initial values.
		/*
		real minX = geom.GetVertex(1).GetPos().GetX();
		real maxX = geom.GetVertex(1).GetPos().GetX();
		real minY = geom.GetVertex(1).GetPos().GetY();
		real maxY = geom.GetVertex(1).GetPos().GetY();
		real minZ = geom.GetVertex(1).GetPos().GetZ();
		real maxZ = geom.GetVertex(1).GetPos().GetZ();
		*/

		real minX = FLT_MAX;
		real maxX = -FLT_MAX;
		real minY = FLT_MAX;
		real maxY = -FLT_MAX;
		real minZ = FLT_MAX;
		real maxZ = -FLT_MAX;
		typedef map<VertexId, Vertex> VertexMap;
		VertexMap vertices = geom.GetVertices();
		VertexMap::const_iterator end = vertices.end(); 

		for (VertexMap::const_iterator it = vertices.begin(); it != end; ++it)
		{
			Vertex v = (*it).second;
			real xExtent = v.GetPos().GetX() - m_Pos.GetX();
			real yExtent = v.GetPos().GetY() - m_Pos.GetY();
			real zExtent = v.GetPos().GetZ() - m_Pos.GetZ();

			if(xExtent < minX)
			{ 
				minX = xExtent; 
			}
			else if(xExtent > maxX)
			{
				maxX = xExtent;
			}

			if(yExtent < minY)
			{ 
				minY = yExtent; 
			}
			else if(yExtent > maxY)
			{
				maxY = yExtent;
			}

			if(zExtent < minZ)
			{ 
				minZ = zExtent; 
			}
			else if(zExtent > maxZ)
			{
				maxZ = zExtent;	
			}
		}
		m_Extents.SetX(std::max(real_abs(minX), real_abs(maxX)));
		m_Extents.SetY(std::max(real_abs(minY), real_abs(maxY)));
		m_Extents.SetZ(std::max(real_abs(minZ), real_abs(maxZ)));
	}

	void AABB::DebugDraw()
	{
		glPushMatrix();
		glTranslatef(m_Pos.GetX(), m_Pos.GetY(), m_Pos.GetZ());
		if(m_Colliding)
		{
			glColor3f(1.0,0.0,0.0);
		}
		else
		{
			glColor3f(0.0,1.0,0.0);
		}
		glBegin(GL_LINE_LOOP);
//			glVertex3f(0,0,0);

			//Back Face
			glVertex3f(-m_Extents.GetX(), 
					-m_Extents.GetY(),
					-m_Extents.GetZ());

			glVertex3f(-m_Extents.GetX(), 
					m_Extents.GetY(),
					-m_Extents.GetZ());

			glVertex3f(-m_Extents.GetX(), 
					m_Extents.GetY(),
					m_Extents.GetZ());

			glVertex3f(-m_Extents.GetX(), 
					-m_Extents.GetY(),
					m_Extents.GetZ());
		glEnd();

		glBegin(GL_LINE_LOOP);
			//Front Face
			glVertex3f(m_Extents.GetX(), 
					-m_Extents.GetY(),
					m_Extents.GetZ());

			glVertex3f(m_Extents.GetX(), 
					m_Extents.GetY(),
					m_Extents.GetZ());

			glVertex3f(m_Extents.GetX(), 
					m_Extents.GetY(),
					-m_Extents.GetZ());

			glVertex3f(m_Extents.GetX(), 
					-m_Extents.GetY(),
					-m_Extents.GetZ());
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(m_Extents.GetX(), 
					-m_Extents.GetY(),
					m_Extents.GetZ());

			glVertex3f(m_Extents.GetX(), 
					m_Extents.GetY(),
					m_Extents.GetZ());
			glVertex3f(-m_Extents.GetX(), 
					m_Extents.GetY(),
					m_Extents.GetZ());

			glVertex3f(-m_Extents.GetX(), 
					-m_Extents.GetY(),
					m_Extents.GetZ());

		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(m_Extents.GetX(), 
					m_Extents.GetY(),
					-m_Extents.GetZ());

			glVertex3f(m_Extents.GetX(), 
					-m_Extents.GetY(),
					-m_Extents.GetZ());
			glVertex3f(-m_Extents.GetX(), 
					-m_Extents.GetY(),
					-m_Extents.GetZ());

			glVertex3f(-m_Extents.GetX(), 
					m_Extents.GetY(),
					-m_Extents.GetZ());

		glEnd();
		glPopMatrix();
	}
}
