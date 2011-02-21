#pragma once

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
#include "GL/glew.h" // glew for saccess to shader functionality
#include "GL/glut.h"	// GLUT
#include <GL/glu.h>		// for gluPerspective & gluLookAt
#include <iostream>		// I/O
#include  <math.h>

#endif

#include "Vector3D.h"

#ifndef M_PI 
#define M_PI 3.1415926535897932384626433832795f
#endif

//#ifndef COMMON_HEADER
//#define COMMON_HEADER
//#include "CommonStuff.h"
//#endif



class Camera
{

	Vector3D position;
	Vector3D zOrientation; // This is the direction tha camer is facing
	Vector3D xOrientation; // This is the up (y) vector cmoing out of the top of the camer
	Vector3D yOrientation; // this is the x vector coming out of the right of the camera


	//GLfloat roll;
	//GLfloat pitch;

	//GLfloat yaw;

	


	

public:
	Camera(void);
	bool setCameraPosition(GLfloat x, GLfloat y, GLfloat z);
	bool updateCameraPosition(GLfloat x, GLfloat y, GLfloat z);
	bool moveCamera(GLfloat moveValue);
	bool pitchCamera(GLfloat degrees);
	bool rollCamera(GLfloat degrees);
	bool yawCamera(GLfloat degrees);
	bool strafeCamera(GLfloat moveValue);
	bool verticalStrafeCamera(GLfloat moveValue);
	bool positionCamera();

	bool lookAt(GLfloat x, GLfloat y, GLfloat z);

	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();


	void init();
	


	
public:
	~Camera(void);
};
