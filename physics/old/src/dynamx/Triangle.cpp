#include "Triangle.hpp"

namespace dynamx
{
	Triangle::Triangle()
		:
			m_NormalSphereList(0),
			m_Quadric(gluNewQuadric()),
			m_ClosestFeature(-1),
			m_Colliding(0)
	{
	}

	Triangle::~Triangle()
	{
		gluDeleteQuadric(m_Quadric);
	}

	void Triangle::ChooseColour(int i)
	{
		if(!m_Colliding)
		{
			if(m_ClosestFeature == i)
			{
				glColor3f(1,0,0);
			}
			else
			{
				glColor3f(0,1,0);
			}
		}
		else
		{
				glColor3f(1,0,0);
		}
	}

	void Triangle::DrawEdge(int i)
	{
		ChooseColour(i+3);
		glVertex3f(m_Edges[i].GetOrigin().GetX(),
				m_Edges[i].GetOrigin().GetY(),
				m_Edges[i].GetOrigin().GetZ());
		Vector3 other = m_Edges[i].GetOrigin().ToVector3().Add(m_Edges[i].GetDirection().Multiply(m_Edges[i].GetLength()));
		glVertex3f(other.GetX(),
				other.GetY(),
				other.GetZ());
	}

	void Triangle::VDraw()
	{
		float Radius = 0.1;
		float SphereStacks = 30;
		float SphereSlices = 30;
		m_NormalSphereList = glGenLists(1);
		glNewList(m_NormalSphereList, GL_COMPILE);
			gluSphere( m_Quadric, Radius, SphereSlices, SphereStacks);
		glEndList ();

		glPushMatrix();
		glColor3f(0.1,0.9,1);

		glPushMatrix();
		ChooseColour(0);
		glTranslatef(m_Points[0].GetX(),
					m_Points[0].GetY(),
					m_Points[0].GetZ());
		glCallList(m_NormalSphereList);
		glPopMatrix();

		glPushMatrix();
		ChooseColour(1);
		glTranslatef(m_Points[1].GetX(),
					m_Points[1].GetY(),
					m_Points[1].GetZ());
		glCallList(m_NormalSphereList);
		glPopMatrix();


		glPushMatrix();
		ChooseColour(2);
		glTranslatef(m_Points[2].GetX(),
					m_Points[2].GetY(),
					m_Points[2].GetZ());
		glCallList(m_NormalSphereList);
		glPopMatrix();

		glColor3f(0.1,0.9,1);
		glPushMatrix();
		/*
		glBegin(GL_LINE_LOOP);
		//glBegin(GL_POINTS);
				glPushMatrix();
				glVertex3f(m_Points[0].GetX(),
					m_Points[0].GetY(),
					m_Points[0].GetZ());
				glVertex3f(m_Points[1].GetX(),
					m_Points[1].GetY(),
					m_Points[1].GetZ());
				glVertex3f(m_Points[2].GetX(),
					m_Points[2].GetY(),
					m_Points[2].GetZ());
				glPopMatrix();	
		glEnd();
		*/

		if(m_ClosestFeature == 6)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glBegin(GL_LINES);
		}
			glPushMatrix();
				DrawEdge(0);
				DrawEdge(1);
				DrawEdge(2);
				/*
		m_Edges[0].SetLength(m_Points[0].CalculateDistance(m_Points[1]));
//		m_Edges[0].SetDirection( m_Points[1].ToVector3().Subtract(m_Points[0].ToVector3()));
		//m_Edges[0].SetDirection( m_Points[1].ToVector3().Subtract(m_Points[0].ToVector3()));
		m_Edges[0].SetDirection( m_Points[0].ToVector3().Subtract(m_Points[1].ToVector3()));
		*/

		/*
				glVertex3f(m_Points[0].GetX(),
					m_Points[0].GetY(),
					m_Points[0].GetZ());
				glVertex3f(m_Points[1].GetX(),
					m_Points[1].GetY(),
					m_Points[1].GetZ());
					*/

				/*
				ChooseColour(4);
				glVertex3f(m_Points[1].GetX(),
					m_Points[1].GetY(),
					m_Points[1].GetZ());
				glVertex3f(m_Points[2].GetX(),
					m_Points[2].GetY(),
					m_Points[2].GetZ());

				ChooseColour(5);
				glVertex3f(m_Points[2].GetX(),
					m_Points[2].GetY(),
					m_Points[2].GetZ());
				glVertex3f(m_Points[0].GetX(),
					m_Points[0].GetY(),
					m_Points[0].GetZ());
					*/
			glPopMatrix();
		glEnd();
		glPopMatrix();
		glPopMatrix();

	}

	void Triangle::SetClosestFeature(int i, const Point3& point)
	{
		m_ClosestFeature = i;
		m_ClosestPoint = point;
	}

	Point3 Triangle::GetClosestFeaturePos()
	{
		//TODO: Add support for lines and face.
//		return m_Points[m_ClosestFeature];
		return m_ClosestPoint;
	}

	void Triangle::CreateEdges()
	{
		//0 --> 1
		m_Edges[0].SetOrigin(m_Points[0]);
		m_Edges[0].SetLength(m_Points[0].CalculateDistance(m_Points[1]));
//		m_Edges[0].SetDirection( m_Points[1].ToVector3().Subtract(m_Points[0].ToVector3()));
		//m_Edges[0].SetDirection( m_Points[1].ToVector3().Subtract(m_Points[0].ToVector3()));
		Vector3 direction0 = m_Points[1].ToVector3().Subtract(m_Points[0].ToVector3());
		direction0.Normalize();
		m_Edges[0].SetDirection( direction0 );

		//1 --> 2
		m_Edges[1].SetOrigin(m_Points[1]);
		m_Edges[1].SetLength(m_Points[1].CalculateDistance(m_Points[2]));
//		m_Edges[1].SetDirection( m_Points[2].ToVector3().Subtract(m_Points[1].ToVector3()));
//		m_Edges[1].SetDirection( m_Points[1].ToVector3().Subtract(m_Points[2].ToVector3()));

		Vector3 direction1 = m_Points[2].ToVector3().Subtract(m_Points[1].ToVector3());
		direction1.Normalize();
		m_Edges[1].SetDirection( direction1 );

		//2 --> 0
		m_Edges[2].SetOrigin(m_Points[2]);
		m_Edges[2].SetLength(m_Points[0].CalculateDistance(m_Points[2]));
//		m_Edges[2].SetDirection( m_Points[0].ToVector3().Subtract(m_Points[2].ToVector3()));

		Vector3 direction2 = m_Points[0].ToVector3().Subtract(m_Points[2].ToVector3());
		direction2.Normalize();
		m_Edges[2].SetDirection( direction2 );
	}

	CollisionPlane Triangle::GetPlane() const
	{
		CollisionPlane result;
		result.SetNormal(m_Edges[0].GetDirection().CrossProduct(m_Edges[1].GetDirection()));
		result.SetPoint(m_Points[0]);
		return result;
	}

	void Triangle::SetGlobalPos(const Point3& pos)
	{
		m_Points[0] = pos.Add(m_LocalPoints[0]);
		m_Points[1] = pos.Add(m_LocalPoints[1]);
		m_Points[2] = pos.Add(m_LocalPoints[2]);
		CreateEdges();
	}
}
