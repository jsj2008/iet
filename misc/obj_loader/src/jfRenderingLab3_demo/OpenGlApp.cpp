// OPenGLApp.cpp : Defines the entry point for the console application.
//

// Header Files Specified
// These contain functionality that is need for the GLUT application
// And for general windows functionality
//#include "stdafx.h"
//#include <windows.h>	// for timeGetTime()
//#include <mmsystem.h>	// ditto

#ifdef WIN
#ifndef INCLUDE_GL
#define INCLUDE_GL

#include "gl/glew.h" // glew for saccess to shader functionality
#include "gl/glut.h"	// GLUT
#include <gl/glu.h>		// for gluPerspective & gluLookAt
#include <iostream>		// I/O
#include  <math.h>
#endif
#else

#include <GL/glew.h> // glew for saccess to shader functionality
//#include "GL/glut.h"	// GLUT
#include <GL/glu.h>		// for gluPerspective & gluLookAt
#include <iostream>		// I/O
#include  <math.h>

#endif

#include <sstream>
#include "IL/il.h"	// for easier loading of images
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "textureTGA.h" // TGA support
#include "Vector3D.h"
#include "Camera.h"

#include <jfModel/jfObjLoader.hpp>
#include <jfModel/jfModelDrawer.hpp>

#define DRAW_PYRAMID 1
#define DRAW_SPHERE 2
#define DRAW_CUBE 3
#define DRAW_TEAPOT 4
#define DRAW_MYTEAPOT 5

using namespace std;

// Decclaration of functions to be used within the program
// these are accessible from an function in this file
void setupScene();
void updateScene();
void renderScene();
void exitScene();
void keypress(unsigned char key, int x, int y);
void setViewport(int width, int height);


void setUpQuadric();
void loadCubeMaptexture();
void enableCubeMap(bool enable);
void drawSkyBox();

void loadShaders();

void drawPyramid();
void drawSphere();
void drawCube();
void drawTeapot();
void drawMyTeapot();

// Global Variable to be used within the program

Camera myCamera;
bool		wireframe=false;
int         windowId;
GLuint      textureId;
//DWORD		lastTickCount;
int		lastTickCount;
bool normalsOutput = false;
const int nReflectOptions = 4;

GLUquadricObj* sphere;

GLint drawObject = DRAW_PYRAMID;

jfModel teapotModel;

GLfloat blackMaterial[4] = {0.0,0.0,0.0,1.0}; // Used to set a material value to 0

GLfloat materialAmbient[4]; 				// Ambient material Values 
GLfloat materialDiffuse[4];				 // Diffuse material Values
GLfloat materialSpecular[4];		// Specular material Values
GLfloat materialEmissive[4];
GLfloat materialShininess;				 // material Shininess


GLfloat materialAmbient2[4]; 				// Ambient material Values 
GLfloat materialDiffuse2[4];				 // Diffuse material Values
GLfloat materialSpecular2[4];		// Specular material Values
GLfloat materialEmissive2[4];
GLfloat materialShininess2;				 // material Shininess

GLfloat materialAmbient3[4]; 				// Ambient material Values 
GLfloat materialDiffuse3[4];				 // Diffuse material Values
GLfloat materialSpecular3[4];		// Specular material Values
GLfloat materialEmissive3[4];
GLfloat materialShininess3;				 // material Shininess

GLfloat rotateSpeed = 0.f;
GLfloat rotateAngle = 0.f;

bool mainLightEnabled = true;

// Add any further global Variables Here  
// Gloabl Variables for shaders

GLuint myProgObj;
GLuint myVertexObj;
GLuint myFragObj;

GLuint textureID[6];
GLint rotationValue = 2;

//Location variabls for shader uniforms
GLint eyePos;

int reflect = 0;

GLfloat rotationAngle = 0;
bool cubeMapEnabled = false;
GLuint cubeMapTextureId;

//uniform Locations

