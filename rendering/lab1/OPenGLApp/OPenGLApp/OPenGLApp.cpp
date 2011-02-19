// OPenGLApp.cpp : Defines the entry point for the console application.
//

// Header Files Specified
// These contain functionality that is need for the GLUT application
// And for general windows functionality
//#include "stdafx.h"
#include <windows.h>	// for timeGetTime()
#include <mmsystem.h>	// ditto

#ifndef INCLUDE_GL
#define INCLUDE_GL
#include <gl/glew.h> // glew for access to shader functionality
#include <gl/glut.h>	// GLUT
#include <gl/glu.h>		// for gluPerspective & gluLookAt
#include <iostream>		// I/O
#include  <math.h>
#endif

#include <sstream>
#include <fstream>

#include <IL/il.h>	// devIL lbrary for easier loading of images
#include <IL/ilu.h>
#include <IL/ilut.h>


void setupScene();
void updateScene();
void renderScene();
void exitScene();
void keypress(unsigned char key, int x, int y);
void setViewport(int width, int height);
void loadAndBindTexture(std::string textureFilename);
bool textureEnabled = false;

struct CubeVertex
{
	float position[3]; // x,y and z
	float colour[4]; // red green blue and alpa
	float texture_coordinates[2]; // u and v
};

CubeVertex cubeVertices[24];

void loadShaders();
bool fixedFunctionPipeline = true;

// Global Variables to be used within the program

bool		wireframe=false;
int         windowId;
GLuint      textureId;
DWORD		lastTickCount;

bool useTexture = true;

void drawColorCube();
void drawTexturedCube();

GLint rotateSpeed = 1;
GLint rotateAngle = 0;

// Global Variables for shaders

GLuint myProgObj;
GLuint myVertexObj;
GLuint myFragObj;

GLuint textureID;
GLuint errorNum;
std::string errorStr;


void renderScene(){

	glUseProgram(0); // use the default pipeline
	glDisable(GL_LIGHTING);
			
    // Clear framebuffer & depth buffer
	// So we can draw the scene from scratch
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Disable Textures until we want to use them
	glDisable(GL_TEXTURE_2D);

    // Reset Modelview matrix 
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Set up an "isometric" view position & direction
	glTranslatef(0,0,-20); 
	glRotatef(45,1.0,0.0,0.0);  
	glRotatef(45,0.0,1.0,0.0); 
		
	GLfloat modelview[16];
	// following line allows inspection of the modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX,modelview);

	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error After Camera Position " << gluErrorString(errorNum) << std::endl;
	}
	
	//	Apply rotation to object being drawn
	rotateAngle += rotateSpeed;
	rotateAngle %= 360 ;

	glPushMatrix();
	glRotatef(rotateAngle, 0,1,0);

	if(fixedFunctionPipeline)
	{
		glUseProgram(0);
		errorNum = glGetError();
		if(errorNum != GL_NO_ERROR)
		{
			std::cout << "Error Setting Fixed Function Pipeline " << gluErrorString(errorNum) << std::endl;
		}
	}else
	{
		glUseProgram(myProgObj);	
		errorNum = glGetError();
		if(errorNum != GL_NO_ERROR)
		{
			std::cout << "Error Setting Custom Shader Program " << gluErrorString(errorNum) << std::endl;
		}
	}
	if(useTexture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textureID);
	}

	if(useTexture)
	{
		drawTexturedCube();
	}
	else
	{
		drawColorCube();
	}
	
	// undo rotation which was applied to cube, in case there are ohter objects to be drawn
	glPopMatrix();
    // Swap double buffer for flicker-free animation
    glutSwapBuffers();

	glDisable(GL_TEXTURE_2D);
	// Double Buffering is a technique by which the image is not drawn directly to the screen
	// but rather to a buffer in the background
	// Once the drawing is complete the buffers are swapped
	// this prevents flicker in animation

	glDisable(GL_TEXTURE_2D);
	errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error at end of renderScene:  " << gluErrorString(errorNum) << std::endl;
	}
}

void updateScene(){
	
	// Wait until at least 16ms passed since start of last frame
	// Effectively caps framerate at ~60fps
	// This stops the animation going too fast
	while(timeGetTime()-lastTickCount<16);
	lastTickCount=timeGetTime();
    
	// This is a good place to put any animation code
	// such as the amount an object onscreen should be moved or rotated
	// Start Updates here

	// End updates here
	
	// Draw the next frame
    glutPostRedisplay();

}

