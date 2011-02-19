#pragma once
#ifndef INCLUDE_GL
#define INCLUDE_GL
#include "gl/glut.h"	// GLUT
#include <gl/glu.h>		// for gluPerspective & gluLookAt

#include  <math.h>
#endif
#ifndef M_PI 
#define M_PI 3.1415926535897932384626433832795f
#endif
						// Header File For The GLaux Library


class Vector3D
{

	GLfloat values[3];


public:
	void normalise();
	Vector3D getNormal();
	GLfloat getDotProduct(const Vector3D *vector2);
	
	GLfloat getMagnitude();
	GLfloat getAngle(const Vector3D *vector2) ;
	GLfloat getAngleDegrees(const Vector3D *vector2) ;
	GLfloat getValue(GLint index) const;
	void set(GLfloat x, GLfloat y, GLfloat z);
	void update(GLfloat x, GLfloat y, GLfloat z);
	Vector3D(void);
	Vector3D(GLfloat x, GLfloat y, GLfloat z);
	GLvoid MultiplyMatrix(GLfloat* matrix);
	const GLfloat* getArrayPtr() const;
	//GLfloat operator[](int i);
	GLfloat &operator[](int i);

	GLfloat  &operator[](int i) const;

	//Vector3D operator+(Vector3D vector2);
	Vector3D  operator+(const Vector3D vector2) const;
	Vector3D  operator-(const Vector3D vector2) const;
	//Vector3D operator-(Vector3D vector2);
	
	// Need to implement the following


	Vector3D getCrossProduct(const Vector3D vector2) ;
	Vector3D getPlaneNormal(const Vector3D vector2, const Vector3D vector3 ) ;

	// overide plus for float integer and double
	// Vector addition and subtraction
	// matrinx multiply (specify matrix ordinality)



//	GLfloat getDistance(Vector3D vector2);

public:
	~Vector3D(void);
};
