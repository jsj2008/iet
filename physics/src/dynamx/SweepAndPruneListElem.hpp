#ifndef  SWEEPANDPRUNELISTELEM_H
#define  SWEEPANDPRUNELISTELEM_H

#include <dynamx/Core.hpp>

namespace dynamx
{

	class AABBSweepAndPruneElem;

	enum 
	{
		MIN_ELEM = 0,
		MAX_ELEM = 1
	};
	/*
	 * =====================================================================================
	 *        Class: SweepAndPruneListElem
	 *  Description:
	 * =====================================================================================
	 */
	class SweepAndPruneListElem
	{
		public:
			SweepAndPruneListElem(AABBSweepAndPruneElem* parent, int minmax);

			virtual ~SweepAndPruneListElem();

			SweepAndPruneListElem* GetLeft(int i)
			{
				return m_pLeft[i];
			}

			SweepAndPruneListElem* GetRight(int i)
			{
				return m_pRight[i];
			}

			void SetLeft(SweepAndPruneListElem* val, int i)
			{
				m_pLeft[i] = val;
			}

			void SetRight(SweepAndPruneListElem* val, int i)
			{
				m_pRight[i] = val;
			}

			real GetValue(int i)
			{
				return m_Value[i];
			}

			void SetValue(real val, int i)
			{
				m_Value[i] = val;
			}

			int GetMinMax()
			{
				return m_MinOrMax;
			}

			void SetMinMax(int val)
			{
				m_MinOrMax = val;
			}
			
			AABBSweepAndPruneElem* GetParent()
			{
			    return m_Parent;
			}

		protected:
			SweepAndPruneListElem* m_pLeft[3]; //1 for each of 3 axes
			SweepAndPruneListElem* m_pRight[3]; //1 for each of 3 axes
			real m_Value[3]; //1 for each of 3 axes
			int m_MinOrMax;
			AABBSweepAndPruneElem* m_Parent;

		private:
	};

}

#endif   // SWEEPANDPRUNELISTELEM_H