void keypress(unsigned char key, int x, int y){
	
	// Test if user pressed ESCAPE (ascii 27)
	// If so, exit the program
    if(key==27){
		exitScene();
	}

	// 'X' key toggles wireframe mode on & off
	if(key == 'x' || key == 'X'){
		wireframe=!wireframe;
		if(wireframe){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	else if(key == '+'){
		rotateSpeed += 1;
	}else if(key == '-'){
		
		rotateSpeed -= 1;
	}else if (key == 'f' || key == 'F')
	{
		if(fixedFunctionPipeline){
			fixedFunctionPipeline = false;
			//glUseProgram(myProgObj);
		}else
		{
			fixedFunctionPipeline = true;
			//glUseProgram(0);
		}
	}
	else if (key == 't' || key == 'T')
	{
		useTexture = !useTexture;
	}

	// Other possible keypresses go here
	// else if(key == 'a'){...}
}



void setupScene(){

	// This function is called once when the appication  is started
	
    // Initialise desired OpenGL state
    glClearColor(0.2,0.2,0.2,1.0);
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Loading the textures
    // Generate GL texture ID & load texture
	loadShaders();
	loadAndBindTexture(".\\metal.tga");
	glColor3f(1,1,1);    
}

void exitScene(){

    std::cout<<"Exiting scene..."<<std::endl;

    // Close window
    glutDestroyWindow(windowId);

    // Exit program
    exit(0);
}

void setViewport(int width, int height) {

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

int main(int argc, char *argv[]){
        
	// argc and argv refer to parameters that may have been passed in from  the command line
	// argc is the number of parameters ( the Arguemnets themselves)
	// argv is an array of old fashioned character based c-style strings which contain the paramaters
	// the following line passes those parameters to the glut library.
	
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
	windowId = glutCreateWindow("OpenGL: Basic Shaders");
    
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

    // Setup OpenGL state & scene resources (models, textures etc)
    setupScene();

    // Show window & start update loop
    glutMainLoop();    

    return 0; 
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
	{
			std::cerr << "Ready for OpenGL 2.0\n"<< std::endl;
	}
	else 
	{
			std::cerr << "OpenGL 2.0 not supported\n" << std::endl;
			//exit(1);	
	}

	myProgObj = glCreateProgram();
	GLint status = 0;
	
	std::ifstream shdr;
	shdr.open(".\\vertShader.txt");
	if(!shdr)
	{
		std::cerr << "Shader File Not Found!" << std::endl;
	}
	else
	{
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

	//Load Fragemnt shader from text file
	std::ifstream fshdr;
	fshdr.open(".\\fragShader.txt");
	if(!fshdr)
	{
		std::cerr << "Shader File Not Found!" << std::endl;
	}
	else
	{
		std::cout  << "Shader File Found OK!" << std::endl;
	}
	std::stringstream fshdrData;
	
	while (fshdr.get(inChar))
	{
		fshdrData << inChar;
	}

	std::string fshaderStr(fshdrData.str());
	fshdr.close();
	
	GLchar* fragProg = new GLchar[fshaderStr.length()+ 1];
	for(unsigned int i = 0 ; i < fshaderStr.length(); i ++)
	{
		fragProg[i] = fshaderStr[i];
	}

	fragProg[fshaderStr.length()] = '\0';


	progData = &fragProg[0];
	myFragObj = glCreateShader(GL_FRAGMENT_SHADER);
	// copy fragment code onto graphics card
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

	}else{
		std::cout << "Shaders linked Successfuly" <<std::endl;
	}
	

	// list the active unifroms associated with the shaders	
	GLchar nameBuffer[40];
	GLint numUniforms = -1;
	glGetProgramiv(	myProgObj, GL_ACTIVE_UNIFORMS, &numUniforms);
	GLint nameLength;
	GLint varSize;
	GLenum varType;
	for(int i =0 ; i < numUniforms ; i++)
	{
		glGetActiveUniform(myProgObj,  i,  40, &nameLength, &varSize, 	&varType, nameBuffer);
		std::cout << "Uniform Name " << nameBuffer << std::endl;
	}

	// start using program
	glUseProgram(myProgObj);
	
	//Check for an open GL error
	GLuint errorNum = glGetError();
	if(errorNum != GL_NO_ERROR)
	{
		std::cout << "Error at end of shader setup :" << gluErrorString(errorNum) << std::endl;
	}
}


void loadAndBindTexture(std::string textureFilename)
{

	// Initialize IL
	ilInit();
	// Initialize ILU
	iluInit();
	// Initialize ILUT with OpenGL support.
	ilutRenderer(ILUT_OPENGL);
	
	ILboolean imageLoaded;
	ILuint ImageName;	

	glGenTextures(1, &textureID);
	ilGenImages(1,&ImageName);

	errorNum = ilGetError();
	if(errorNum != IL_NO_ERROR)
	{
			errorStr = iluErrorString(errorNum);
			std::cout << errorStr;
	}

	ilBindImage(ImageName);
	imageLoaded =  ilLoadImage(textureFilename.c_str());

	textureID = ilutGLBindTexImage();

	errorNum = ilGetError();
	if(errorNum != IL_NO_ERROR)
	{
			std::cout << iluErrorString(errorNum);;
	}

	ilDeleteImages(1,&ImageName);
	
	errorNum = ilGetError();
	if(errorNum != IL_NO_ERROR)
	{
			std::cout << iluErrorString(errorNum);;
	}	
}




void drawColorCube()
{

	glBegin(GL_QUADS);

			//right Side
			glNormal3f(1,0,0);
			glColor3f(1.0,1.0,1.0);	glVertex3f(4,4,4);
			glColor3f(1.0,1.0,0.0);	glVertex3f(4,4,-4);
			glColor3f(1.0,0.0,0.0);	glVertex3f(4,-4,-4);
			glColor3f(1.0,0.0,1.0);	glVertex3f(4,-4,4);

			//left Side
			glNormal3f(-1,0,0);	
			glColor3f(0.0,1.0,1.0);	glVertex3f(-4,4,4);	
			glColor3f(0.0,1.0,0.0);	glVertex3f(-4,4,-4);	
			glColor3f(0.0,0.0,0.0);	glVertex3f(-4,-4,-4);	

			glColor3f(0.0,0.0,1.0);	glVertex3f(-4,-4,4);
			//TopSide
			
			glNormal3f(0,1,0);
			glColor3f(0.0,1.0,0.0);	glVertex3f(-4,4,-4);
			glColor3f(0.0,1.0,1.0);	glVertex3f(-4,4,4);	
			glColor3f(1.0,1.0,1.0);	glVertex3f(4,4,4);
			glColor3f(1.0,1.0,0.0);	glVertex3f(4,4,-4);
			
			//Bottom Side
			glNormal3f(0,-1,0);
			glColor3f(0.0,0.0,0.0);	glVertex3f(-4,-4,-4);
			glColor3f(0.0,0.0,1.0);	glVertex3f(-4,-4,4);
			glColor3f(1.0,0.0,1.0);	glVertex3f(4,-4,4);
			glColor3f(1.0,0.0,0.0);	glVertex3f(4,-4,-4);

			// Front Face		
			glNormal3f(0,0,1);
			glColor3f(1.0,1.0,1.0); glVertex3f(4,4,4);	
			glColor3f(1.0,0.0,1.0); glVertex3f(4,-4,4);
			glColor3f(0.0,0.0,1.0); glVertex3f(-4,-4,4);
			glColor3f(0.0,1.0,1.0);glVertex3f(-4,4,4);
		
			//Back Face
			glNormal3f(0,0,-1);
			glColor3f(1.0,1.0,0.0);	glVertex3f(4,4,-4);
			glColor3f(1.0,0.0,0.0);	glVertex3f(4,-4,-4);
			glColor3f(0.0,0.0,0.0);	glVertex3f(-4,-4,-4);
			glColor3f(0.0,1.0,0.0);	glVertex3f(-4,4,-4);

		glEnd();

}

void drawTexturedCube()
{

	glBegin(GL_QUADS);

	//right Side
	glColor3f(1.0,1.0,1.0);
	glNormal3f(1,0,0);
	glTexCoord2f(1.0,1.0);;	glVertex3f(4,4,4);
	glTexCoord2f(1.0,0.0);	glVertex3f(4,4,-4);
	glTexCoord2f(0.0,0.0);	glVertex3f(4,-4,-4);
	glTexCoord2f(0.0,1.0);;	glVertex3f(4,-4,4);

	//left Side
	glNormal3f(-1,0,0);	
	glTexCoord2f(1.0,1.0);	glVertex3f(-4,4,4);	
	glTexCoord2f(1.0,0.0);	glVertex3f(-4,4,-4);	
	glTexCoord2f(0.0,0.0);	glVertex3f(-4,-4,-4);	
	glTexCoord2f(0.0,1.0);  glVertex3f(-4,-4,4);

	//TopSide
	glNormal3f(0,1,0);
	glTexCoord2f(0.0,0.0);	glVertex3f(-4,4,-4);
	glTexCoord2f(0.0,1.0);	glVertex3f(-4,4,4);	
	glTexCoord2f(1.0,1.0);	glVertex3f(4,4,4);
	glTexCoord2f(1.0,0.0);;	glVertex3f(4,4,-4);

	//Bottom Side
	glNormal3f(0,-1,0);
	glTexCoord2f(0.0,0.0);	glVertex3f(-4,-4,-4);
	glTexCoord2f(0.0,1.0);	glVertex3f(-4,-4,4);
	glTexCoord2f(1.0,1.0);	glVertex3f(4,-4,4);
	glTexCoord2f(1.0,0.0);	glVertex3f(4,-4,-4);

	// Front Face		
	glNormal3f(0,0,1);
	glTexCoord2f(1.0,1.0);	glVertex3f(4,4,4);	
	glTexCoord2f(1.0,0.0);	glVertex3f(4,-4,4);
	glTexCoord2f(0.0,0.0);	glVertex3f(-4,-4,4);
	glTexCoord2f(0.0,1.0);	glVertex3f(-4,4,4);

	//Back Face
	glNormal3f(0,0,-1);
	glTexCoord2f(1.0,1.0);	glVertex3f(4,4,-4);
	glTexCoord2f(1.0,0.0);	glVertex3f(4,-4,-4);
	glTexCoord2f(0.0,0.0);	glVertex3f(-4,-4,-4);
	glTexCoord2f(0.0,1.0);	glVertex3f(-4,4,-4);

	glEnd();
}

