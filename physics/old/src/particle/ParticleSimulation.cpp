#include "ParticleSimulation.hpp"

#include <dynamx/Vector3.hpp>

#include <iostream>
using namespace std;

const char* PARTICLE_TEX_PATH = "../../media/tex/particle_texture.tga";

ParticleSimulation::ParticleSimulation()
	:
		Simulation()
{
	m_Quadric = gluNewQuadric();
	gluQuadricTexture(m_Quadric, true);
	m_PlaneHalfSize = 40.f;
	m_NParticles = 3;
	m_MaxParticles = 100;
	m_NColours = 300;
	m_Gravity = false;
	m_Attraction = false;
	m_IsSpawning = true;

	m_GravityForceGen = new dynamx::ParticleGravityForceGenerator(dynamx::Vector3(0,-9.8,0));
	m_DragForceGen = new dynamx::ParticleDragForceGenerator(0.1,0.1);
	m_AttractionForceGen = new dynamx::ParticleAttractionForceGenerator( dynamx::Point3(m_PlaneHalfSize,m_PlaneHalfSize,m_PlaneHalfSize),1000.1);
	m_SpawnPos.Set(m_PlaneHalfSize,m_PlaneHalfSize,m_PlaneHalfSize);
}

ParticleSimulation::~ParticleSimulation()
{
	gluDeleteQuadric(m_Quadric);
	delete m_GravityForceGen;
	delete m_DragForceGen;
	delete m_AttractionForceGen;
}

void ParticleSimulation::VOnInit()
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

	m_ParticleTexId = TextureLoader::GetInstance().GetNextTextureId();
	TextureLoader::GetInstance().LoadTexture(PARTICLE_TEX_PATH, m_ParticleTexId);

	float Radius = 0.5;
	float SphereStacks = 30;
	float SphereSlices = 30;
	m_NormalSphereList = glGenLists(1);
	glNewList(m_NormalSphereList, GL_COMPILE);
		gluSphere( m_Quadric, Radius, SphereSlices, SphereStacks);
	glEndList ();

	m_PlaneList=glGenLists(1);
	glNewList(m_PlaneList, GL_COMPILE);
		glBegin(GL_LINE_LOOP);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_PlaneHalfSize, 0, -m_PlaneHalfSize);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_PlaneHalfSize, 0,  m_PlaneHalfSize);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( m_PlaneHalfSize, 0,  m_PlaneHalfSize);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( m_PlaneHalfSize, 0, -m_PlaneHalfSize);
		glEnd();
	glEndList ();

	srand(time(NULL));

	m_Colours = new Colour[m_NColours];
	for(int i = 0 ; i < m_NColours ; i++)
	{
		m_Colours[i].r = (rand() % 1) * 0.321;
		m_Colours[i].g = (rand() % 2) * 0.348;
		m_Colours[i].b = (rand() % 3) * 0.291;
	}
	m_PlaneColour.r = 0.2;
	m_PlaneColour.g = 0.4;
	m_PlaneColour.b = 0.4;

	InitGL();

	m_Camera.SetPos(dynamx::Point3(0,10,40));

	m_Finished = false;

	m_SpawnTimer.Start();
}

void ParticleSimulation::VOnMainLoop()
{
	while(!m_Finished)
	{
		HandleInput();
		VOnUpdate();
		VOnRender();
	}
}

void ParticleSimulation::HandleInput()
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
			else if(event.key.keysym.sym == SDLK_g)
			{
				ToggleGravity();
			}
			else if(event.key.keysym.sym == SDLK_h)
			{
				ToggleAttraction();
			}
			else if(event.key.keysym.sym == SDLK_m)
			{
				m_MaxParticles += 1000;
			}
			else if(event.key.keysym.sym == SDLK_v)
			{
				m_IsSpawning = ! m_IsSpawning;
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

	int x;
	int y;
	if(event.type == SDL_MOUSEMOTION)
	{
		SDL_MouseMotionEvent* castEvent = (SDL_MouseMotionEvent*)&event;
		x = castEvent->xrel;
		y = castEvent->yrel;
		dynamx::Vector3 camRot = m_Camera.GetRot();
		camRot.SetX(y + camRot.GetX());
		camRot.SetY(x + camRot.GetY());
		m_Camera.SetRot(camRot);
	}
}

