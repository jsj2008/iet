#include "AABBSweepAndPruneElem.hpp"

namespace dynamx
{
    
    AABBSweepAndPruneElem::AABBSweepAndPruneElem()
	{
		m_Min = new SweepAndPruneListElem(this, MIN_ELEM);
		m_Max = new SweepAndPruneListElem(this, MAX_ELEM);
	}
	
	AABBSweepAndPruneElem::AABBSweepAndPruneElem(shared_ptr<AABB> aabb)
	{
		m_Min = new SweepAndPruneListElem(this, MIN_ELEM);
		m_Max = new SweepAndPruneListElem(this, MAX_ELEM);
		m_AABB = aabb;
	}

	AABBSweepAndPruneElem::~AABBSweepAndPruneElem()
	{
		delete m_Min;
		delete m_Max;
	}
}
