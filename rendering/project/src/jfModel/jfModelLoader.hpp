#ifndef  JFMODELLOADER_H
#define  JFMODELLOADER_H

#include <jfCore/jfCore.hpp>
#include <jfModel/jfModel.hpp>

/*
 * =====================================================================================
 *        Class: jfModelLoader
 *  Description:
 * =====================================================================================
 */
class jfModelLoader
{
	public:
		virtual ~jfModelLoader()
		{
		}

		virtual bool loadFromFile(jfString filename, jfModel* model) = 0;
		
	protected:
	private:
};


#endif   // JFMODELLOADER_H
