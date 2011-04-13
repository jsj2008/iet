#include "ObjLoader.hpp"

namespace dynamx
{

	ObjLoader::ObjLoader()
	{
	}

	ObjLoader::~ObjLoader()
	{
	}


	/*
	void ObjLoader::HandleLine(const string& line, RigidBodyGeomery* geom)
	{
		cin
	}
	*/

	void ObjLoader::LoadFile(const std::string& filename, RigidBodyGeometry* geom)
	{
		geom->Reset();

		ifstream objFileP;
		objFileP.open(filename.c_str());

		if(!objFileP) 
		{
			assert(0 && "File could not be opened");
			return;
		}

		string str;
		while (getline(objFileP,str)) 
		{
//			objFileP >> output;
			stringstream iss(str);

			char type[2];
			type[0] = 0;
			type[1] = 0;
			iss >> type;

			if((type[0] == 'v') && (type[1] == 0))
			{
				Vertex v = geom->MakeVertex();
				real x,y,z;
				iss >> x >> y >> z;
				Point3 p(x,y,z);
				v.SetPos(p);
				geom->AddVertex(v);
			}
			else if((type[0] == 'f') && (type[1] == 0))
			{
				Face f = geom->MakeFace();
				VertexId id;
				while(!iss.eof())
				{
					iss >> id;
					f.AddVertexId(id);
				}
				geom->AddFace(f);
			}
			//TODO: Add more types such as normals
			
//			HandleLine(objFileP, str, geom);
//			cout<<output;
		}
		objFileP.close();
	}

}
