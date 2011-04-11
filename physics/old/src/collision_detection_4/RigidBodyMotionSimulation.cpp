#include "RigidBodyMotionSimulation.hpp"

#include <float.h>

#include <dynamx/Vector3.hpp>

#include <iostream>
using namespace std;

const char* PARTICLE_TEX_PATH = "../../media/tex/particle_texture.tga";

RigidBodyMotionSimulation::RigidBodyMotionSimulation()
	:
		Simulation(),
		m_NarrowPhaseCollisionDetector(0),
		m_Plane(0),
		m_Particle(0),
		m_Quadric(0),
		m_NormalSphereList(0),
		isColliding(0),
		m_Contact(new Contact()),
		m_Triangle_0(new Triangle()),
		m_Triangle_1(new Triangle()),
		m_VoronoiChecker(new VoronoiChecker())
{
//	m_CollisionDetector = new SweepAndPruneCollisionDetector();
	//m_FpsTimer = new FpsTimer();
	m_NarrowPhaseCollisionDetector = new CollisionDetector();
	m_Quadric = gluNewQuadric();
}

RigidBodyMotionSimulation::~RigidBodyMotionSimulation()
{
//	delete m_CollisionDetector;
	delete m_NarrowPhaseCollisionDetector;
	delete m_Plane;
	delete m_Triangle_0;
}

void RigidBodyMotionSimulation::VOnInit()
{
	Simulation::VOnInit();

	InitGL();

//	m_Layout = new FTSimpleLayout();

//	m_Layout->SetFont(m_Font);

	CreateObjects();

	m_Camera.SetPos(dynamx::Point3(1,1,6));
	m_Camera.SetRot(dynamx::Vector3(0,0,0));

	m_Finished = false;

	float Radius = 0.3;
	float SphereStacks = 30;
	float SphereSlices = 30;
	m_NormalSphereList = glGenLists(1);
	glNewList(m_NormalSphereList, GL_COMPILE);
		gluSphere( m_Quadric, Radius, SphereSlices, SphereStacks);
	glEndList ();
}

void RigidBodyMotionSimulation::VOnMainLoop()
{
	while(!m_Finished)
	{
		HandleInput();
		VOnUpdate();
		VOnRender();
	}
}

void RigidBodyMotionSimulation::HandleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_Finished = true;
			}
			else if (event.key.keysym.sym == SDLK_f)
			{
				if (event.key.keysym.mod & KMOD_CTRL)
				{
					m_WindowManager->ToggleFullscreen();
				}
			}
			else if(event.key.keysym.sym == SDLK_w)
			{
				m_Camera.StrafeForward();
			}
			else if(event.key.keysym.sym == SDLK_a)
			{
				m_Camera.StrafeLeft();
			}
			else if(event.key.keysym.sym == SDLK_s)
			{
				m_Camera.StrafeBackward();
			}
			else if(event.key.keysym.sym == SDLK_d)
			{
				m_Camera.StrafeRight();
			}
			else if(event.key.keysym.sym == SDLK_i)
			{
				m_Camera.SetPos(m_Camera.GetPos().Add(Vector3(0,1,0)));
			}
			else if(event.key.keysym.sym == SDLK_k)
			{
				m_Camera.SetPos(m_Camera.GetPos().Add(Vector3(0,-1,0)));
			}
			else if(event.key.keysym.sym == SDLK_j)
			{
				m_Camera.SetRot(m_Camera.GetRot().Add(Vector3(0,-8,0)));
			}
			else if(event.key.keysym.sym == SDLK_l)
			{
				m_Camera.SetRot(m_Camera.GetRot().Add(Vector3(0,8,0)));
			}
			else if(event.key.keysym.sym == SDLK_c)
			{
				m_Particle->SetPos(Point3(m_Particle->GetPos().GetX() + 1, m_Particle->GetPos().GetY(), m_Particle->GetPos().GetZ()));
			}
			else if(event.key.keysym.sym == SDLK_v)
			{
				m_Particle->SetPos(Point3(m_Particle->GetPos().GetX(), m_Particle->GetPos().GetY() + 1, m_Particle->GetPos().GetZ()));
			}
			else if(event.key.keysym.sym == SDLK_b)
			{
				m_Particle->SetPos(Point3(m_Particle->GetPos().GetX(), m_Particle->GetPos().GetY(), m_Particle->GetPos().GetZ() + 1));
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if(event.key.keysym.sym == SDLK_w)
			{
				m_Camera.UnStrafeForward();
			}
			else if(event.key.keysym.sym == SDLK_a)
			{
				m_Camera.UnStrafeLeft();
			}
			else if(event.key.keysym.sym == SDLK_s)
			{
				m_Camera.UnStrafeBackward();
			}
			else if(event.key.keysym.sym == SDLK_d)
			{
				m_Camera.UnStrafeRight();
			}
		}
		else if(event.type == SDL_QUIT)
		{
			m_Finished = true;
		}
	}

	/*
	int x;
	int y;
	if(event.type == SDL_MOUSEMOTION)
	{
		SDL_MouseMotionEvent* castEvent = (SDL_MouseMotionEvent*)&event;
		x = castEvent->x;
		y = castEvent->y;
//		x = castEvent->xrel;
//		y = castEvent->yrel;
		float scaling = 0.004;
		m_Particle->SetPos(Point3(x*scaling, (m_WindowManager->GetScreenHeight()-y)*scaling, 1));
//		dynamx::Vector3 camRot = m_Camera.GetRot();
//		camRot.SetY(x + camRot.GetY());
//		camRot.SetX(y + camRot.GetX());
//		m_Camera.SetRot(camRot);
	}
*/
}

