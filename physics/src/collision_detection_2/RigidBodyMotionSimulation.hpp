#ifndef  RIGIDBODYMOTIONSIMULATION_H
#define  RIGIDBODYMOTIONSIMULATION_H

#include <vector>
#include <list>
#include <sstream>

#include "SDL/SDL_opengl.h"
#include <boost/shared_ptr.hpp>

#include <dynamx/Point3.hpp>
#include <dynamx/RigidBody.hpp>
#include <dynamx/Particle.hpp>
//#include <dynamx/SweepAndPruneCollisionDetector.hpp>
#include <dynamx/CollisionDetector.hpp>
#include <dynamx/CollisionPlane.hpp>
#include <dynamx/Contact.hpp>

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
//		SweepAndPruneCollisionDetector* m_CollisionDetector;
		CollisionDetector* m_NarrowPhaseCollisionDetector;
		shared_ptr<CollisionPlane> m_Plane;
		Particle* m_Particle;

		GLUquadric* m_Quadric;

	//	list<ContactPtr> m_Contacts;

		GLuint m_NormalSphereList;

//		bool particleColliding;
		bool isColliding;


//		shared_ptr<dynamx::Contact> m_Contact;
		ContactPtr m_Contact;
		//FpsTimer* m_FpsTimer;
	private:
};

#endif   // RIGIDBODYMOTIONSIMULATION_H