void ParticleSimulation::CreateObjects()
{

	for(int i = 0 ; i < 6 ; i++)
	{
		PlanePtr plane(new dynamx::Plane());
		if(i==0)
		{
			//Bottom
			plane->SetPos(dynamx::Point3(m_PlaneHalfSize,0,m_PlaneHalfSize));
			plane->SetNormal(dynamx::Vector3(0,1,0));
		}
		else if(i==1)
		{
			//Back
			plane->SetPos(dynamx::Point3(m_PlaneHalfSize,m_PlaneHalfSize,0));
			plane->SetNormal(dynamx::Vector3(0,0,1));
		}
		else if(i==2)
		{
			//Left
			plane->SetPos(dynamx::Point3(0,m_PlaneHalfSize,m_PlaneHalfSize));
			plane->SetNormal(dynamx::Vector3(1,0,0));
		}
		else if(i==3)
		{
			//Top
			plane->SetPos(dynamx::Point3(m_PlaneHalfSize,(m_PlaneHalfSize*2),m_PlaneHalfSize));
			plane->SetNormal(dynamx::Vector3(0,-1,0));
		}
		else if(i==4)
		{
			//Right
			plane->SetPos(dynamx::Point3((m_PlaneHalfSize*2),m_PlaneHalfSize,m_PlaneHalfSize));
			plane->SetNormal(dynamx::Vector3(-1,0,0));
		}
		else if(i==5)
		{
			//Front
			plane->SetPos(dynamx::Point3(m_PlaneHalfSize, m_PlaneHalfSize,(m_PlaneHalfSize*2)));
			plane->SetNormal(dynamx::Vector3(0,0,-1));
		}
		m_Planes.push_back(plane);
	}

	srand(time(NULL));

	float thetaDiff = PI/8;
	float theta = 0;
	float spiralRadius = 4.f;

	for(int i = 0; i < m_NParticles; i++)
	{
		SpawnParticle();
	}
	
}

void ParticleSimulation::DoCamera()
{
	glRotatef(m_Camera.GetRot().GetX(),1.0,0.0,0.0);
	glRotatef(m_Camera.GetRot().GetY(),0.0,1.0,0.0);
	glRotatef(m_Camera.GetRot().GetZ(),0.0,0.0,1.0);

	GLfloat xtrans = -(m_Camera.GetPos().GetX());
	GLfloat ytrans = -(m_Camera.GetPos().GetY());
	GLfloat ztrans = -(m_Camera.GetPos().GetZ());
	glTranslatef(xtrans, ytrans, ztrans);
}


void ParticleSimulation::VOnRenderParticles()
{
	int i = 0;
	list<ParticlePtr>::iterator it, itEnd;
	for(it = m_Particles.begin(), itEnd = m_Particles.end();
			it != itEnd ;
			it++)
	{
//		Colour colour = m_Colours[i%m_NColours];

		Colour colour = ChooseColour((*it));

		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, m_ParticleTexId );

		glPushMatrix();
			glColor3f(colour.r, colour.g, colour.b);
			glTranslatef((*it)->GetPos().GetX(), 
							(*it)->GetPos().GetY(), 
							(*it)->GetPos().GetZ());
			glCallList(m_NormalSphereList);
		glPopMatrix();

		glDisable( GL_TEXTURE_2D );
		i++;
	}
}

void ParticleSimulation::VOnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DoCamera();

	VOnRenderParticles();

	int i = 0;
	vector<PlanePtr>::iterator it, itEnd;
	for(it = m_Planes.begin(), itEnd = m_Planes.end();
			it != itEnd ;
			it++)
	{
		glPushMatrix();
			glColor3f(m_PlaneColour.r, m_PlaneColour.g, m_PlaneColour.b);

			glTranslatef((*it)->GetPos().GetX(), 
					(*it)->GetPos().GetY(), 
					(*it)->GetPos().GetZ());
			if(i==1)
			{
				glRotatef(90, 1, 0, 0);
			}
			else if(i==2)
			{
				glRotatef(90, 0, 0, 1);
			}
			else if(i==4)
			{
				glRotatef(90, 0, 0, 1);
			}
			else if(i==5)
			{
				glRotatef(90, 1, 0, 0);
			}
			glCallList(m_PlaneList);
		glPopMatrix();
		i++;
	}

	stringstream out;
	out<<"Number of particles : "<<m_Particles.size();
	out<<" Gravity : ";
	if(m_Gravity)
	{
		out<<"On";
	}
	else
	{
		out<<"Off";
	}
	out<<" Attraction : ";
	if(m_Attraction)
	{
		out<<"On";
	}
	else
	{
		out<<"Off";
	}


	m_Font->Render(out.str().c_str());