void RigidBodyMotionSimulation::CreateObjects()
{
	for(int i = 0 ; i < 0 ; i++)
	{
		RigidBodyPtr body(new RigidBody());
		body->SetMass(1);
	//	Point3 newPos(0,20,30);
	
		Point3 newPos(30,10,0);
		body->SetPos(newPos);

		Matrix3 inertiaTensor;
		inertiaTensor.SetBlockInertiaTensor(Vector3(1,1,1), 1);
		body->SetInertiaTensor(inertiaTensor);

//		body->LoadModel("../../media/models/torus.obj");
		body->LoadModel("../../media/models/cube.obj");

		//matrix3 orientation = body->getorientation();
		//orientation.createrotationmatrixaboutxaxis(45, &orientation);
		//body->setorientation(orientation);
		
		Quaternion orientation;
		Vector3 rotationVec(1,1,1);
		orientation.RotateByVector(rotationVec);
		body->SetOrientation(orientation);


		body->CalculateInternals();

		//m_CollisionDetector->AddAABB(body->GetAABB());

		/*
		if(i==0)
		{
			body->AddForceAtBodyPoint(Vector3(10,10, 0),Point3(0,0,0));
		}
		else
		{
			body->AddForceAtBodyPoint(Vector3(-10,-10, 0),Point3(0,0,0));
		}
		*/
		body->AddForceAtBodyPoint(Vector3(0,-90,0),Point3(0,0,0));

		//body->CalculateInternals();
		m_RigidBodies.push_back(body);
	}

	m_Plane = new CollisionPlane();
	m_Plane->SetPoint(Point3(0,0,0));
	m_Plane->SetNormal(Vector3(0,1,0));

	m_Particle = new Particle();
	m_Particle->SetPos(Point3(0,10,1));
	m_Particle->SetVel(Vector3(0,-10,0));

	/*
	m_Triangle_0->SetPoint( Point3(1.0f,3.0f,0.0f), 0 );
	m_Triangle_0->SetPoint( Point3(2.0f,1.0f,0.0f), 1 );
	m_Triangle_0->SetPoint( Point3(2.0f,2.0f,0.0f), 2 );
	*/

	m_Triangle_0->SetPoint( Point3(0.3f,0.3f,0.0f), 0 );
	m_Triangle_0->SetPoint( Point3(1.3f,1.3f,0.0f), 1 );
	m_Triangle_0->SetPoint( Point3(2.3f,0.3f,0.0f), 2 );
	m_Triangle_0->CreateEdges();

//	m_Contact = new Contact();
}

