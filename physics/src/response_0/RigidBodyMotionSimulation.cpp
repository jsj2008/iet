#include "RigidBodyMotionSimulation.hpp"

#include <dynamx/Vector3.hpp>

#include <iostream>
using namespace std;

const char* PARTICLE_TEX_PATH = "../../media/tex/particle_texture.tga";

RigidBodyMotionSimulation::RigidBodyMotionSimulation()
	:
		Simulation(),
		m_Particle(0),
		m_Quadric(0),
		m_NormalSphereList(0),
		isColliding(0)
{
//	m_CollisionDetector = new SweepAndPruneCollisionDetector();
	//m_FpsTimer = new FpsTimer();
//	m_NarrowPhaseCollisionDetector = new CollisionDetector();

	m_NarrowPhaseCollisionDetector = shared_ptr<CollisionDetector>(new CollisionDetector());
	m_ContactResolver = shared_ptr<ContactResolver>(new ContactResolver());
	m_Quadric = gluNewQuadric();
	m_Font = new FTGLPixmapFont ("../../media/font/Abduction.ttf");
}

RigidBodyMotionSimulation::~RigidBodyMotionSimulation()
{
//	delete m_CollisionDetector;
//	delete m_NarrowPhaseCollisionDetector;
//	delete m_Contact;
	
	delete m_Font;
	gluDeleteQuadric(m_Quadric);
}

void RigidBodyMotionSimulation::VOnInit()
{
	Simulation::VOnInit();

	InitGL();

	// If something went wrong, bail out.
	if(m_Font->Error())
	{
		assert(0 && "Font is wrong");
	}

	// Set the font size and render a small text.
	m_Font->FaceSize(18);
//	m_Layout = new FTSimpleLayout();

//	m_Layout->SetFont(m_Font);

	CreateObjects();

	m_Camera.SetPos(dynamx::Point3(0,10,40));
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
	for(int i = 0 ; i < 1 ; i++)
	{
		RigidBodyPtr body(new RigidBody());
		body->SetMass(1);
	//	Point3 newPos(0,20,30);
	
		Point3 newPos(-i*10,4,-i*10);
		body->SetPos(newPos);

		Matrix3 inertiaTensor;
		inertiaTensor.SetBlockInertiaTensor(Vector3(1.0,1.0,1.0), body->GetMass());
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
		//body->AddForceAtBodyPoint(Vector3(0,-90,0),Point3(0.1,0.2,0));
//		body->AddForceAtBodyPoint(Vector3(0,-99.8,0),Point3(0.0,0.0,0.0));

//		body->SetLinearVel(Vector3(0,-9,0));

		//body->CalculateInternals();
		m_RigidBodies.push_back(body);
	}

	m_Plane = shared_ptr<CollisionPlane>(new CollisionPlane());
	m_Plane->SetPoint(Point3(0,0,0));
	m_Plane->SetNormal(Vector3(0,1,0));

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

void RigidBodyMotionSimulation::RenderBodies()
{
	list<RigidBodyPtr>::iterator it, itEnd;
	for(it = m_RigidBodies.begin(), itEnd = m_RigidBodies.end();
			it != itEnd ;
			it++)
	{
		/*
		if(isColliding)
		{
			glColor3f(1.0,0,0);
		}
		else
		{
			glColor3f(0,1,0);
		}
		*/
		glColor3f(0,1,0);
		(*it)->VDraw();
	}
}

void RigidBodyMotionSimulation::VOnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DoCamera();

	RenderBodies();

	vector<ContactPtr>::iterator it, itEnd;
	for(it = m_Contacts.begin(), itEnd = m_Contacts.end();
			it != itEnd ;
			it++)
	{
		glPushMatrix();
		glColor3f(0.1,0.9,1);
		glTranslatef((*it)->GetClosestPoint().GetX(),
					(*it)->GetClosestPoint().GetY(),
					(*it)->GetClosestPoint().GetZ());
		glCallList(m_NormalSphereList);

		//Now draw arrow for normal
		glBegin(GL_LINES);
				glPushMatrix();
				glVertex3f(0, 
						0,
						0);
				glVertex3f((*it)->GetCollisionNormal().GetX(), 
						(*it)->GetCollisionNormal().GetY(),
						(*it)->GetCollisionNormal().GetZ());
				glPopMatrix();	
		glEnd();
		glPopMatrix();
	}


	m_Plane->VDraw();
	
	stringstream out;
	out<<"nContacts is : "<<m_Contacts.size()<<endl;

	m_Font->Render(out.str().c_str());

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
//	float timestep = 1.0f / 120.0f; //TODO : Adaptive timestep.

	m_Contacts.clear();
//	vector<ContactPtr> contacts;
	list<RigidBodyPtr>::iterator it, itEnd;
	for(it = m_RigidBodies.begin(), itEnd = m_RigidBodies.end();
			it != itEnd ;
			it++)
	{
		(*it)->AddForceAtBodyPoint(Vector3(0,-9.8,0),Point3(0.0,0.0,0.0));
//		(*it)->SetLinearVel((*it)->GetLinearVel().Subtract(Vector3(0,0.1,0)));

		(*it)->Integrate(timestep);

//		m_Contact = new Contact();
		
		int maxTries = 1;
		int i = 0;
		do
		{
			i++;
			if(i > maxTries)
			{
				break;
			}
			isColliding = false;
//			ContactPtr contact(new Contact());
			shared_ptr<vector<ContactPtr> > contacts(new vector<ContactPtr>());
			if(m_NarrowPhaseCollisionDetector->RigidBodyAndPlane((*it), m_Plane, contacts))
			{
				isColliding = true;
//				m_Contacts.push_back(contact);
//				m_ContactResolver->ResolveContacts(m_Contacts, timestep);
//				m_ContactResolver->ResolveContacts(*(contacts.get()), timestep);
				while( ! contacts->empty() )
				{
					m_Contacts.push_back( contacts->back() );
					contacts->pop_back();
				}
			}
		}
		while(isColliding);


		/*
		if((*it)->GetPos().GetY() < -10)
		{
			(*it)->AddForceAtBodyPoint(Vector3(0,180,0),Point3(0,0,0));
		}
		else if((*it)->GetPos().GetY() > 10)
		{
			(*it)->AddForceAtBodyPoint(Vector3(0,-180,0),Point3(0,0,0));
		}
		*/

		//TODO: Draw contact.
	}

	m_ContactResolver->ResolveContacts(m_Contacts, timestep);

//	m_CollisionDetector->CheckForCollisions();
	//Narrowphase Collision Detection
	/*
	particleColliding = false;
	real d;
	if(m_NarrowPhaseCollisionDetector->PointAndPlane(m_Particle->GetPos(), (*m_Plane), &d))
	{
		//cout <<"Collision!"<<endl;
		particleColliding = true;
	}
	cout<<"distance from plane is : "<<d<<endl;
	*/
//		Contact contact;
//		m_NarrowPhaseCollisionDetector->RigidBodyAndPlane( (*it), (*m_Plane), &contact);


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

