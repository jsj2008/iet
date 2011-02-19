
uniform float specIntensity;
uniform vec4 specColor;
uniform float t[2];
uniform vec4 colors[3];

varying vec3 normal, lightDir;

varying vec3 reflectw;
uniform samplerCube myMap;

void main(void)
{
	
	gl_FragColor = textureCube(myMap,reflectw);
	
}

