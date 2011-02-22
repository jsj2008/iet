#ifndef  OBJLOADER_H
#define  OBJLOADER_H

#include <sstream>
#include <iostream>
#include <fstream>

#include <dynamx/RigidBodyGeometry.hpp>

using namespace std;

namespace dynamx
{
	class ObjLoader
	{
		public:

			ObjLoader();

			~ObjLoader();

			void LoadFile(const std::string& filename, RigidBodyGeometry* geom);

		private:	
	};
}

#endif   // OBJLOADER_H
