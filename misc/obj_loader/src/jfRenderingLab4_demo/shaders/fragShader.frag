/*
varying vec3 reflectv;
varying vec3 refractv;
uniform samplerCube myMap;

uniform int doReflect; //pass a value in to switch between reflect and refract

varying float reflectionCoeff;

//For chromatic dispersion
varying vec3 refractvRed; 
varying vec3 refractvBlue; 
varying vec3 refractvGreen; 

void main(void)
{
	if(doReflect==0)
	{
		//reflection solution only 
		vec4 R = textureCube(myMap,reflectv);
		gl_FragColor = R; 
	}
	else if(doReflect==1)
	{
		//refraction solution only
		vec4 R = textureCube(myMap,refractv);
		if(length(refractv) < 0)
		{
			gl_FragColor = textureCube(myMap, vec3(0,0,0));
		}
		else if(length(refractv) > 1)
		{
			gl_FragColor = textureCube(myMap, vec3(0,0,0));
		}
		else
		{
			gl_FragColor = R; 
		}
	}
	else if(doReflect==2)
	{
		vec4 reflectedColour = textureCube(myMap,reflectv);
		vec4 refractedColour = textureCube(myMap,refractv);
		//Linear interpolation between the colours.
		vec3 colour = mix(refractedColour, reflectedColour, reflectionCoeff);

		colour = clamp(colour,0,1);
		gl_FragColor = vec4(colour, 1.0);
	}
	else if(doReflect==3)
	{
		vec4 reflectedColour = textureCube(myMap,reflectv);
		vec4 refractedColour;
		refractedColour.r = textureCube(myMap,refractvRed).r;
		refractedColour.b = textureCube(myMap,refractvBlue).b;
		refractedColour.g = textureCube(myMap,refractvGreen).g;
		//Linear interpolation between the colours.
		vec3 colour = mix(refractedColour, reflectedColour, reflectionCoeff);
		gl_FragColor = vec4(colour, 1.0);
	}
	//To DO: refraction + reflection
}

*/

/*
uniform vec4 ambientColour;
uniform vec4 diffuseColour;
uniform vec4 specularColour;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform float shininess;

varying vec3 v;
varying vec3 l;

void main(void)
{
	l = normalize(l);
	v = normalize(v);

	vec3 n = 2.0 * texture2D( normalTex, gl_TexCoord[0].st ).xyz - 1.0; //Tangent space normal
	vec4 diffuseTerm = texture2D( diffuseTex, gl_TexCoord[0].st ) * diffuseColour * (max( 0.0, dot(n,l)));
	vec3 r = reflect(-l, n); //tangent-space reflection
	vec4 specularTerm = specularColour * pow(max(0.0,dot(r,v)), shininess);
	
	gl_FragColor = ambientColour + diffuseTerm + specularTerm;
}
*/

/*
uniform vec3 SurfaceColor; // = (0.7, 0.6, 0.18)
uniform float BumpDensity; // = 16.0
uniform float BumpSize;          // = 0.15
uniform float SpecularFactor; // = 0.5

//uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

varying vec3 LightDir;
varying vec3 EyeDir;

void main()
{
    vec3 litColor;
    vec2 c = BumpDensity * gl_TexCoord[0].st;
    vec2 p = fract(c) - vec2(0.5);
    float d, f;
    d = p.x * p.x + p.y * p.y;
    f = 1.0 / sqrt(d + 1.0);
    if (d >= BumpSize)
    {
		p = vec2(0.0); 
		f = 1.0; 
	}
    vec3 normDelta = vec3(p.x, p.y, 1.0) * f;
    litColor = SurfaceColor * max(dot(normDelta, LightDir), 0.0);
    vec3 reflectDir = reflect(LightDir, normDelta);
    float spec = max(dot(EyeDir, reflectDir), 0.0);
    spec = pow(spec, 6.0);
    spec *= SpecularFactor;
    litColor = min(litColor + spec, vec3(1.0));
    gl_FragColor = vec4(litColor, 1.0);
}

*/

uniform sampler2D normalTexture;
uniform sampler2D diffuseTexture;

// New bumpmapping
varying vec3 lightVec;
varying vec3 halfVec;
varying vec3 eyeVec;


void main()
{

	// lookup normal from normal map, move from [0,1] to  [-1, 1] range, normalize
	vec3 normal = 2.0 * texture2D (normalTexture, gl_TexCoord[0].st).rgb - 1.0;
	normal = normalize (normal);
	
	// compute diffuse lighting
	float lamberFactor= max (dot (lightVec, normal), 0.0) ;
	vec4 diffuseMaterial = 0.0;
	vec4 diffuseLight  = 0.0;
	
	// compute specular lighting
	vec4 specularMaterial ;
	vec4 specularLight ;
	float shininess ;
  
	// compute ambient
	vec4 ambientLight = gl_LightSource[0].ambient;	
	
	if (lamberFactor > 0.0)
	{
		diffuseMaterial = texture2D (diffuseTexture, gl_TexCoord[0].st);
		diffuseLight  = gl_LightSource[0].diffuse;
		
		// In doom3, specular value comes from a texture 
		specularMaterial =  vec4(1.0)  ;
		specularLight = gl_LightSource[0].specular;
		shininess = pow (max (dot (halfVec, normal), 0.0), 2.0)  ;
		 
		gl_FragColor =	diffuseMaterial * diffuseLight * lamberFactor ;
		gl_FragColor +=	specularMaterial * specularLight * shininess ;				
	
	}
	
	gl_FragColor +=	ambientLight;
	
}		
