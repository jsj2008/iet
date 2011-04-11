#include "SweepAndPruneListElem.hpp"

namespace dynamx
{
    SweepAndPruneListElem::SweepAndPruneListElem(AABBSweepAndPruneElem* parent, int minmax)
		:
			m_Parent(parent)
    {
        m_MinOrMax = minmax;
    }

    SweepAndPruneListElem::~SweepAndPruneListElem()
    {
    }
}