void RigidBodyMotionSimulation::DoCamera()
{
	glRotatef(m_Camera.GetRot().GetX(),1.0,0.0,0.0);
	glRotatef(m_Camera.GetRot().GetY(),0.0,1.0,0.0);
	glRotatef(m_Camera.GetRot().GetZ(),0.0,0.0,1.0);

	GLfloat xtrans = -(m_Camera.GetPos().GetX());
	GLfloat ytrans = -(m_Camera.GetPos().GetY());
	GLfloat ztrans = -(m_Camera.GetPos().GetZ());
	glTranslatef(xtrans, ytrans, ztrans);
}


void RigidBodyMotionSimulation::VOnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DoCamera();

	list<RigidBodyPtr>::iterator it, itEnd;
	for(it = m_RigidBodies.begin(), itEnd = m_RigidBodies.end();
			it != itEnd ;
			it++)
	{
		if(isColliding)
		{
			glColor3f(1.0,0,0);
		}
		else
		{
			glColor3f(0,1,0);
		}
		(*it)->VDraw();
	}

	glPushMatrix();
	if(isColliding)
	{
		glColor3f(1.0,0.0,0);
	}
	else
	{
		glColor3f(0.0,1.0,0);
	}
	m_Triangle_0->VDraw();
	glPopMatrix();

	if(isColliding)
	{
		glPushMatrix();
		glColor3f(0.1,0.9,1);
		glTranslatef(m_Contact->GetClosestPoint().GetX(),
					m_Contact->GetClosestPoint().GetY(),
					m_Contact->GetClosestPoint().GetZ());
		glCallList(m_NormalSphereList);

		//Now draw arrow for normal
		glBegin(GL_LINES);
				glPushMatrix();
				glVertex3f(0, 
						0,
						0);
				glVertex3f(m_Contact->GetCollisionNormal().GetX(), 
						m_Contact->GetCollisionNormal().GetY(),
						m_Contact->GetCollisionNormal().GetZ());
				glPopMatrix();	
		glEnd();
		glPopMatrix();
	}

	/*
	glPushMatrix();
		glTranslatef(m_Particle->GetPos().GetX(),
					m_Particle->GetPos().GetY(),
					m_Particle->GetPos().GetZ());
		glCallList(m_NormalSphereList);
	glPopMatrix();
	*/

	/*
	//line to closest feature
	glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(m_Particle->GetPos().GetX(),
					m_Particle->GetPos().GetY(),
					m_Particle->GetPos().GetZ());
		Point3 closestFeaturePos = m_Triangle_0->GetClosestFeaturePos();
		glVertex3f(closestFeaturePos.GetX(),
					closestFeaturePos.GetY(),
					closestFeaturePos.GetZ());
		glEnd();
	glPopMatrix();
	*/

	m_Plane->VDraw();

	SDL_GL_SwapBuffers();
}

void RigidBodyMotionSimulation::InitGL()
{
	SetupLighting();
	glShadeModel( GL_SMOOTH );
	//glClearColor(0.1, 0.1, 0.5, 0.0);
	glClearDepth( 10.0f );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glClearAccum(0.1, 0.1, 0.8, 0.0);

	glViewport(0, 0, m_WindowManager->GetScreenWidth(), m_WindowManager->GetScreenWidth());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(float)m_WindowManager->GetScreenWidth()/(float)m_WindowManager->GetScreenWidth(),0.1,600);
	glEnable(GL_COLOR_MATERIAL);
}

void RigidBodyMotionSimulation::SetupLighting()
{
	GLfloat WHITE_LIGHT[] = {0.1, 0.9, 0.2, 0.0};
	GLfloat LIGHT_POSITION[4] = { 0.0, 5.0, 10.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE_LIGHT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE_LIGHT);
	glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE_LIGHT);
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);
}

