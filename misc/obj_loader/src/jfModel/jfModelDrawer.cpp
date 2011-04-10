
#include "jfModelDrawer.hpp"

jfModelDrawer::jfModelDrawer()
{
}

jfModelDrawer::~jfModelDrawer()
{
}

void jfModelDrawer::draw(const jfModel& model) const
{
	glPushMatrix();
	//glMultMatrixf(mat);
		model.draw();
	glPopMatrix();	
}
