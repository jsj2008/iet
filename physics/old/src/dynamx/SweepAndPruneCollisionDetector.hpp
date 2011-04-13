#ifndef  SWEEPANDPRUNECOLLISIONDETECTOR_H
#define  SWEEPANDPRUNECOLLISIONDETECTOR_H

#include <iostream>
#include <vector>
#include <list>

#include <boost/shared_ptr.hpp>

#include <dynamx/AABB.hpp>
#include <dynamx/AABBSweepAndPruneElem.hpp>
#include <dynamx/CollisionPair.hpp>
#include <dynamx/SweepAndPruneListElem.hpp>

using namespace std;
using namespace boost;

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: SweepAndPruneCollisionDetector
	 *  Description:
	 * =====================================================================================
	 */
	class SweepAndPruneCollisionDetector
	{
		public:
			SweepAndPruneCollisionDetector();

			virtual ~SweepAndPruneCollisionDetector();

			void InitLists();

			bool TestAABBCollision(shared_ptr<AABB> a, shared_ptr<AABB> b);

			bool TestAABBCollision(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b);
			
            bool AddCollisionPair(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b);
            
            bool HasCollisionPair(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b);

            void UpdateAABBPosition(AABBSweepAndPruneElem* pAABBElem);
            
			void InsertAABBIntoList(AABBSweepAndPruneElem* pAABBElem);
			
			void MoveElement(int i, SweepAndPruneListElem* pSrc, SweepAndPruneListElem* pDest);
			 
			void CheckForCollisionsSimple();

			void CheckForCollisions();
			
            void PerformTraversal();

			/*
			void AddAABB(shared_ptr<AABB> val)
			{
				m_AABBs.push_back(val);
			}
			*/

			void AddAABB(shared_ptr<AABB> val)
			{
				AABBSweepAndPruneElem* elem = new AABBSweepAndPruneElem(val);
				InsertAABBIntoList(elem);

				m_AABBs.push_back(elem); //So I can update on every loop.
			}

			/*
			AABBSweepAndPruneElem* GetAABBSweepAndPruneElem(SweepAndPruneListElem* pElem)
			{
				return (AABBSweepAndPruneElem *)(pElem->GetMinMax() ? (pElem - 1) : pElem);
			}
			*/

			AABBSweepAndPruneElem* GetAABBSweepAndPruneElem(SweepAndPruneListElem* pElem)
			{
				return pElem->GetParent();
			}

		protected:
			vector<AABBSweepAndPruneElem* > m_AABBs;

			//AABBSweepAndPruneElem* m_AABBListHead;
			SweepAndPruneListElem* m_ListHead[3];
			vector<CollisionPair> m_CollisionPairs;

		private:
	};
}
#endif   // SWEEPANDPRUNECOLLISIONDETECTOR_H
