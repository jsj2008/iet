#ifndef  PARTICLESIMULATION_H
#define  PARTICLESIMULATION_H

#include <vector>
#include <list>
#include <sstream>

#include <FTGL/ftgl.h>

#include "SDL/SDL_opengl.h"
#include <boost/shared_ptr.hpp>

#include <dynamx/Particle.hpp>
#include <dynamx/Plane.hpp>
#include <dynamx/ParticleForceRegistry.hpp>
#include <dynamx/ParticleGravityForceGenerator.hpp>
#include <dynamx/ParticleDragForceGenerator.hpp>
#include <dynamx/ParticleAttractionForceGenerator.hpp>

#include <common/Simulation.hpp>
#include <common/Camera.hpp>
#include <common/Math.hpp>
#include <common/Colour.hpp>
#include <common/TextureLoader.hpp>
#include <common/FpsTimer.hpp>

#include <assert.h>

using namespace std;

typedef boost::shared_ptr<dynamx::Plane> PlanePtr;
typedef boost::shared_ptr<dynamx::Particle> ParticlePtr;

const bool CAPFPS = true;
const int FPS = 60;
const int SPAWN_TIME = 10;

class ParticleSimulation : public Simulation
{
	public:
		ParticleSimulation();

		virtual ~ParticleSimulation();

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

		void CollisionDetection();

		void CalculateForces(float timestep);

		void VOnRenderParticles();

		bool m_Finished;

		Colour ChooseColour(ParticlePtr particle);

		void SpawnParticle();

		void RemoveParticle();

		void ToggleGravity();

		void ToggleAttraction();

		/*-----------------------------------------------------------------------------
		 *  Members
		 *-----------------------------------------------------------------------------*/
	
		Camera m_Camera;

//		dynamx::Particle* m_Particles;
		std::list<ParticlePtr> m_Particles;
//		dynamx::Plane m_Plane;
		std::vector<PlanePtr> m_Planes;
		int m_NParticles;

		GLUquadric* m_Quadric;
		GLuint m_NormalSphereList;

		GLuint m_PlaneList;

		float m_PlaneHalfSize;

		Colour* m_Colours;
		int m_NColours;
		Colour m_PlaneColour;

		int m_ParticleTexId;

		dynamx::ParticleForceRegistry m_ParticleForceRegistry;
		dynamx::ParticleGravityForceGenerator* m_GravityForceGen;
		dynamx::ParticleDragForceGenerator* m_DragForceGen;
		dynamx::ParticleAttractionForceGenerator* m_AttractionForceGen;

		FpsTimer m_FpsTimer;
		FpsTimer m_SpawnTimer;

		dynamx::Point3 m_SpawnPos;

		FTGLPixmapFont* m_Font;

		int m_MaxParticles;

		bool m_Gravity;
		bool m_Attraction;
		FTSimpleLayout* m_Layout;
		bool m_IsSpawning;
	private:
};

#endif   // PARTICLESIMULATION_H