//	m_Layout->Render(out.str().c_str());


	//Draw particle at attraction centre
	if(m_Attraction)
	{
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(m_PlaneHalfSize, 
				m_PlaneHalfSize, 
				m_PlaneHalfSize);
		glScalef(10, 10, 10);
		glCallList(m_NormalSphereList);
		glPopMatrix();
	}

	SDL_GL_SwapBuffers();
}

void ParticleSimulation::InitGL()
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

void ParticleSimulation::SetupLighting()
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

void ParticleSimulation::VOnUpdate()
{
	m_FpsTimer.Start();

	m_Camera.UpdatePosAndRot();

	float timestep = 1.0f / 60.0f; //TODO : Adaptive timestep.

	CalculateForces(timestep);

	list<ParticlePtr>::iterator particleIt, particleItEnd;
	for(particleIt = m_Particles.begin(), particleItEnd = m_Particles.end();
			particleIt != particleItEnd ; 
			particleIt++)
	{
		(*particleIt)->Integrate(timestep);
	}
	
	CollisionDetection();	

	if(m_IsSpawning)
	{
		if(m_SpawnTimer.GetTicks() > SPAWN_TIME)
		{
			if(m_Particles.size() >= m_MaxParticles)
			{
				RemoveParticle();
			}
			SpawnParticle();
			m_SpawnTimer.Start();
		}
	}

	//Cap the FPS
	if( ( CAPFPS == true ) && ( m_FpsTimer.GetTicks() < (1000 / FPS) ) )
	{
		//Sleep the remaining frame time 
		SDL_Delay( ( 1000 / FPS ) - m_FpsTimer.GetTicks() );
	}


}

void ParticleSimulation::CollisionDetection()
{
	float epsilon = 0.01;

	list<ParticlePtr>::iterator particleIt, particleItEnd;
	for(particleIt = m_Particles.begin(), particleItEnd = m_Particles.end();
			particleIt != particleItEnd ; 
			particleIt++)
	{
		vector<PlanePtr>::iterator it, itEnd;
		for(it = m_Planes.begin(), itEnd = m_Planes.end() ; it != itEnd ; it++)
		{
			dynamx::Vector3 particlePos((*particleIt)->GetPos());
			dynamx::Vector3 planePos((*it)->GetPos());
			dynamx::Vector3 relPos = particlePos.Subtract(planePos);
			if((relPos.DotProduct((*it)->GetNormal()) < epsilon) &&
					((*it)->GetNormal().DotProduct((*particleIt)->GetVel()) < epsilon))
			{
				//Do post processing method
				//Move particle above plane by the amount it is penetrating and add epsilon.
				dynamx::Vector3 deltaPos = ((*it)->GetNormal().Multiply(relPos.DotProduct((*it)->GetNormal()))).Multiply(-1);
				(*particleIt)->SetPos((*particleIt)->GetPos().Add(deltaPos.Multiply(1+epsilon)));


				//Do Collision response.
				float r = 1.0; //Coeff of restitution
				dynamx::Vector3 initialVel = (*particleIt)->GetVel();
				float velMag = initialVel.Magnitude();
				initialVel.Normalize();
				dynamx::Vector3 contactNormal = (*it)->GetNormal();
				//Get vel in normal dir
				dynamx::Vector3 velNormal = (contactNormal.Multiply(initialVel.DotProduct(contactNormal))); 
				dynamx::Vector3 velTangential = initialVel.Subtract(velNormal); 
				dynamx::Vector3 postCollisionVel = (velTangential.Subtract(velNormal.Multiply(r))).Multiply(velMag);
				
				stringstream out;
				out<<"contactNormal :"<<endl;
				out<<"x is :"<<contactNormal.GetX()<<endl;
				out<<"y is :"<<contactNormal.GetY()<<endl;
				out<<"z is :"<<contactNormal.GetZ()<<endl;
				out<<"initialVel :"<<endl;
				out<<"x is :"<<initialVel.GetX()<<endl;
				out<<"y is :"<<initialVel.GetY()<<endl;
				out<<"z is :"<<initialVel.GetZ()<<endl;
				out<<"velNormal :"<<endl;
				out<<"x is :"<<velNormal.GetX()<<endl;
				out<<"y is :"<<velNormal.GetY()<<endl;
				out<<"z is :"<<velNormal.GetZ()<<endl;
				out<<"velTangential :"<<endl;
				out<<"x is :"<<velTangential.GetX()<<endl;
				out<<"y is :"<<velTangential.GetY()<<endl;
				out<<"z is :"<<velTangential.GetZ()<<endl;
				out<<"postCollisionVel :"<<endl;
				out<<"x is :"<<postCollisionVel.GetX()<<endl;
				out<<"y is :"<<postCollisionVel.GetY()<<endl;
				out<<"z is :"<<postCollisionVel.GetZ()<<endl;
				//cout<<out.str();

				(*particleIt)->SetVel(postCollisionVel);

			}
		}
	}
}

