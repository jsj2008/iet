#ifndef  COLLISIONPAIR_H
#define  COLLISIONPAIR_H

#include <dynamx/AABBSweepAndPruneElem.hpp>

namespace dynamx
{

	/*
	 * =====================================================================================
	 *        Class: CollisionPair
	 *  Description:
	 * =====================================================================================
	 */
	class CollisionPair
	{
		public:
			CollisionPair(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b)
			{
			    m_A = a;
			    m_B = b;
			}

			virtual ~CollisionPair()
			{
			}

			AABBSweepAndPruneElem* GetA()
			{
				return m_A;
			}

			AABBSweepAndPruneElem* GetB()
			{
				return m_B;
			}
			
		protected:
			AABBSweepAndPruneElem* m_A;
			AABBSweepAndPruneElem* m_B;

		private:
	};
}

#endif   // COLLISIONPAIR_H
