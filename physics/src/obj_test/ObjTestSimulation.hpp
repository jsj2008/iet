#ifndef  OBJTESTSIMULATION_H
#define  OBJTESTSIMULATION_H

#include <vector>
#include <list>
#include <sstream>
#include <map>

#include <FTGL/ftgl.h>

#include "SDL/SDL_opengl.h"
#include <boost/shared_ptr.hpp>

#include <dynamx/Point3.hpp>
#include <dynamx/RigidBody.hpp>
#include <dynamx/RigidBodyGeometry.hpp>
#include <dynamx/ObjLoader.hpp>

#include <common/Simulation.hpp>
#include <common/Camera.hpp>
#include <common/Math.hpp>
#include <common/Colour.hpp>
#include <common/TextureLoader.hpp>
#include <common/FpsTimer.hpp>

#include <assert.h>

using namespace std;
using namespace boost;
using namespace dynamx;

const bool CAPFPS = true;
const int FPS = 60;

class ObjTestSimulation : public Simulation
{
	public:
		ObjTestSimulation();

		virtual ~ObjTestSimulation();

		virtual void VOnInit();

		virtual void VOnMainLoop();
		
	protected:
		void HandleInput();

		void CreateObjects();

		virtual void VOnRender();

		void InitGL();

		void SetupLighting();

		void DoCamera();

		void VOnUpdate();

		bool m_Finished;

		/*-----------------------------------------------------------------------------
		 *  Members
		 *-----------------------------------------------------------------------------*/
		Camera m_Camera;
		RigidBodyGeometry m_RigidBodyGeometry;
		ObjLoader m_ObjLoader;

		FpsTimer m_FpsTimer;
		FTGLPixmapFont* m_Font;
		FTSimpleLayout* m_Layout;
	private:
};

#endif   // OBJTESTSIMULATION_H