void ParticleSimulation::CalculateForces(float timestep)
{
	m_ParticleForceRegistry.Update(timestep);
}

Colour ParticleSimulation::ChooseColour(ParticlePtr particle)
{
	Colour red;
	red.r = 1.0;
   	red.g = 0.0;
   	red.b = 0.0;
	Colour green;
	green.r = 0.0;
   	green.g = 1.0;
   	green.b = 0.0;

	float cutoff = 10.0;

	if(particle->GetVel().Magnitude() > cutoff)
	{
		return red;
	}
	else
	{
		return green;
	}
}

void ParticleSimulation::SpawnParticle()
{
	float magForce = 1000000;
	int negMultiplier = 1;
	if((rand() % 2) == 1)
	{
		negMultiplier = -1;
	}
	float xForce = ((float) rand()/RAND_MAX) * magForce * negMultiplier;
	float yForce = ((float) rand()/RAND_MAX) * magForce * negMultiplier;
	float zForce = ((float) rand()/RAND_MAX) * magForce * negMultiplier;

	ParticlePtr particle(new dynamx::Particle());
	particle->SetPos(m_SpawnPos);
	particle->SetMass(1000);
	particle->AddForce(dynamx::Vector3(xForce,yForce,zForce)); //Random Force

//	m_ParticleForceRegistry.Add(particle.get(), m_GravityForceGen);
	m_ParticleForceRegistry.Add(particle.get(), m_DragForceGen);

//	m_ParticleForceRegistry.Add(particle.get(), m_AttractionForceGen);

	m_Particles.push_back(particle);
}

void ParticleSimulation::RemoveParticle()
{
	ParticlePtr particle = m_Particles.front();
	m_ParticleForceRegistry.Remove(particle.get(), m_GravityForceGen);
	m_ParticleForceRegistry.Remove(particle.get(), m_DragForceGen);
	m_Particles.pop_front();
}

void ParticleSimulation::ToggleGravity()
{
	if(m_Gravity)
	{
		list<ParticlePtr>::iterator particleIt, particleItEnd;
		for(particleIt = m_Particles.begin(), particleItEnd = m_Particles.end();
				particleIt != particleItEnd ; 
				particleIt++)
		{
			m_ParticleForceRegistry.Remove((*particleIt).get(), m_GravityForceGen);
		}
		m_Gravity = false;
	}
	else
	{
		list<ParticlePtr>::iterator particleIt, particleItEnd;
		for(particleIt = m_Particles.begin(), particleItEnd = m_Particles.end();
				particleIt != particleItEnd ; 
				particleIt++)
		{
			m_ParticleForceRegistry.Add((*particleIt).get(), m_GravityForceGen);
		}
		m_Gravity = true;
	}
}

void ParticleSimulation::ToggleAttraction()
{
	if(m_Attraction)
	{
		list<ParticlePtr>::iterator particleIt, particleItEnd;
		for(particleIt = m_Particles.begin(), particleItEnd = m_Particles.end();
				particleIt != particleItEnd ; 
				particleIt++)
		{
			m_ParticleForceRegistry.Remove((*particleIt).get(), m_AttractionForceGen);
		}
		m_Attraction = false;
	}
	else
	{

		list<ParticlePtr>::iterator particleIt, particleItEnd;
		for(particleIt = m_Particles.begin(), particleItEnd = m_Particles.end();
				particleIt != particleItEnd ; 
				particleIt++)
		{
			m_ParticleForceRegistry.Add((*particleIt).get(), m_AttractionForceGen);
		}
		m_Attraction = true;
	}
}
