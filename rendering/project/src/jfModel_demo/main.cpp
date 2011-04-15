#include <jfwm/jfWindowManager.hpp>
#include <jfwm/jfSDLWindowManager.hpp>
#include <jfModel/jfObjLoader.hpp>
#include <jfModel/jfModelDrawer.hpp>

void setupLighting()
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

void initGL(const jfWindow& window)
{
	setupLighting();
	glShadeModel( GL_SMOOTH );
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth( 10.0f );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glClearAccum(0.1, 0.1, 0.8, 0.0);

	glViewport(0, 0, window.getWidth(), window.getHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(float)window.getWidth()/(float)window.getHeight(),0.1,600);


	// Enable color tracking
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glEnable(GL_COLOR_MATERIAL);
	// Set material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,128);

	glEnable(GL_NORMALIZE);

}

void onRender(const jfModelDrawer& drawer, const jfModel& model)
{
	glShadeModel( GL_SMOOTH );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glTranslatef(0,-1,-3);
//	glTranslatef(0,-1000,-1000);
	gluLookAt(0,200,300, 0,0,0 , 0,1,0);

	glRotatef(90, 0, 1, 0);
	drawer.draw(model);


	/*
	GLUquadric* m_Quadric = gluNewQuadric();
	float Radius = 3.3;
	float SphereStacks = 30;
	float SphereSlices = 30;
	GLuint m_NormalSphereList = glGenLists(1);
	glNewList(m_NormalSphereList, GL_COMPILE);
		gluSphere( m_Quadric, Radius, SphereSlices, SphereStacks);
	glEndList ();

	glCallList(m_NormalSphereList);
	*/

	SDL_GL_SwapBuffers();
}

int main(void)
{
	jfWindowManager* wm = new jfSDLWindowManager();
	jfObjLoader* objLoader = new jfObjLoader();
	wm->init();
	jfWindow* window = wm->createWindow("test");

	initGL(*window);

	jfModel model;
	objLoader->loadFromFile("../../media/models/teapot_3.obj", &model);
	
	jfModelDrawer drawer;
	drawer.draw(model);
	for(int i = 0 ; i < 10000 ; i++)
	{
		onRender(drawer,model);
	}
	delete wm;
	delete objLoader;
	return 0;		
}
