#ifndef  RIGIDBODYMOTIONSIMULATION_H
#define  RIGIDBODYMOTIONSIMULATION_H

#include <vector>
#include <list>
#include <sstream>

#include <FTGL/ftgl.h>

#include "SDL/SDL_opengl.h"
#include <boost/shared_ptr.hpp>

#include <dynamx/Point3.hpp>
#include <dynamx/RigidBody.hpp>
#include <dynamx/SweepAndPruneCollisionDetector.hpp>

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

typedef boost::shared_ptr<dynamx::RigidBody> RigidBodyPtr;

const bool CAPFPS = true;
const int FPS = 60;

class RigidBodyMotionSimulation : public Simulation
{
	public:
		RigidBodyMotionSimulation();

		virtual ~RigidBodyMotionSimulation();

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
		std::list<RigidBodyPtr> m_RigidBodies;
		SweepAndPruneCollisionDetector* m_CollisionDetector;

		FpsTimer m_FpsTimer;
		FTGLPixmapFont* m_Font;
		FTSimpleLayout* m_Layout;
	private:
};

#endif   // RIGIDBODYMOTIONSIMULATION_H
