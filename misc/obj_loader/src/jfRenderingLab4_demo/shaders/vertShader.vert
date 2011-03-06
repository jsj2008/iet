/*
uniform mat4 modelMat; // custom matrix passed in, the model_view matrix without the model
uniform vec3 eyew;
uniform int doReflect; //pass a value in to switch between reflect and refract

varying vec3 reflectv; //pass pervertex reflected ray to rasterizer
varying vec3 refractv; //pass pervertex refracted ray to rasterizer

//For chromatic dispersion
varying vec3 refractvRed; 
varying vec3 refractvBlue; 
varying vec3 refractvGreen; 

varying float reflectionCoeff;

void main()
{
	if(doReflect==0)
	{
		//Reflection
		vec4 positionw = modelMat*gl_Vertex;
		vec4 normw = normalize(modelMat * vec4(gl_Normal,0.0)); 
		vec3 lightw = normalize(positionw.xyz - eyew);
		
		reflectv = reflect(lightw,normw.xyz); //this does reflection

//		reflectv = clamp(reflectv, 0, 1);
				
		gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
	}
	else if(doReflect==1)
	{
		//Refraction
		vec4 positionw = modelMat*gl_Vertex;
		vec4 normw = normalize(modelMat * vec4(gl_Normal,0.0)); 
		vec3 lightw = normalize(positionw.xyz - eyew);
		float eta = 0.33;
		
		refractv = refract(lightw, normw.xyz, eta); //this does refraction
				
		gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
	}
	else if(doReflect==2)
	{
		//Reflection and refraction
		//Monochromatic dispersion
		vec4 positionw = modelMat*gl_Vertex;
		vec4 normw = normalize(modelMat * vec4(gl_Normal,0.0)); 
		vec3 lightw = normalize(positionw.xyz - eyew);
//		float eta = 0.15;
		float eta = 0.33;

		//float eta = 0.87;

		reflectv = reflect(lightw,normw.xyz); //this does reflection
		refractv = refract(lightw,normw.xyz, eta); //this does refraction
				
		gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;

		//Fresnel stuff.
		vec3 I = -lightw;
		vec3 N = normw;
		float r_zero = ( ((1-eta) * (1-eta)) / ((eta+1) * (eta+1)) );
		float fresnelPower = 5.0;
		reflectionCoeff = max(0, min(1, r_zero + (1.0-r_zero) * pow((1.0 - dot(I, N)), fresnelPower)));
	}
	else if(doReflect==3)
	{
		//Reflection and refraction
		//Chromatic dispersion

		vec4 positionw = modelMat*gl_Vertex;
		vec4 normw = normalize(modelMat * vec4(gl_Normal,0.0)); 
		vec3 lightw = normalize(positionw.xyz - eyew);

		float eta = 0.33;
		float etaRed = 0.29;
		float etaGreen = 0.33;
		float etaBlue = 0.37;

		reflectv = reflect(lightw, normw.xyz); //this does reflection
		refractvRed = refract(lightw, normw.xyz, etaRed); //this does refraction
		refractvGreen = refract(lightw, normw.xyz, etaGreen); //this does refraction
		refractvBlue = refract(lightw, normw.xyz, etaBlue); //this does refraction
				
		gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;

		//Fresnel stuff.
		vec3 I = -lightw;
		vec3 N = normw;
		float r_zero = ( ((1-eta) * (1-eta)) / ((eta+1) * (eta+1)) );
		float fresnelPower = 5.0;
		reflectionCoeff = max(0, min(1, r_zero + (1.0-r_zero) * pow((1.0 - dot(I, N)), fresnelPower)));
	}
}
*/

/*
varying vec3 v;
varying vec3 l;

uniform vec4 L;

attribute vec3 rm_Tangent;
attribute vec3 rm_Bitangent;

void main(void)
{
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	vec4 camera = gl_ModelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0);
	vec3 view = normalize(camera.xyz - glVertex.xyz);
	vec3 light = normaize(gl_ModelViewMatrixTranspose*L).xyz;

	mat3 TBNinv(rm_Tangent, rm_Bitangent, gl_Normal); //Maps from object space to world space
	l = TBNinv * light;
	v = TBNinv * view;
}
*/

/*
uniform vec3 LightPosition;
//attribute vec3 Tangent;

varying vec3 LightDir;
varying vec3 EyeDir;

vec3 calcTangent()
{
	vec3 tangent;
	vec3 c1 = cross(gl_Normal, vec3(0.0, 0.0, 1.0));
	vec3 c2 = cross(gl_Normal, vec3(0.0, 1.0, 0.0));
	if(length(c1)>length(c2))
	{
		tangent = c1;
	}
	else
	{
		tangent = c2;
	}
	tangent = normalize(tangent);
	return tangent;
}

void main()
{
	vec3 Tangent = calcTangent();

	EyeDir = vec3(gl_ModelViewMatrix * gl_Vertex);
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * Tangent);

	vec3 b = cross(n, t); //binormal

//	mat3 tangentmat = mat3( tangent, binormal, normal );
//	LightDir

	vec3 v; //temp variable
	v.x = dot(LightPosition, t);
	v.y = dot(LightPosition, b);
	v.z = dot(LightPosition, n);
	LightDir = normalize(v);
	v.x = dot(EyeDir, t);
	v.y = dot(EyeDir, b);
	v.z = dot(EyeDir, n);
	EyeDir = normalize(v);
}
*/

vec3 calcTangent()
{
	vec3 tangent;
	vec3 c1 = cross(gl_Normal, vec3(0.0, 0.0, 1.0));
	vec3 c2 = cross(gl_Normal, vec3(0.0, 1.0, 0.0));
	if(length(c1)>length(c2))
	{
		tangent = c1;
	}
	else
	{
		tangent = c2;
	}
	tangent = normalize(tangent);
	return tangent;
}

//attribute vec3 tangent;
varying vec3 lightVec;
varying vec3 halfVec;
varying vec3 eyeVec;


void main()
{
	vec3 tangent = calcTangent();

	gl_TexCoord[0] =  gl_MultiTexCoord0;

	// Building the matrix Eye Space -> Tangent Space
	vec3 n = normalize (gl_NormalMatrix * gl_Normal);
	vec3 t = normalize (gl_NormalMatrix * tangent);
	vec3 b = cross (n, t);

	vec3 vertexPosition = vec3(gl_ModelViewMatrix *  gl_Vertex);
	vec3 lightDir = normalize(gl_LightSource[0].position.xyz - vertexPosition);

	// transform light and half angle vectors by tangent basis
	vec3 v;
	v.x = dot (lightDir, t);
	v.y = dot (lightDir, b);
	v.z = dot (lightDir, n);
	lightVec = normalize (v);

	v.x = dot (vertexPosition, t);
	v.y = dot (vertexPosition, b);
	v.z = dot (vertexPosition, n);
	eyeVec = normalize (v);

	vertexPosition = normalize(vertexPosition);

	/* Normalize the halfVector to pass it to the fragment shader */
	vec3 halfVector = normalize((vertexPosition + lightDir) / 2.0);
	v.x = dot (halfVector, t);
	v.y = dot (halfVector, b);
	v.z = dot (halfVector, n);
	halfVec = normalize (v);

	gl_Position = ftransform();
}

