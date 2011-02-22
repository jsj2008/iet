#include "RigidBodyMotionSimulation.hpp"

#include <dynamx/Vector3.hpp>

#include <iostream>
using namespace std;

const char* PARTICLE_TEX_PATH = "../../media/tex/particle_texture.tga";

RigidBodyMotionSimulation::RigidBodyMotionSimulation()
	:
		Simulation()
{
}

RigidBodyMotionSimulation::~RigidBodyMotionSimulation()
{
}

void RigidBodyMotionSimulation::VOnInit()
{
	Simulation::VOnInit();

	m_Font = new FTGLPixmapFont ("../../media/font/Abduction.ttf");

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
	RigidBodyPtr body(new RigidBody());
	body->SetMass(1);
//	Point3 newPos(0,20,30);
	Point3 newPos(0,0,-80);
	body->SetPos(newPos);

	Matrix3 inertiaTensor;
	inertiaTensor.SetBlockInertiaTensor(Vector3(1,1,1), 1);
	body->SetInertiaTensor(inertiaTensor);

	//matrix3 orientation = body->getorientation();
	//orientation.createrotationmatrixaboutxaxis(45, &orientation);
	//body->setorientation(orientation);
	
	Quaternion orientation;
	Vector3 rotationVec(1,1,1);
	orientation.RotateByVector(rotationVec);
	body->SetOrientation(orientation);
	/*
	//orientation.createrotationmatrixaboutxaxis(45, &orientation);
	//body->setorientation(orientation);
	Vector3 testVel(0,10,0);
	body->SetLinearVel(testVel);
	Vector3 testAngularVel(1.1,1.1,1.1);
	body->SetAngularVel(testAngularVel);
	*/

	body->CalculateInternals();

	body->AddForceAtBodyPoint(Vector3(0,-9,0),Point3(0,0,0));

	//body->CalculateInternals();
	m_RigidBodies.push_back(body);
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

	stringstream out;
	out<<"Pos is :[";
	out<<m_RigidBodies.front()->GetPos().GetX()<<",";
	out<<m_RigidBodies.front()->GetPos().GetY()<<",";
	out<<m_RigidBodies.front()->GetPos().GetZ()<<"]";

	m_Font->Render(out.str().c_str());

	SDL_GL_SwapBuffers();
}

void RigidBodyMotionSimulation::InitGL()
{
	SetupLighting();
	glShadeModel( GL_SMOOTH );
	glClearColor(0.1, 0.1, 0.5, 0.0);
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
	GLfloat WHITE_LIGHT[] = {1.0, 1.0, 1.0, 1.0};
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
	m_FpsTimer.Start();

	m_Camera.UpdatePosAndRot();

	float timestep = 1.0f / 60.0f; //TODO : Adaptive timestep.

	list<RigidBodyPtr>::iterator it, itEnd;
	for(it = m_RigidBodies.begin(), itEnd = m_RigidBodies.end();
			it != itEnd ;
			it++)
	{
		(*it)->Integrate(timestep);
	}

	//Cap the FPS
	if( ( CAPFPS == true ) && ( m_FpsTimer.GetTicks() < (1000 / FPS) ) )
	{
		//Sleep the remaining frame time 
		SDL_Delay( ( 1000 / FPS ) - m_FpsTimer.GetTicks() );
	}
}
