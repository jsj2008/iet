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


uniform vec3 SurfaceColor; // = (0.7, 0.6, 0.18)
uniform float BumpDensity; // = 16.0
uniform float BumpSize;          // = 0.15
uniform float SpecularFactor; // = 0.5

uniform int doReflect; //pass a value in to switch between reflect and refract

//uniform sampler2D diffuseTexture;
//uniform sampler2D normalTexture;
uniform samplerCube myMap;
uniform sampler2D myBumpMap;

varying vec3 LightDir;
varying vec3 EyeDir;

void main()
{
	if(doReflect==0)
	{
		//Reflection without cubemap
		vec3 litColor;
		vec2 c = BumpDensity * gl_TexCoord[0].st;

		//vec2 p = fract(c) - vec2(0.5);
		vec2 p = fract(c);
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
	else if(doReflect==1)
	{
		//Reflection
		vec3 litColor;
		vec2 c = BumpDensity * gl_TexCoord[0].st;

		//vec2 p = fract(c) - vec2(0.5);
		vec2 p = fract(c);

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
		vec4 R = textureCube(myMap,vec4(litColor,1.0));
		gl_FragColor = R; 

//		gl_FragColor = vec4(litColor, 1.0);
	}
	else if(doReflect==2)
	{
		//Refraction
		vec3 litColor;
		vec2 c = BumpDensity * gl_TexCoord[0].st;

		//vec2 p = fract(c) - vec2(0.5);
		vec2 p = fract(c);
		float d, f;
		d = p.x * p.x + p.y * p.y;
		f = 1.0 / sqrt(d + 1.0);
		if (d >= BumpSize)
		{
			p = vec2(0.0); 
			f = 1.0; 
		}
		float eta = 0.33;

		vec3 normDelta = vec3(p.x, p.y, 1.0) * f;
		litColor = SurfaceColor * max(dot(normDelta, LightDir), 0.0);
		vec3 refractDir = refract(LightDir, normDelta, eta);
		float spec = max(dot(EyeDir, refractDir), 0.0);
		spec = pow(spec, 6.0);
		spec *= SpecularFactor;
		litColor = min(litColor + spec, vec3(1.0));
//		vec4 R = textureCube(myMap,vec4(litColor,1.0));
//		gl_FragColor = R; 
		vec4 R = textureCube(myMap,litColor);

		gl_FragColor = R; 
/*
		if((litColor) < 0)
		{
			gl_FragColor = textureCube(myMap, vec3(0,0,0));
		}
		else if((litColor) > 1)
		{
			gl_FragColor = textureCube(myMap, vec3(0,0,0));
		}
		else
		{
			gl_FragColor = R; 
		}
*/
	}
	else if(doReflect==3)
	{
		//Reflection + refraction
		vec3 litColor;
		vec2 c = BumpDensity * gl_TexCoord[0].st;

		//vec2 p = fract(c) - vec2(0.5);
		vec2 p = fract(c);
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

		//Reflect

		float eta = 0.33;


		//Fresnel stuff.
		vec3 I = -LightDir;
		vec3 N = normDelta;
		float r_zero = ( ((1-eta) * (1-eta)) / ((eta+1) * (eta+1)) );
		float fresnelPower = 5.0;
		float reflectionCoeff = max(0, min(1, r_zero + (1.0-r_zero) * pow((1.0 - dot(I, N)), fresnelPower)));

		vec3 reflectDir = reflect(LightDir, normDelta);
		float specReflect = max(dot(EyeDir, reflectDir), 0.0);
		specReflect = pow(specReflect, 6.0);
//		specReflect = pow(specReflect, (reflectionCoeff)*6);
		specReflect *= SpecularFactor;
		vec4 reflectedColour = textureCube(myMap,reflectDir);
		//Refract
		vec3 refractDir = refract(LightDir, normDelta, eta);

		float specRefract = max(dot(EyeDir, refractDir), 0.0);
		specRefract = pow(specRefract, 6.0);
		//specRefract = pow(specRefract, (1-reflectionCoeff)*6);
		specRefract *= SpecularFactor;
		//Mix
		vec4 refractedColour = textureCube(myMap,refractDir);
		//Linear interpolation between the colours.
		vec3 colour = mix(refractedColour, reflectedColour, reflectionCoeff);

		float spec = specReflect + specRefract * 0.5; //Average

		litColor = min(litColor + spec, vec3(1.0));

//		vec4 R = textureCube(myMap,vec4(litColor,1.0));
//		gl_FragColor = R; 

		//Linear interpolation between the colours.
		vec3 c0 = mix(refractedColour, reflectedColour, reflectionCoeff);
		gl_FragColor = vec4(c0, 1.0);


//		gl_FragColor = clamp(max(vec4(colour, 1.0), litColor), 0, 1);
//		gl_FragColor = vec4(max(colour, litColor),1.0);
//		gl_FragColor = vec4(colour,1.0);
	}
	else if(doReflect==4)
	{
		//Chromatic Dispersion
		vec3 litColor;
		vec2 c = BumpDensity * gl_TexCoord[0].st;

		//vec2 p = fract(c) - vec2(0.5);
		vec2 p = fract(c);
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

		//Reflect
		float eta = 0.33;
		float etaRed = 0.29;
		float etaGreen = 0.33;
		float etaBlue = 0.37;

		//Fresnel stuff.
		vec3 I = -LightDir;
		vec3 N = normDelta;
		float r_zero = ( ((1-eta) * (1-eta)) / ((eta+1) * (eta+1)) );
		float fresnelPower = 5.0;
		float reflectionCoeff = max(0, min(1, r_zero + (1.0-r_zero) * pow((1.0 - dot(I, N)), fresnelPower)));

		vec3 reflectDir = reflect(LightDir, N);
		float specReflect = max(dot(EyeDir, reflectDir), 0.0);
		specReflect = pow(specReflect, 6.0);
//		specReflect = pow(specReflect, (reflectionCoeff)*6);
		specReflect *= SpecularFactor;
		vec4 reflectedColour = textureCube(myMap,reflectDir);
		//Refract
		vec3 refractDir = refract(LightDir, N, eta);

		vec3 refractDirRed = refract(LightDir, N, etaRed);
		vec3 refractDirGreen = refract(LightDir, N, etaGreen);
		vec3 refractDirBlue = refract(LightDir, N, etaBlue);

		float specRefract = max(dot(EyeDir, refractDir), 0.0);
		specRefract = pow(specRefract, 6.0);
		//specRefract = pow(specRefract, (1-reflectionCoeff)*6);
		specRefract *= SpecularFactor;

		float specRefractRed = max(dot(EyeDir, refractDirRed), 0.0);
		specRefractRed = pow(specRefractRed, 6.0);
		specRefractRed *= SpecularFactor;

		float specRefractGreen = max(dot(EyeDir, refractDirGreen), 0.0);
		specRefractGreen = pow(specRefractGreen, 6.0);
		specRefractGreen *= SpecularFactor;

		float specRefractBlue = max(dot(EyeDir, refractDirBlue), 0.0);
		specRefractBlue = pow(specRefractBlue, 6.0);
		specRefractBlue *= SpecularFactor;

		//Mix
		vec4 refractedColour;
		refractedColour.r = textureCube(myMap,refractDirRed).r;
		refractedColour.b = textureCube(myMap,refractDirBlue).b;
		refractedColour.g = textureCube(myMap,refractDirGreen).g;
//		vec4 refractedColour = textureCube(myMap,refractDir);
		//Linear interpolation between the colours.
		vec3 colour = mix(refractedColour, reflectedColour, reflectionCoeff);

		float spec = specReflect + specRefract * 0.5; //Average

/*
		litColor.r += specRefractRed;
		litColor.g += specRefractGreen;
		litColor.b += specRefractBlue;
*/

		litColor.r = specRefractRed;
		litColor.g = specRefractGreen;
		litColor.b = specRefractBlue;

		litColor = min(litColor + spec, vec3(1.0));
//		litColor = min(litColor + colour, vec3(1.0));


//		vec4 R = textureCube(myMap,vec4(litColor,1.0));
//		gl_FragColor = R; 


//		gl_FragColor = textureCube(myMap,vec4(colour,1.0));
//		gl_FragColor = vec4(colour, 1.0);

		//gl_FragColor = vec4(max(colour, litColor),1.0);
//		gl_FragColor = vec4(litColor, 1.0);

//		vec4 R = textureCube(myMap,vec4(litColor,1.0));
//		gl_FragColor = R; 

		//Linear interpolation between the colours.
		vec3 c0 = mix(refractedColour, reflectedColour, reflectionCoeff);
		gl_FragColor = vec4(c0, 1.0);

	}

}

/*

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
*/
