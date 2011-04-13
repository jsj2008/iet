#include "RigidBodyMotionSimulation.hpp"

#include <dynamx/Vector3.hpp>

#include <iostream>
using namespace std;

const char* PARTICLE_TEX_PATH = "../../media/tex/particle_texture.tga";

RigidBodyMotionSimulation::RigidBodyMotionSimulation()
	:
		Simulation()
{
//	m_CollisionDetector = new SweepAndPruneCollisionDetector();
	//m_FpsTimer = new FpsTimer();
	m_NarrowPhaseCollisionDetector = new CollisionDetector();
	m_Plane = 0;
	m_Quadric = gluNewQuadric();
}

RigidBodyMotionSimulation::~RigidBodyMotionSimulation()
{
//	delete m_CollisionDetector;
	delete m_NarrowPhaseCollisionDetector;
	delete m_Plane;
}

void RigidBodyMotionSimulation::VOnInit()
{
	Simulation::VOnInit();


	float Radius = 1.0;
	float SphereStacks = 30;
	float SphereSlices = 30;
	m_NormalSphereList = glGenLists(1);
	glNewList(m_NormalSphereList, GL_COMPILE);
		gluSphere( m_Quadric, Radius, SphereSlices, SphereStacks);
	glEndList ();


//	m_Layout = new FTSimpleLayout();

//	m_Layout->SetFont(m_Font);

	CreateObjects();

	InitGL();

	m_Camera.SetPos(dynamx::Point3(0,10,40));
	m_Camera.SetRot(dynamx::Vector3(0,0,0));

	m_Finished = false;
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
		x = castEvent->xrel;
		y = castEvent->yrel;
		dynamx::Vector3 camRot = m_Camera.GetRot();
		camRot.SetY(x + camRot.GetY());
		camRot.SetX(y + camRot.GetX());
		m_Camera.SetRot(camRot);
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
	
		Point3 newPos(i,i,-80);
		body->SetPos(newPos);

		Matrix3 inertiaTensor;
		inertiaTensor.SetBlockInertiaTensor(Vector3(1,1,1), 1);
		body->SetInertiaTensor(inertiaTensor);

		body->LoadModel("../../media/models/torus.obj");
//		body->LoadModel("../../media/models/cube.obj");

		//matrix3 orientation = body->getorientation();
		//orientation.createrotationmatrixaboutxaxis(45, &orientation);
		//body->setorientation(orientation);
		
		Quaternion orientation;
		Vector3 rotationVec(1,1,1);
		orientation.RotateByVector(rotationVec);
		body->SetOrientation(orientation);


		body->CalculateInternals();

		//m_CollisionDetector->AddAABB(body->GetAABB());

		if(i==0)
		{
			body->AddForceAtBodyPoint(Vector3(10,10, 0),Point3(0,0,0));
		}
		else
		{
			body->AddForceAtBodyPoint(Vector3(-10,-10, 0),Point3(0,0,0));
		}
//		body->AddForceAtBodyPoint(Vector3(0,-9,0),Point3(100,0,0));

		//body->CalculateInternals();
		m_RigidBodies.push_back(body);
	}

	m_Particle = new Particle();
	m_Particle->SetPos(Point3(0,10,0));
	m_Particle->SetVel(Point3(1,-10,0));

	m_Plane = new CollisionPlane();
	m_Plane->SetPoint(Point3(0,0,0));
	m_Plane->SetNormal(Vector3(0,1,0));
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
		(*it)->VDraw();
	}

	m_Plane->VDraw();

	//Draw Particles
	glPushMatrix();
		if(particleColliding)
		{
			glColor3f(1.0, 0.0, 0.0);
		}
		else
		{
			glColor3f(0.0, 1.0, 0.0);
		}
		//cout<<"x is : "<<m_Particle->GetPos().GetX()<<endl;
		//cout<<"y is : "<<m_Particle->GetPos().GetY()<<endl;
		//cout<<"z is : "<<m_Particle->GetPos().GetZ()<<endl;
		glTranslatef(m_Particle->GetPos().GetX(),
					m_Particle->GetPos().GetY(),
					m_Particle->GetPos().GetZ());
		glCallList(m_NormalSphereList);
	glPopMatrix();

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

	list<RigidBodyPtr>::iterator it, itEnd;
	for(it = m_RigidBodies.begin(), itEnd = m_RigidBodies.end();
			it != itEnd ;
			it++)
	{
		(*it)->Integrate(timestep);



		//TODO: Draw contact.
	}

//	m_CollisionDetector->CheckForCollisions();
	//Narrowphase Collision Detection
	particleColliding = false;
	real d;
	if(m_NarrowPhaseCollisionDetector->PointAndPlane(m_Particle->GetPos(), (*m_Plane), &d))
	{
		//cout <<"Collision!"<<endl;
		particleColliding = true;
	}
	cout<<"distance from plane is : "<<d<<endl;
//		Contact contact;
//		m_NarrowPhaseCollisionDetector->RigidBodyAndPlane( (*it), (*m_Plane), &contact);

	unsigned endTicks = SDL_GetTicks();
	if( ( CAPFPS == true ) && ( (endTicks - startTicks) < (1000 / FPS) ) )
	{
		//Sleep the remaining frame time
		SDL_Delay( ( 1000 / FPS ) - (endTicks-startTicks) );
	}

	m_Particle->Integrate(timestep);

	if(m_Particle->GetPos().GetY() < -10)
	{
		m_Particle->SetVel(Vector3(1,10,0));
	}
	else if(m_Particle->GetPos().GetY() > 10)
	{
		m_Particle->SetVel(Vector3(1,-10,0));
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

