#ifndef  JFCORE_H
#define  JFCORE_H

//TODO : Add support for multiple platforms.
#ifdef __linux__

#include <stdint.h>

typedef uint32_t jfUint32;

#endif

#ifdef __WIN32_

typedef __uint32 jfUint32;

#endif

//My own types. So that I can easily change them.
#include <string>
typedef std::string jfString;
typedef int jfFaceId;
typedef int jfVertexId;
typedef int jfVertexTextureId;
typedef int jfNormalId;

//Memory Allocation stuff.
#define JF_NEW new
#define JF_SAFE_DELETE(x) if(x) delete x; x=NULL;
#define JF_SAFE_DELETE_ARRAY(x) if (x) delete [] x; x=NULL; 

//Floating point precision stuff.
#include <math.h>
#include <float.h>
typedef float jfReal;
#define jfRealSqrt(x) sqrtf(x)
#define jfRealPow(x,y) powf(x,y)
#define jfRealAbs(x) fabs(x)

#endif   // JFCORE_H
