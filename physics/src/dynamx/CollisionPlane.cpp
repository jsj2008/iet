#include "CollisionPlane.hpp"

namespace dynamx
{
	CollisionPlane::CollisionPlane()
        : 
            RigidBody()
	{
        m_InverseMass = 0;
	}

	CollisionPlane::~CollisionPlane()
	{
	}

	void CollisionPlane::VDraw()
	{
		glPushMatrix();
		/*
			glRotatef( m_Normal.GetX(), 1.0, 0, 0 );
			glRotatef( m_Normal.GetY(), 1.0, 0, 0 );
			glRotatef( m_Normal.GetZ(), 1.0, 0, 0 );
			glTranslatef(m_Point.GetX(), m_Point.GetY(), m_Point.GetZ() );
			*/
			int halfsize = 100;
			glColor3f(1.0,0.0,0.0);
			glBegin(GL_LINE_LOOP);
				glVertex3f(halfsize, 0.0f, halfsize);
				glVertex3f(halfsize, 0.0f, -halfsize);
				glVertex3f(-halfsize, 0.0f, -halfsize);
				glVertex3f(-halfsize, 0.0f, halfsize);
				glVertex3f(halfsize, 0.0f, halfsize);

				glVertex3f(-halfsize, 0.0f, -halfsize);
				glVertex3f(halfsize, 0.0f, -halfsize);
				glVertex3f(-halfsize, 0.0f, halfsize);
			glEnd( );
		glPopMatrix();
	}
}
