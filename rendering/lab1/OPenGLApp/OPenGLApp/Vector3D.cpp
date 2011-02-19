#include "Vector3D.h"

Vector3D::Vector3D(void)
{
	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
}


Vector3D::Vector3D(GLfloat x, GLfloat y, GLfloat z){
	values[0] = x;
	values[1] = y;
	values[2] = z;
}
Vector3D::~Vector3D(void)
{
}

const GLfloat* Vector3D::getArrayPtr() const{
	//return  (const GLfloat*) &values;
	//const GLfloat* val;
	//val = &values[0];
	//return &values;
	return  &values[0];
	//return  (const GLfloat*) values;
}
void Vector3D::set(GLfloat x, GLfloat y, GLfloat z){

	values[0] = x;
	values[1] = y;
	values[2] = z;

}
void Vector3D::update(GLfloat x, GLfloat y, GLfloat z){

	values[0] += x;
	values[1] += y;
	values[2] += z;
}

void Vector3D::normalise(){
	// normalises this vector
 GLfloat magnitude = getMagnitude();
 values[0] = values[0] / magnitude;
 values[1] = values[1] / magnitude;
 values[2] = values[2] / magnitude;

}

Vector3D Vector3D:: getNormal(){
// returns a normalised version of this Vector;

	Vector3D result(values[0], values[1], values[2]);

	result.normalise();

	return result;
}

GLfloat  Vector3D::getValue(GLint index) const{
	if(index > 2 || index < 0){

		throw("Vector 3D index out of bounds: index = " + index);
	}

	return values[index];


}
GLfloat Vector3D::getDotProduct(const Vector3D *vector2){

	GLfloat dotProduct = 0.0;


	for(int i = 0; i < 3; i++){
		dotProduct += values[i] * vector2->getValue(i); 
	}

	return dotProduct;

}
GLfloat Vector3D::getMagnitude(){

	return sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]);

}
GLfloat Vector3D::getAngle(const Vector3D *vector2) {

	GLfloat angle;

	GLfloat mag1 = getMagnitude();
	GLfloat mag2 = ((Vector3D*)vector2)->getMagnitude();
	GLfloat cosValue = getDotProduct(vector2) / (mag1 * mag2);

	angle = acos(cosValue);
	return angle;
}

GLvoid Vector3D::MultiplyMatrix(GLfloat* matrix){
	// Multiplies the Vector by the 4x4 matrix pointed to by  matrix

	//resulting vecotr v = Mc

	GLfloat current[3];
	
	current[0] = values[0];
	current[1] = values[1];
	current[2] = values[2];
	//current[3] = values[3];


	values[0] = (matrix[0] * current[0]) + (matrix[4] * current[1]) + (matrix[8] * current[2]);
	values[1] = (matrix[1] * current[0]) + (matrix[5] * current[1]) + (matrix[9] * current[2]);
	values[2] = (matrix[2] * current[0]) + (matrix[6] * current[1]) + (matrix[10] * current[2]);

		GLfloat temp[3];

		for(int i = 0; i < 3 ; i++){
			if(values[i] >= 0){
				temp[i] = floor(values[i] * 10000.0f );
			}else{
				temp[i] = ceil(values[i] * 10000.0f );
			}
				values[i] = temp[i] / 10000.0f;

		}


//	values[
	
}


GLfloat &Vector3D::operator[](int i){
	
	if( i > 2 || i <0){
		throw("Invalid Index passed to Vector");
	
	}	
	return values[i];

}
GLfloat  &Vector3D::operator[](int i) const{
	
	if( i > 2 || i <0){
		throw("Invalid Index passed to Vector");
	
	}	
	return (const float)values[i];

}

Vector3D Vector3D::operator+(const Vector3D vector2) const{

	Vector3D result;

	result[0] = values[0] + vector2[0];
	result[1] = values[1] + vector2[1];
	result[2] = values[1] + vector2[2];

	return result;
}

Vector3D Vector3D::operator-(const Vector3D vector2) const{

	Vector3D result;

	result[0] = values[0] - vector2[0];
	result[1] = values[1] - vector2[1];
	result[2] = values[2] - vector2[2];

	return result;
}





Vector3D Vector3D::getCrossProduct(const Vector3D vector2){
	


	Vector3D crossProduct;

	// Need to make sure neither vector is a null vector
	// If one is translat each +1 along the x axis
	//	the resulting crsoo product will be the same


	crossProduct[0] = values[1] * vector2[2] - values[2] * vector2[1];
	crossProduct[1] = values[2] * vector2[0] - values[0] * vector2[2];
	crossProduct[2] = values[0] * vector2[1] - values[1] * vector2[0];


	return crossProduct;
}








GLfloat Vector3D::getAngleDegrees(const Vector3D *vector2){

	GLfloat angleRadians = getAngle(vector2);

	return angleRadians * (180 / M_PI);

}