void RigidBodyMotionSimulation::VOnUpdate()
{
//	m_FpsTimer->Start();

	unsigned startTicks = SDL_GetTicks();

	m_Camera.UpdatePosAndRot();

	float timestep = 1.0f / 60.0f; //TODO : Adaptive timestep.

	/*
	list<RigidBodyPtr>::iterator it, itEnd;
	for(it = m_RigidBodies.begin(), itEnd = m_RigidBodies.end();
			it != itEnd ;
			it++)
	{
		(*it)->Integrate(timestep);

		isColliding = false;
		if(m_NarrowPhaseCollisionDetector->RigidBodyAndPlane((*it), (*m_Plane), m_Contact))
		{
			isColliding = true;
		}

		if((*it)->GetPos().GetY() < -10)
		{
			(*it)->AddForceAtBodyPoint(Vector3(0,180,0),Point3(0,0,0));
		}
		else if((*it)->GetPos().GetY() > 10)
		{
			(*it)->AddForceAtBodyPoint(Vector3(0,-180,0),Point3(0,0,0));
		}

		//TODO: Draw contact.
	}
	*/

	m_Particle->Integrate(timestep);

	m_Triangle_0->SetGlobalPos(m_Particle->GetPos());

	isColliding = false;
	m_Triangle_0->SetColliding(false);
//	Contact contact;
	if(m_NarrowPhaseCollisionDetector->TriangleAndPlane((*m_Triangle_0), (*m_Plane), m_Contact))
	{
		m_Triangle_0->SetColliding(true);
		isColliding = true;
	}

	if(m_Particle->GetPos().GetY() < -10)
	{
		m_Particle->SetVel(Vector3(0,10,0));
	}
	if(m_Particle->GetPos().GetY() > 10)
	{
		m_Particle->SetVel(Vector3(0,-10,0));
	}
	/*

//	m_CollisionDetector->CheckForCollisions();
//
	bool found = false;
	Point3 closestPoint = m_Triangle_0->GetPoint(0);
	real closestD = FLT_MAX;
	int closestI = -1;
	//Narrowphase Collision Detection
	//Check points first
	for(int i = 0 ; i < 3 ; i++)
	{
		if(m_VoronoiChecker->PointAndPoint(i, m_Particle->GetPos(), (*m_Triangle_0)))
		{
			Point3 point = m_Triangle_0->GetPoint(i);
			real d = m_NarrowPhaseCollisionDetector->PointAndPoint(point, m_Particle->GetPos());
			if(d < closestD)
			{
				closestPoint = point;
				closestI = i;
				closestD = d;
			}
			found = true;
			break;
		}
	}
	//Check edges if not found in vertices.
	if(!found)
	{
		for(int i = 0 ; i < 3 ; i++)
		{
			if(m_VoronoiChecker->PointAndEdge(i, m_Particle->GetPos(), (*m_Triangle_0)))
			{
				Point3 point = m_Triangle_0->GetPoint(i);
				Edge edge = m_Triangle_0->GetEdge(i);
				Point3 result;
				real d = m_NarrowPhaseCollisionDetector->PointAndEdge(m_Particle->GetPos(), edge, &result);
				if(d < closestD)
				{
					closestPoint = result;
					closestI = i+3;
					closestD = d;
				}
				found = true;
				break;
			}
		}
	}
	//Check plane since not point or edge.
	if(!found)
	{
		//Check plane
		CollisionPlane plane = m_Triangle_0->GetPlane();	
		Point3 result;
		real d = m_NarrowPhaseCollisionDetector->PointAndPlane(m_Particle->GetPos(), plane, &result);

		if(d < closestD)
		{
			closestPoint = result;
			closestI = 6;
			closestD = d;
		}
	}

	m_Triangle_0->SetClosestFeature(closestI, closestPoint);
	cout<<"closestI is :" <<closestI<<endl;
	cout<<"closestD is :" <<closestD<<endl;
//		Contact contact;
//		m_NarrowPhaseCollisionDetector->RigidBodyAndPlane( (*it), (*m_Plane), &contact);

*/

	unsigned endTicks = SDL_GetTicks();
	if( ( CAPFPS == true ) && ( (endTicks - startTicks) < (1000 / FPS) ) )
	{
		//Sleep the remaining frame time
		SDL_Delay( ( 1000 / FPS ) - (endTicks-startTicks) );
	}

/*
	//Cap the FPS
	if( ( CAPFPS == true ) && ( m_FpsTimer->GetTicks() < (1000 / FPS) ) )
	{
		//Sleep the remaining frame time 
		SDL_Delay( ( 1000 / FPS ) - m_FpsTimer->GetTicks() );
	}
	*/
}

