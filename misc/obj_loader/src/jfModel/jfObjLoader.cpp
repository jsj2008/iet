#include "jfObjLoader.hpp"

jfObjLoader::jfObjLoader()
{
}

jfObjLoader::~jfObjLoader()
{
}

bool jfObjLoader::loadFromFile(jfString filename, jfModel* model)
{
	std::ifstream objFileP;
	objFileP.open(filename.c_str());

	if(!objFileP) 
	{
		std::stringstream out;
		out<<"Obj file could not be opened"<<filename;
		jfLog(JF_LOG_ERROR, out.str());
		assert(0 && out.str().c_str());
		return false;
	}

	std::string str;
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
			jfVertex v = model->makeVertex();
			jfReal x,y,z;
			iss >> x >> y >> z;
			jfPoint3 p(x,y,z);
			v.setPos(p);
			model->addVertex(v);
		}
		else if((type[0] == 'v') && (type[1] == 't'))
		{
			jfVertexTexture t = model->makeVertexTexture();

			//TODO: Add support for w
			jfReal u,v;
			iss >> u >> v;
			t.setU(u);
			t.setV(v);
			model->addVertexTexture(t);
		}
		else if((type[0] == 'v') && (type[1] == 'n'))
		{
			jfNormal n = model->makeNormal();

			jfReal x,y,z;
			iss >> x >> y >> z;
			n.set(x,y,z);
			model->addNormal(n);
		}
		else if((type[0] == 'f') && (type[1] == 0))
		{
			jfFace f = model->makeFace();
			jfVertexId id;
			while(!iss.eof())
			{
				iss >> id;
				f.addVertexId(id);
				if(iss.peek() == '/')
				{
					char delim;
					iss >> delim;

					//Vertex Texture
					jfVertexTextureId texid;
					iss >> texid;
					f.addVertexTextureId(texid);
					if(iss.peek() == '/')
					{
						char delim;
						iss >> delim;

						//Vertex Normal
						jfNormalId nid;
						iss >> nid;
						f.addNormalId(nid);
					}
				}
			}
			model->addFace(f);
		}
	}
	objFileP.close();

	model->createList();
}
