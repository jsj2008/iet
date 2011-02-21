#include "Camera.h"

Camera::Camera(void)
{
	position.set(0,0,10);

	// Orientation vector should always be normalised
	zOrientation.set(0,0,-1);
	yOrientation.set(0,1,0);
	xOrientation.set(1,0,0);

//	yawDegrees = 0;
}
void Camera::init(){
	position.set(0,0,10);

	// Orientation vector should always be normalised
	zOrientation.set(0,0,-1);
	yOrientation.set(0,1,0);
	xOrientation.set(1,0,0);
}

Camera::~Camera(void)
{
}

bool Camera::setCameraPosition(GLfloat x, GLfloat y, GLfloat z){
	position.set(x,y,z);


	return true;
}

bool Camera::moveCamera(GLfloat moveValue){
	
	GLfloat xMove = zOrientation.getValue(0) * moveValue;
	GLfloat yMove = zOrientation.getValue(1) * moveValue;
	GLfloat zMove = zOrientation.getValue(2) * moveValue;

	position.update(xMove,yMove,zMove);

	return false;
}
bool Camera::strafeCamera(GLfloat moveValue){
	GLfloat xMove = xOrientation.getValue(0) * moveValue;
	GLfloat yMove = xOrientation.getValue(1) * moveValue;
	GLfloat zMove = xOrientation.getValue(2) * moveValue;

	position.update(xMove,yMove,zMove);

	return false;

}

bool Camera::verticalStrafeCamera(GLfloat moveValue){
	GLfloat xMove = yOrientation.getValue(0) * moveValue;
	GLfloat yMove = yOrientation.getValue(1) * moveValue;
	GLfloat zMove = yOrientation.getValue(2) * moveValue;

	position.update(xMove,yMove,zMove);

	return false;

}
bool Camera::pitchCamera(GLfloat degrees){
		GLfloat rotationMatrix[16];
	glPushMatrix();
	glLoadIdentity();
//	glGetFloatv(GL_MODELVIEW_MATRIX,rotationMatrix);

	glRotatef(degrees,xOrientation.getValue(0),xOrientation.getValue(1),xOrientation.getValue(2));
	glGetFloatv(GL_MODELVIEW_MATRIX,rotationMatrix);
	zOrientation.MultiplyMatrix(rotationMatrix);
	yOrientation.MultiplyMatrix(rotationMatrix);

	glPopMatrix();



	return true;
}

bool Camera::rollCamera(GLfloat degrees){
		GLfloat rotationMatrix[16];
	glPushMatrix();
	glLoadIdentity();
//	glGetFloatv(GL_MODELVIEW_MATRIX,rotationMatrix);

	glRotatef(degrees,zOrientation.getValue(0),zOrientation.getValue(1),zOrientation.getValue(2));
	glGetFloatv(GL_MODELVIEW_MATRIX,rotationMatrix);
	zOrientation.MultiplyMatrix(rotationMatrix);
	xOrientation.MultiplyMatrix(rotationMatrix);

	glPopMatrix();

return true;
}




bool Camera::yawCamera(GLfloat degrees){
		GLfloat rotationMatrix[16];
	glPushMatrix();
	glLoadIdentity();
	

	glRotatef(degrees,yOrientation.getValue(0),yOrientation.getValue(1),yOrientation.getValue(2));
	glGetFloatv(GL_MODELVIEW_MATRIX,rotationMatrix);
	zOrientation.MultiplyMatrix(rotationMatrix);
	xOrientation.MultiplyMatrix(rotationMatrix);

	glPopMatrix();
	
	

	return true;
}


GLfloat Camera::getX(){
	return position[0];


}
GLfloat Camera::getY(){
	return position[1];
}
GLfloat Camera::getZ(){
	return position[2];
}

bool Camera::updateCameraPosition(GLfloat x, GLfloat y, GLfloat z){
	position.update(x,y,z);
	return true;
}


bool Camera::positionCamera(){
	

	gluLookAt(position[0],position[1],position[2],position[0] + (zOrientation[0] * 1000),position[1] + (zOrientation[1]*1000),position[2] + (zOrientation[2] * 1000),yOrientation[0],yOrientation[1],yOrientation[2]);
//	print();
	return true;
}






