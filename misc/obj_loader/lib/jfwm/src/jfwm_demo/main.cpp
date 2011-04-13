#include <jfwm/jfWindowManager.hpp>
#include <jfwm/jfSDLWindowManager.hpp>

int main(void)
{
	jfWindowManager* wm = new jfSDLWindowManager();
	wm->init();
	wm->createWindow("test");
	for(int i = 0 ; i < 10000 ; i++)
	{
		;
	}
	delete wm;
	return 0;
}
