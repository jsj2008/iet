#ifndef  AABBSWEEPANDPRUNEELEM_H
#define  AABBSWEEPANDPRUNEELEM_H

#include <dynamx/AABB.hpp>
#include <dynamx/SweepAndPruneListElem.hpp>

namespace dynamx
{
	class AABBSweepAndPruneElem
	{
		public:
			AABBSweepAndPruneElem();
			
            AABBSweepAndPruneElem(shared_ptr<AABB> aabb);

			virtual ~AABBSweepAndPruneElem();

			SweepAndPruneListElem* GetMax()
			{
				return m_Max;
			}

			SweepAndPruneListElem* GetMin()
			{
				return m_Min;
			}

			shared_ptr<AABB> GetAABB()
			{
				return m_AABB;
			}

			void UpdateMinMax()
			{
				Vector3 extents = m_AABB->GetExtents();
				real xExtents = extents.GetX();
				real yExtents = extents.GetY();
				real zExtents = extents.GetZ();
				real xPos = m_AABB->GetPos().GetX();
				real yPos = m_AABB->GetPos().GetY();
				real zPos = m_AABB->GetPos().GetZ();
				m_Min->SetValue(xExtents - xPos, 0);
				m_Min->SetValue(yExtents - yPos, 1);
				m_Min->SetValue(zExtents - zPos, 2);

				m_Max->SetValue(xExtents + xPos, 0);
				m_Max->SetValue(yExtents + yPos, 1);
				m_Max->SetValue(zExtents + zPos, 2);
			}

		private:
			SweepAndPruneListElem* m_Min;
			SweepAndPruneListElem* m_Max;
			shared_ptr<AABB> m_AABB;
	};
}
#endif   // AABBSWEEPANDPRUNEELEM_H
