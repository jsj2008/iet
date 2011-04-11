#ifndef  JFOBJLOADER_H
#define  JFOBJLOADER_H

#include <sstream>
#include <string>
#include <fstream>

#include <jfAlgebra/jfPoint3.hpp>
#include <jfAlgebra/jfVector3.hpp>
#include <jfCore/jfCore.hpp>
#include <jfModel/jfModel.hpp>
#include <jfModel/jfModelLoader.hpp>
#include <jfLog/jfLogger.hpp>

/*
 * =====================================================================================
 *        Class: jfObjLoader
 *  Description:
 * =====================================================================================
 */
class jfObjLoader : public jfModelLoader
{
	public:
		jfObjLoader();

		virtual ~jfObjLoader();

		virtual bool loadFromFile(jfString filename, jfModel* model);
		
	protected:
	private:
};



#endif   // JFOBJLOADER_H
