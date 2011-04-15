#ifndef  JFQSPLATMODEL_H
#define  JFQSPLATMODEL_H

#include <jfPoint/qsplat/qsplat_model.h>

#include <string>

using namespace std;

/*
 * =====================================================================================
 *        Class: jfQSplatModel
 *  Description:
 * =====================================================================================
 */
class jfQSplatModel
{
	public:
		jfQSplatModel(string);

		virtual ~jfQSplatModel();
		
	protected:
		QSplat_Model* m_Model;
	private:
};


#endif   // JFQSPLATMODEL_H