GLint modelMatLoc;
GLint invModelMatLoc;
GLint eyewLoc;
GLint cubeSamplerLoc;
GLint reflectLoc;

void renderScene()
{	
	glUseProgram(0);
	glDisable(GL_LIGHTING);

	// Clear framebuffer & depth buffer
	// So we cna withdraw the scene from scratch
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Disable Textures until we want to use them
	glDisable(GL_TEXTURE_2D);


	// Reset Modelview matrix 
	// Removing alltransforamtions and positioing the camera in 
	// the defaultposition (at (0,0,0) and looking down the negative z axis
	// Remember OpenGL uses a right handed system

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set view position & direction
	// (Camera at (0,0,5) looking down the negative Z-axis)
	//gluLookAt(cameraPosition[0],cameraPosition[1],cameraPosition[2],  0,0,-100,  0,1,0);
	myCamera.positionCamera();

	GLfloat lightPosition[4] = {0,0,-5,1};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// Start your draawing Funciobnality Here
	// This should specify the drawing of the planets
	// as well as the positioniong of the light source

	// Draw Background Cube
	glPushMatrix();
	glScalef(50,50,50);
	drawSkyBox();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-40);
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0);glVertex3f(1,1,1);
	glTexCoord2f(0,1);glVertex3f(1,-1,1);
	glTexCoord2f(1,1);glVertex3f(-1,-1,1);
	glTexCoord2f(1,0);glVertex3f(-1,1,1);
	glEnd();
	glPopMatrix();
	rotateAngle += rotateSpeed;
	if (	rotateAngle > 360 )
	{
		rotateAngle-=360 ;
	}
	if (	rotateAngle < 0 )
	{
		rotateAngle = 360-rotateAngle ;
	}
	GLuint errorNum;
	//send unofrm attributes here
	glPushMatrix();
	glTranslatef(0,0,-10);
	glRotatef(rotateAngle, 0,1,0);
	// Draw the Pyramid object here
	//draw the desk ornament
	if(!mainLightEnabled)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
	else
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}
	glEnable(GL_TEXTURE_2D);
	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}
	glUseProgram(myProgObj);
	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}
	//send uniforms here

	// get the model view matrix
	// using opengl to calulate the model matrix
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0,0,-10);

	glRotatef(rotateAngle, 0,1,0);

	GLfloat modelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,modelMatrix);

	glPopMatrix();

	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}

	glUniformMatrix4fv(modelMatLoc,1,false,modelMatrix);
	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}

	GLfloat eyePos[4];
	eyePos[0] = myCamera.getX();
	eyePos[1] = myCamera.getY();
	eyePos[2] = myCamera.getZ();
	eyePos[3] = 1;

	glUniform3fv(eyewLoc,1,eyePos);

	/*
	if(reflect==0)
	{
		glUniform1i(reflectLoc,0);
	}
	else if(reflect == 1)
	{
		glUniform1i(reflectLoc,0);
	}
	*/
	glUniform1i(reflectLoc, reflect);

	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}

	switch(drawObject)
	{
		case DRAW_PYRAMID:
			drawPyramid();
			break;
		case DRAW_SPHERE:
			drawSphere();
			break;
		case DRAW_CUBE:
			drawCube();
			break;
		case DRAW_TEAPOT:
			drawTeapot();
			break;
		case DRAW_MYTEAPOT:
			drawMyTeapot();
			break;
	}

	// End you drawing code here

	glPopMatrix();
	// Swap double buffer for flicker-free animation
	glutSwapBuffers();

	glDisable(GL_TEXTURE_2D);

	// Double Buffering is a technique by which the image is not drawn directly to the screen
	// but rather to a buffer in the background
	// Once the drawing is complete the buffers are swapped
	// this prevents flicker in animation
	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}
}

