// simple toon vertex shader
// www.lighthouse3d.com


uniform mat4 modelMat;
uniform mat3 invModelMat;
uniform vec3 eyew;
varying vec3 reflectw;

void main()
{
	vec4 positionw = modelMat*gl_Vertex;
	vec3 normw = normalize(modelMat * vec4(gl_Normal,0.0));
	vec3 lightw = normalize(positionw - eyew);
	reflectw = reflect(lightw,normw);
	gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
	
}
