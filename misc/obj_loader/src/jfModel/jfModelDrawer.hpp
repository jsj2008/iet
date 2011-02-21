#ifndef  JFMODELDRAWER_H
#define  JFMODELDRAWER_H

#include <GL/glu.h>

#include <jfModel/jfModel.hpp>

/*
 * =====================================================================================
 *        Class: jfModelDrawer
 *  Description:
 * =====================================================================================
 */
class jfModelDrawer
{
	public:
		jfModelDrawer();
		
		virtual ~jfModelDrawer();

		virtual void draw(const jfModel& model) const;
		
	protected:
	private:
};


#endif   // JFMODELDRAWER_H