void updateScene()
{
	// Wait until at least 16ms passed since start of last frame
	// Effectively caps framerate at ~60fps
	// This stops the animation going too fast
	//	while(timeGetTime()-lastTickCount<16);
	//	lastTickCount=timeGetTime();
	
	//Ultimate hack. Better than using windows API though.
	int time = glutGet(GLUT_ELAPSED_TIME); 
	while((time - lastTickCount) < 16)
	{
		time = glutGet(GLUT_ELAPSED_TIME); 
	}
	lastTickCount = glutGet(GLUT_ELAPSED_TIME); 


	// This is a good place to put any animation code
	// such as the amount an object onscreen should be moved or rotated
	// Start Updates here

	// End updates here

	// Draw the next frame
	glutPostRedisplay();

}

void keypress(unsigned char key, int x, int y)
{
	// Test if user pressed ESCAPE (ascii 27)
	// If so, exit the program
	if(key==27)
	{		exitScene();
	}

	// 'X' key toggles wireframe mode on & off
	if(key == 'x' || key == 'X')
	{		wireframe=!wireframe;
		if(wireframe)
		{			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(key == 'a')
	{		//	myCamera.strafeCamera(-1);
		myCamera.yawCamera(2);
		//cameraPosition[0] -= 1;
	}else if(key == 'd')
	{		//	myCamera.strafeCamera(1);]
		myCamera.yawCamera(-2);
		//cameraPosition[0]  += 1;
	}else if(key == 'w')
	{		myCamera.moveCamera(0.2);
		//	cameraPosition[2] -= 1;
	}else if(key == 's')
	{		myCamera.moveCamera(-0.2);
		//	cameraPosition[2] += 1;
	}else if(key == 'l')
	{		if(mainLightEnabled)
		{			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}else{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}
		mainLightEnabled = !mainLightEnabled;
	}
	else if(key == '+')
	{
		rotateSpeed +=0.5;
	}else if(key == '-')
	{
		rotateSpeed -= 0.5;
	}else if(key == 'c' || key == 'C')
	{

		if(cubeMapEnabled)
		{			enableCubeMap(false);
		}else{
			enableCubeMap(true);
		}

	}else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5')
	{
		drawObject = key - 48;
	}else if (key == 'r' || key == 'R')
	{
		//reflect = !reflect;
		reflect = (reflect+1) % nReflectOptions;
		cout<<"reflect is :"<<reflect<<endl;
	}
	else if (key == 'f')
	{
		//reflect = !reflect;
		reflect = (reflect-1);
		if(reflect == -1)
		{
			reflect = nReflectOptions - 1;
		}
		cout<<"reflect is :"<<reflect<<endl;
	}

	// Other possible keypresses go here
	//if(key == 'a'){...}
}



void setupScene()
{
	// This function is called once when the appication 
	// is started
	std::cout<<"Initializing scene..."<<std::endl;
	myCamera.setCameraPosition(0,1.5,5);
	// Initialise desired OpenGL state
	glClearColor(0,0,0,0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//	glEnable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Loading the textures
	// Generate GL texture ID & load texture
	glGenTextures(1, &textureId);

	//textureTga sunTexture("gv2_logo.tga", textureId);

	setUpQuadric();

	// seting up lighting parameters here (the different components of the light)

	GLfloat spotCutoff = 80.0;
	GLfloat spotExponent = 3.0;

	//End Your spotlight code here


	// Enabling open GL to use 2 Sided Lighting
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

	// Set up the second Light (the "room light")

	GLfloat lightDiffuse[4] = { 1.0,0.0,0.0,1.0};
	GLfloat lightAmbient[4] = { 0.0,0.0,0.0,1.0};
	GLfloat lightSpecular[4] = { 1.0,1.0,1.0,1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);				// Setup The Ambient Light			
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	cubeMapEnabled = false;

	loadShaders();
	loadCubeMaptexture();
	glColor3f(1,1,1);

	jfObjLoader objLoader;
//	objLoader.loadFromFile("../../media/models/dragon.obj", &teapotModel);
	objLoader.loadFromFile("../../media/models/bunny.obj", &teapotModel);
	

}

void exitScene()
{
	std::cout<<"Exiting scene..."<<std::endl;

	// Close window
	glutDestroyWindow(windowId);

	// Free any allocated memory

	// Exit program
	exit(0);
}

void setViewport(int width, int height)
{
	// Configure the view which we will be useing to look at the model
	// This includes definining how much of the window we want to look at 
	// as well as the perspective of the scence that is being drawn
	// Work out window ratio, avoid divide-by-zero


	// following line avoids a divide by zero error
	if(height==0)height=1;
	float ratio = float(width)/float(height);

	// The projection matrix defines how the 3D scrence is rendered ionto the 3D screen
	// Reset projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Fill screen with viewport
	glViewport(0, 0, width, height);

	// Set a 45 degree perspective
	gluPerspective(45, ratio, .1, 1000);

}

int main(int argc, char *argv[])
{
	// argc and argv refer to parameters that may have been passed in from  the command line
	// argc is the number of parameters ( the Arguemnets themselves)
	// argv is an array of old fashioned character based c-style strings which contain the paramaters
	// the following line passes those parameters to the glut library.
	//
	// In our case there are no parameters to be passed
	// i.e. argc = 0 (or is empty)
	// argv = ""
	// Initialise OpenGL

	glutInit(&argc, argv); 

	// Set window position, size & create window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// Position the GLUT window on-screen
	glutInitWindowPosition(50,50);
	// specify the window size
	glutInitWindowSize(640,480);
	windowId = glutCreateWindow("CS4: Lighting ");

	// Set GLUT callback functions
	// specify what function we want to be called for specific events
	// When the window is resized
	glutReshapeFunc(setViewport);
	// when the window is refreshed/drawn
	glutDisplayFunc(renderScene);

	// when nothing is happening
	glutIdleFunc(updateScene);
	// When a key press event is received

	glutKeyboardFunc(keypress);
	//
	// Setup OpenGL state & scene resources (models, textures etc)
	setupScene();

	// Show window & start update loop
	glutMainLoop();    

	return 0;
}


void setUpQuadric()
{
	sphere  = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricDrawStyle(sphere,GLU_FILL);
	gluQuadricOrientation(sphere,GLU_OUTSIDE);
}


void loadShaders()
{

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "GLEW failed to initialise!" << std::endl;
	}

	if (glewIsSupported("GL_VERSION_2_0"))
	{		std::cerr << "Ready for OpenGL 2.0\n"<< std::endl;
	}else {
		std::cerr << "OpenGL 2.0 not supported\n" << std::endl;
		//exit(1);

	}
	//std::stringstream myOutput;
	//const GLubyte* sExtensions = glGetString(GL_EXTENSIONS);
	//
	//myOutput << "Enabled Extensions\n" << sExtensions << std::endl;

	//std::cout << myOutput.str();
	myProgObj = glCreateProgram();
	GLint status = 0;


	std::ifstream shdr;
	//shdr.open(".\\vertShader.txt");
	shdr.open("../../src/jfRenderingLab3_demo/shaders/vertShader.txt");
	if(!shdr)
	{		std::cerr << "Shader File Not Found!" << std::endl;
	}else{
		std::cout  << "Shader File Found OK!" << std::endl;

	}
	std::stringstream shdrData;
	char inChar;
	while (shdr.get(inChar))
	{

		shdrData << inChar;

	}
	std::string shaderStr(shdrData.str());
	shdr.close();
	//const char* prog = progFile;
	GLchar* vertexProg = new GLchar[shaderStr.length()+ 1];
	for(unsigned int i = 0 ; i < shaderStr.length(); i ++)
	{
		vertexProg[i] = shaderStr[i];
	}

	vertexProg[shaderStr.length()] = '\0';

	const GLchar* progData = &vertexProg[0];
	myVertexObj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(myVertexObj,1, &progData,NULL);

	glAttachShader(myProgObj,myVertexObj);

	delete vertexProg;

	glCompileShader(myVertexObj);
	glGetShaderiv(myVertexObj,GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		//GLuint infoLogLength;

		//glGetShaderiv(myVertexObj,GL_INFO_LOG_LENGTH,&infoLogLength);
		std::cerr << "Shader Compile Failed" << std::endl;
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetShaderiv(myVertexObj, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(myVertexObj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	//Load Fragemnt shader

	std::ifstream fshdr;
	//fshdr.open(".\\fragShader.txt");
	fshdr.open("../../src/jfRenderingLab3_demo/shaders/fragShader.txt");
	if(!fshdr)
	{		std::cerr << "Shader File Not Found!" << std::endl;
	}else{
		std::cout  << "Shader File Found OK!" << std::endl;

	}
	std::stringstream fshdrData;

	while (fshdr.get(inChar))
	{		fshdrData << inChar;
	}

	std::string fshaderStr(fshdrData.str());
	fshdr.close();
	//const char* prog = progFile;
	GLchar* fragProg = new GLchar[fshaderStr.length()+ 1];
	for(unsigned int i = 0 ; i < fshaderStr.length(); i ++)
	{
		fragProg[i] = fshaderStr[i];
	}

	fragProg[fshaderStr.length()] = '\0';

	progData = &fragProg[0];
	myFragObj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(myFragObj,1, &progData,NULL);
	glAttachShader(myProgObj,myFragObj);
	delete fragProg;	

	glCompileShader(myFragObj);
	glGetShaderiv(myFragObj,GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		//GLuint infoLogLength;
		//glGetShaderiv(myVertexObj,GL_INFO_LOG_LENGTH,&infoLogLength);
		std::cerr << "Fragment Shader Compile Failed" << std::endl;
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;
		glGetShaderiv(myFragObj, GL_INFO_LOG_LENGTH,&infologLength);
		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(myFragObj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	glLinkProgram(myProgObj);
	glGetProgramiv(myProgObj,GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		//GLuint infoLogLength;
		//glGetShaderiv(myVertexObj,GL_INFO_LOG_LENGTH,&infoLogLength);
		std::cerr << "Proggy Link Failed" << std::endl;
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;
		glGetProgramiv(myProgObj, GL_INFO_LOG_LENGTH,&infologLength);
		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(myProgObj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}
	else
	{
		std::cout << "Shaders linked Successfuly" <<std::endl;
	}

	GLchar nameBuffer[40];
	GLint numUniforms = -1;
	glGetProgramiv(	myProgObj, GL_ACTIVE_UNIFORMS, &numUniforms);

	GLint nameLength;
	GLint varSize;
	GLenum varType;

	for(int i =0 ; i < numUniforms ; i++)
	{
		glGetActiveUniform(myProgObj,  i,  40, &nameLength, &varSize, 	&varType, nameBuffer);
		std::cout << "UNiform Name " << nameBuffer << std::endl;
	}

	// start using program
	glUseProgram(myProgObj);
	/*GLint loc2 =0;

	  loc2 = glGetUniformLocation(myProgObj,"col");
	  float sc[4] = {0.8,0.8,0.8,1.0};
	  glUniform4f(loc2,sc[0],sc[1],sc[2],sc[3]);*/

	//// set up uniform variabl
	modelMatLoc = glGetUniformLocation(myProgObj, "modelMat");
	//	invModelMatLoc = glGetUniformLocation(myProgObj, "invModelMat");
	eyewLoc = glGetUniformLocation(myProgObj, "eyew");
	cubeSamplerLoc = glGetUniformLocation(myProgObj,"myMap");
	reflectLoc = glGetUniformLocation(myProgObj,"doReflect");	

	GLuint errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{		std::cout << "Error = " << gluErrorString(errorNum) << std::endl;
	}
}

void loadCubeMaptexture()
{
	//drawCloseUp = false;
	// Initialize IL
	ilInit();
	// Initialize ILU
	iluInit();
	// Initialize ILUT with OpenGL support.
	//Enumerate the cube faces so we can cycle through them
	//aeasily as part of a for loop
	GLenum cubefaces[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT,
	};

	ilutRenderer(ILUT_OPENGL);
	//need to load in the 6 textures for the cube map
	int errorNum;
	std::string errorStr;
	/*
	std::string textureFilenames[6] = {
		"../../media/tex/cm_left.tga",
		"../../media/tex/cm_right.tga",										
		"../../media/tex/cm_top.tga",
		"../../media/tex/cm_bottom.tga",
		"../../media/tex/cm_back.tga",		
		"../../media/tex/cm_front.tga"	
	};
	*/

	std::string textureFilenames[6] = {
		"../../media/tex/cubemap_cube2/cube2_negative_x.png",
		"../../media/tex/cubemap_cube2/cube2_positive_x.png",
		"../../media/tex/cubemap_cube2/cube2_positive_y.png",
		"../../media/tex/cubemap_cube2/cube2_negative_y.png",
		"../../media/tex/cubemap_cube2/cube2_negative_z.png",
		"../../media/tex/cubemap_cube2/cube2_positive_z.png"
	};

	ILboolean imageLoaded;
	ILuint ImageName[6];	
	//ImageName = new ILuint[6];

	glGenTextures(6, textureID);
	ilGenImages(6,ImageName);
	errorNum = ilGetError();
	if(errorNum != IL_NO_ERROR)
	{		errorStr= iluErrorString( errorNum);
		std::cout << errorStr;
	}
	ILubyte* dataPtrs[6];
	for(int i=0 ; i < 6 ; i++)
	{
		ilBindImage(ImageName[i]);
		imageLoaded =  ilLoadImage(textureFilenames[i].c_str());
		errorNum = ilGetError();
		if(errorNum != IL_NO_ERROR)
		{			errorStr= iluErrorString( errorNum);
			std::cout << errorStr;
		}
		dataPtrs[i] = ilGetData();
		glBindTexture(GL_TEXTURE_2D,textureID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(
				GL_TEXTURE_2D,
				0,                  // level
				3,          // internal format
				128,     // width
				128,     // height
				0,                 // border
				GL_BGR,           // format
				GL_UNSIGNED_BYTE,   // type
				dataPtrs[i]); // pixel data
		errorNum = glGetError();
		if(errorNum != GL_NO_ERROR)
		{
			std::cerr << gluErrorString( errorNum);

		}
	}
	glGenTextures(1, &cubeMapTextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureId);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	for(int i=0 ; i < 6 ; i++)
	{
		glTexImage2D(
				cubefaces[i],
				0,                  // level
				3,          // internal format
				128,     // width
				128,     // height
				0,                 // border
				GL_BGR,           // format
				GL_UNSIGNED_BYTE,   // type
				dataPtrs[i]); // pixel data
		errorNum = glGetError();
		if(errorNum != GL_NO_ERROR)
		{
			std::cerr << gluErrorString( errorNum);
		}
	}

	ilDeleteImages(6,ImageName);
	errorNum = ilGetError();
	if(errorNum != IL_NO_ERROR)
	{		errorStr= iluErrorString( errorNum);
		std::cout << errorStr;
	}	

	glUniform1i(cubeSamplerLoc,0);

	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cerr << gluErrorString( errorNum);

	}
}

void enableCubeMap(bool enable)
{
	cubeMapEnabled = enable;

	if(enable)
	{
		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureId);
		glEnable(GL_TEXTURE_CUBE_MAP);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);
		glEnable(GL_NORMALIZE);
	}
	else
	{
		glDisable(GL_TEXTURE_CUBE_MAP);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_NORMALIZE);
		glDisable(GL_TEXTURE_CUBE_MAP);
	}
}


void drawSkyBox()
{
	materialAmbient[0]= 1.0f; 	
	materialAmbient[1]= 1.0f;
	materialAmbient[2]= 1.0f;
	materialAmbient[3]= 1.0f;

	materialDiffuse[0] = 1.0f;
	materialDiffuse[1] = 1.0f;
	materialDiffuse[2] = 1.0f;
	materialDiffuse[3] = 1.0f;

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;

	materialShininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,materialSpecular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, materialShininess);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureID[1]);
	glBegin(GL_QUADS);

	//right Side			
	glNormal3f(-1,0,0);
	glTexCoord2f(1,0);glVertex3f(1,1,1);
	glTexCoord2f(0,0);glVertex3f(1,1,-1);
	glTexCoord2f(0,1);glVertex3f(1,-1,-1);
	glTexCoord2f(1,1);glVertex3f(1,-1,1);
	glEnd();

	//left Side
	glBindTexture(GL_TEXTURE_2D,textureID[0]);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0);glVertex3f(-1,1,1);
	glTexCoord2f(1,0);glVertex3f(-1,1,-1);
	glTexCoord2f(1,1);glVertex3f(-1,-1,-1);
	glTexCoord2f(0,1);glVertex3f(-1,-1,1);
	glEnd();

	//TopSide
	//	glColor3f(0,0,1);
	glBindTexture(GL_TEXTURE_2D,textureID[2]);
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glTexCoord2f(1,0);glVertex3f(-1,1,-1);
	glTexCoord2f(1,1);glVertex3f(-1,1,1);
	//	glColor3f(1,0,0);
	glTexCoord2f(0,1);glVertex3f(1,1,1);
	glTexCoord2f(0,0);glVertex3f(1,1,-1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D,textureID[3]);
	glBegin(GL_QUADS);

	//Bottom Side
	//	glColor3f(0,1,1);
	glNormal3f(0,1,0);
	glTexCoord2f(1,1);glVertex3f(-1,-1,-1);
	glTexCoord2f(1,0);glVertex3f(-1,-1,1);
	glTexCoord2f(0,0);glVertex3f(1,-1,1);
	glTexCoord2f(0,1);glVertex3f(1,-1,-1);

	glEnd();

	// back Face	
	glBindTexture(GL_TEXTURE_2D,textureID[4]);
	glBegin(GL_QUADS);

	glNormal3f(0,0,-1);
	glTexCoord2f(0,0);glVertex3f(1,1,1);
	glTexCoord2f(0,1);glVertex3f(1,-1,1);
	glTexCoord2f(1,1);glVertex3f(-1,-1,1);
	glTexCoord2f(1,0);glVertex3f(-1,1,1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D,textureID[5]);
	glBegin(GL_QUADS);

	//front Face
	glNormal3f(0,0,1);
	glTexCoord2f(1,0);glVertex3f(1,1,-1);
	glTexCoord2f(1,1);glVertex3f(1,-1,-1);
	glTexCoord2f(0,1);glVertex3f(-1,-1,-1);
	glTexCoord2f(0,0);glVertex3f(-1,1,-1);

	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawPyramid()
{

	//The following vector3D objects have been created for you to use

	//	glUseProgram(myProgObj);
	// these Vectors are used to define the vertices that make up the pyramid
	// replace all of the (0,0,0) values with the values you want to use for the vertices of your pyramid

	Vector3D top(0,8,0);
	Vector3D backLeft(-4,0,-4);
	Vector3D backRight(4,0,-4);
	Vector3D frontLeft(-4,0,4);
	Vector3D frontRight(4,0,4);

	// the following vectors are used to store the result of the normal calculations
	// It may be necessary for you to create additional vectors to help in you calulations

	Vector3D frontNormal;
	Vector3D backNormal;
	Vector3D leftNormal;
	Vector3D rightNormal;

	Vector3D u,v;
	v = top - frontLeft;
	u = frontRight - frontLeft;
	frontNormal = u.getCrossProduct(v);
	frontNormal.normalise();

	v = top - backRight;
	u = backLeft - backRight;
	backNormal = u.getCrossProduct(v);
	backNormal.normalise();

	v = top - frontRight;
	u = backRight - frontRight;
	rightNormal = u.getCrossProduct(v);
	rightNormal.normalise();

	v = top - backLeft;
	u = frontLeft - backLeft;
	leftNormal = u.getCrossProduct(v);
	leftNormal.normalise();

	glBegin(GL_TRIANGLES);

	////front face
	glNormal3f(frontNormal[0],frontNormal[1],frontNormal[2]);
	glTexCoord2f(0.5,1.0);
	glVertex3f(top[0],top[1],top[2]);
	glTexCoord2f(0.0,0.0);
	glVertex3f(frontLeft[0],frontLeft[1],frontLeft[2]);
	glTexCoord2f(1.0,0.0);
	glVertex3f(frontRight[0],frontRight[1],frontRight[2]);
	//
	////back Face

	glNormal3f(backNormal[0],backNormal[1],backNormal[2]);
	glTexCoord2f(0.5,1.0);
	glVertex3f(top[0],top[1],top[2]);
	glTexCoord2f(0.0,0.0);
	glVertex3f(backRight[0],backRight[1],backRight[2]);
	glTexCoord2f(1.0,0.0);
	glVertex3f(backLeft[0],backLeft[1],backLeft[2]);

	////left Face
	glNormal3f(leftNormal[0],leftNormal[1],leftNormal[2]);
	glTexCoord2f(0.5,1.0);
	glVertex3f(top[0],top[1],top[2]);
	glTexCoord2f(0.0,0.0);
	glVertex3f(backLeft[0],backLeft[1],backLeft[2]);
	glTexCoord2f(1.0,0.0);
	glVertex3f(frontLeft[0],frontLeft[1],frontLeft[2]);

	////right Face
	glNormal3f(rightNormal[0],rightNormal[1],rightNormal[2]);
	glTexCoord2f(0.5,1.0);
	glVertex3f(top[0],top[1],top[2]);
	glTexCoord2f(0.0,0.0);
	glVertex3f(frontRight[0],frontRight[1],frontRight[2]);
	glTexCoord2f(1.0,0.0);
	glVertex3f(backRight[0],backRight[1],backRight[2]);

	glEnd();
}

void drawSphere()
{
	gluSphere(sphere, 4,15,15);

}
void drawCube()
{

	glBegin(GL_QUADS);

	//right Side


	glNormal3f(1,0,0);
	glVertex3f(4,4,4);
	glVertex3f(4,4,-4);
	glVertex3f(4,-4,-4);
	glVertex3f(4,-4,4);

	//left Side
	glNormal3f(-1,0,0);
	glVertex3f(-4,4,4);
	glVertex3f(-4,4,-4);
	glVertex3f(-4,-4,-4);
	glVertex3f(-4,-4,4);

	//TopSide

	glNormal3f(0,1,0);
	glVertex3f(-4,4,-4);
	glVertex3f(-4,4,4);	
	glVertex3f(4,4,4);
	glVertex3f(4,4,-4);

	//Bottom Side

	glNormal3f(0,-1,0);
	glVertex3f(-4,-4,-4);
	glVertex3f(-4,-4,4);
	glVertex3f(4,-4,4);
	glVertex3f(4,-4,-4);

	// Front Face		
	glNormal3f(0,0,1);
	glVertex3f(4,4,4);
	glVertex3f(4,-4,4);
	glVertex3f(-4,-4,4);
	glVertex3f(-4,4,4);

	//Back Face
	glNormal3f(0,0,-1);
	glVertex3f(4,4,-4);
	glVertex3f(4,-4,-4);
	glVertex3f(-4,-4,-4);
	glVertex3f(-4,4,-4);

	glEnd();
}

void drawTeapot()
{
	glutSolidTeapot(4);
}

void drawMyTeapot()
{
	glPushMatrix();
//	glScalef(0.05,0.05,0.05);
	jfModelDrawer drawer;
	drawer.draw(teapotModel);
	glPopMatrix();
}
