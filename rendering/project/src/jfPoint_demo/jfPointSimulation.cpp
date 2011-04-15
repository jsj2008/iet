#include "jfPointSimulation.hpp"

jfPointSimulation::jfPointSimulation()
	:
		jfSimulation()
{
}

jfPointSimulation::~jfPointSimulation()
{
}


void jfPointSimulation::setupLighting()
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

void jfPointSimulation::InitGL()
{
    setupLighting();
    glShadeModel( GL_SMOOTH );
    //glClearColor(0.1, 0.1, 0.5, 0.0);
    glClearDepth( 10.0f );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glClearAccum(0.1, 0.1, 0.8, 0.0);

    glViewport(0, 0, m_Window->getHeight(), m_Window->getWidth());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(float)m_Window->getHeight()/(float)m_Window->getWidth(),0.1,600);
    glEnable(GL_COLOR_MATERIAL);
}

void jfPointSimulation::VOnUpdate()
{
	;
}

void jfPointSimulation::VOnMainLoop()
{
    while(!m_Finished)
    {
        HandleInput();
        VOnUpdate();
        VOnRender();
    }
}

void jfPointSimulation::HandleInput()
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
					m_Window->toggleFullscreen();
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
				m_Camera.setPos(m_Camera.getPos().add(jfVector3(0,1,0)));
			}
			else if(event.key.keysym.sym == SDLK_k)
			{
				m_Camera.setPos(m_Camera.getPos().add(jfVector3(0,-1,0)));
			}
			else if(event.key.keysym.sym == SDLK_j)
			{
				m_Camera.setRot(m_Camera.getRot().add(jfVector3(0,-8,0)));
			}
			else if(event.key.keysym.sym == SDLK_l)
			{
				m_Camera.setRot(m_Camera.getRot().add(jfVector3(0,8,0)));
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
		dynamx::jfVector3 camRot = m_Camera.getRot();
		camRot.setY(x + camRot.getY());
		camRot.setX(y + camRot.getX());
		m_Camera.setRot(camRot);
	}
	*/
}


void jfPointSimulation::VOnInit()
{
    jfSimulation::VOnInit();
	InitGL();
	m_Finished = false;

	jfQSplatModelPtr model(new jfQSplatModel("../../media/models/bunny.qs"));
	m_Models.push_back(model);
}

void jfPointSimulation::DoCamera()
{
	glRotatef(m_Camera.getRot().getX(),1.0,0.0,0.0);
	glRotatef(m_Camera.getRot().getY(),0.0,1.0,0.0);
	glRotatef(m_Camera.getRot().getZ(),0.0,0.0,1.0);

	GLfloat xtrans = -(m_Camera.getPos().getX());
	GLfloat ytrans = -(m_Camera.getPos().getY());
	GLfloat ztrans = -(m_Camera.getPos().getZ());
	glTranslatef(xtrans, ytrans, ztrans);
}

void jfPointSimulation::VOnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DoCamera();

	/*
	glTranslatef(-1.5f,0.0f,-6.0f);				// Left 1.5 Then Into Screen Six Units

	glBegin(GL_TRIANGLES);					// Begin Drawing Triangles
		glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Move Up One Unit From Center (Top Point)
		glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
		glVertex3f(-1.0f,-1.0f, 0.0f);			// Left And Down One Unit (Bottom Left)
		glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
		glVertex3f( 1.0f,-1.0f, 0.0f);			// Right And Down One Unit (Bottom Right)
	glEnd();						// Done Drawing A Triangle
	*/



	SDL_GL_SwapBuffers();
}
