#ifndef  CORE_H
#define  CORE_H

#include <math.h>
#include <assert.h>

#include <dynamx/CoreTypes.hpp>

#define real_sqrt(x) sqrtf(x)
#define real_pow(x,y) pow(x,y)
#define real_abs(x) fabs(x)
 
namespace dynamx
{
	typedef float real;

	const real PI = 3.14159265;

	//Degrees to radians
	inline real dtr(real degrees)
	{
		return (degrees*PI) / 180;
	}
}

#define DN_NOT_IMPLEMENTED assert(0 && "Not implemented");

#endif   // CORE_H
