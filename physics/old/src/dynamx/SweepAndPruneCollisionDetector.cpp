#include "SweepAndPruneCollisionDetector.hpp"

#include <float.h>

namespace dynamx
{
	SweepAndPruneCollisionDetector::SweepAndPruneCollisionDetector()
	{
		InitLists();
	}

	SweepAndPruneCollisionDetector::~SweepAndPruneCollisionDetector()
	{
		//TODO:deletion of list
	}

	void SweepAndPruneCollisionDetector::InitLists()
	{
		AABBSweepAndPruneElem *pSentinel = new AABBSweepAndPruneElem();
		for (int i = 0; i < 3; i++) 
		{
			pSentinel->GetMin()->SetLeft(NULL, i);
			pSentinel->GetMin()->SetRight(pSentinel->GetMax(), i);
			pSentinel->GetMax()->SetLeft(pSentinel->GetMin(), i);
			pSentinel->GetMax()->SetRight(NULL, i);
			pSentinel->GetMin()->SetValue(-FLT_MAX, i);
			pSentinel->GetMax()->SetValue(FLT_MAX, i);
			m_ListHead[i] = pSentinel->GetMin();
		}
		pSentinel->GetMin()->SetMinMax(MAX_ELEM);
		pSentinel->GetMax()->SetMinMax(MIN_ELEM);
	}
	
    bool SweepAndPruneCollisionDetector::AddCollisionPair(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b)
    {
        a->GetAABB()->SetColliding(true);
        b->GetAABB()->SetColliding(true);
		m_CollisionPairs.push_back(CollisionPair(a,b));
    }
    
    bool SweepAndPruneCollisionDetector::HasCollisionPair(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b)
    {
        //Should do test of all collision pairs for this...
        return false;
    }

	void SweepAndPruneCollisionDetector::InsertAABBIntoList(AABBSweepAndPruneElem* pAABBElem)
	{
		for(int i = 0; i < 3 ; i++)
		{
			SweepAndPruneListElem* pElem = m_ListHead[i];

			//Keep going until we find a value greater than ours
			while( pElem->GetValue(i) < pAABBElem->GetMin()->GetValue(i) )
			{
				pElem = pElem->GetRight(i);
			}
			//We have found an elem which is bigger than our min, so we want to insert here (to left of bigger elem).
			pAABBElem->GetMin()->SetLeft(pElem->GetLeft(i), i);
			pAABBElem->GetMin()->SetRight(pElem, i);
			//Now we update the elems that were in the list before
			pElem->GetLeft(i)->SetRight( pAABBElem->GetMin(), i );
			pElem->SetLeft( pAABBElem->GetMin(), i );

			//Now do the same with the max cell
			//We don't have to start at beginning, yay!
			while(pElem->GetValue(i) < pAABBElem->GetMax()->GetValue(i))
			{
				pElem = pElem->GetRight(i);
			}
			pAABBElem->GetMax()->SetLeft(pElem->GetLeft(i), i);
			pAABBElem->GetMax()->SetRight(pElem, i);
			pElem->GetLeft(i)->SetRight(pAABBElem->GetMax(), i);
			pElem->SetLeft(pAABBElem->GetMax(), i);
		}

		SweepAndPruneListElem* pElem = m_ListHead[0];

        pElem = pElem->GetRight(0);
        
		/*
        std::cout<<"hi";
		while(pElem->GetValue(0) < pAABBElem->GetMax()->GetValue(0))
		{
		    assert(0);
			if( TestAABBCollision(pAABBElem, GetAABBSweepAndPruneElem(pElem)))
			{
				//Here we should just colour both elements.
				AddCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(pElem));
			}
			pElem = pElem->GetRight(0);
		}
		*/
		//Now scan through the list and add overlap pairs for all objects that this AABB intersects
		//Enough to do for one axis as all axes need to be overlapping
		for( SweepAndPruneListElem* pElem = m_ListHead[0] ; ;)
		{
			if( pElem->GetMinMax() == MIN_ELEM )
			{
				if( pElem->GetValue(0) > pAABBElem->GetMax()->GetValue(0))
				{
					break;
				}
				if( TestAABBCollision(pAABBElem, GetAABBSweepAndPruneElem(pElem)))
				{
					//Here we should just colour both elements.
					AddCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(pElem));
				}
			}
			else if(pElem->GetValue(0) < pAABBElem->GetMin()->GetValue(0))
			{
				break;
			}
		}
	}

	void SweepAndPruneCollisionDetector::UpdateAABBPosition(AABBSweepAndPruneElem* pAABBElem)
	{
		for( int i = 0 ; i < 3 ; i++)
		{
			SweepAndPruneListElem* pMin = pAABBElem->GetMin();
			SweepAndPruneListElem* pMax = pAABBElem->GetMax();
			SweepAndPruneListElem* t;

			//Move min elem to the left
			//Also check for AABBs that we pass over.
			for( t = pMin->GetLeft(i) ; pMin->GetValue(i) < t->GetValue(i) ; t = t->GetLeft(i) )
			{
				/*
				if(t->GetMinMax() == MAX_ELEM)
				{
					if(TestAABBCollision(pAABBElem, GetAABBSweepAndPruneElem(t)))
					{
						if(!HasCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t)))
						{
							AddCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t));
						}
					}
				}	
				*/
			}

			//If t has moved, our minimum should move too.
			if(t != pMin->GetLeft(i))
			{
				MoveElement(i, pMin, t);
			}

			//Now try to move max element to the right
			for( t = pMax->GetRight(i) ; pMax->GetValue(i) > t->GetValue(i) ; t = t->GetRight(i) )
			{
				/*
				if(t->GetMinMax() == MIN_ELEM)
				{
					if(TestAABBCollision(pAABBElem, GetAABBSweepAndPruneElem(t)))
					{
						if( ! HasCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t)))
						{
							AddCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t));
						}
					}
				}
				*/
			}
			if(t != pMax->GetRight(i))
			{
				MoveElement(i, pMax, t->GetLeft(i));
			}

			//Now try to move min elem to the right.
			for( t = pMin->GetRight(i) ; pMin->GetValue(i) > t->GetValue(i) ; t = t->GetRight(i))
			{
				/*
				if(t->GetMinMax() == MAX_ELEM)
				{
					if(TestAABBCollision(pAABBElem, GetAABBSweepAndPruneElem(t)))
					{
						if( ! HasCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t)))
						{
							AddCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t));
						}
					}
				}
				*/
			}
			if(t != pMin->GetRight(i))
			{
				MoveElement(i, pMin, t->GetLeft(i));
			}

			//Now try and move max element to the left
			for( t = pMax->GetLeft(i) ; pMax->GetValue(i) < t->GetValue(i) ; t = t->GetLeft(i) )
			{
				/*
				if(t->GetMinMax() == MIN_ELEM)
				{
					if(TestAABBCollision(pAABBElem, GetAABBSweepAndPruneElem(t)))
					{
						if( ! HasCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t)))
						{
							AddCollisionPair(pAABBElem, GetAABBSweepAndPruneElem(t));
						}
					}
				}	
				*/
			}
			if(t != pMax->GetLeft(i))
			{
				MoveElement(i, pMax, t);
			}
		}	
	}

	void SweepAndPruneCollisionDetector::MoveElement(int i, SweepAndPruneListElem* pSrc, SweepAndPruneListElem* pDest)
	{
		// Unlink elem from old location
		pSrc->GetLeft(i)->SetRight( pSrc->GetRight(i), i);
		pSrc->GetRight(i)->SetLeft( pSrc->GetLeft(i), i);
		//And relink after the destination linked list element.
		pSrc->SetLeft( pDest, i );
		pSrc->SetRight( pDest->GetRight(i), i);
		pDest->GetRight(i)->SetLeft( pSrc, i);
		pDest->SetRight(pSrc, i);
	}


	bool SweepAndPruneCollisionDetector::TestAABBCollision(shared_ptr<AABB> a, shared_ptr<AABB> b)
	{
		if (real_abs(a->GetPos().GetX() - b->GetPos().GetX()) > (a->GetExtents().GetX() + b->GetExtents().GetX()))
		{
			return false;
		}
		if (real_abs(a->GetPos().GetY() - b->GetPos().GetY()) > (a->GetExtents().GetY() + b->GetExtents().GetY()))
		{
			return false;
		}
		if (real_abs(a->GetPos().GetZ() - b->GetPos().GetZ()) > (a->GetExtents().GetZ() + b->GetExtents().GetZ()))
		{
			return false;
		}
		return true;
	}

	bool SweepAndPruneCollisionDetector::TestAABBCollision(AABBSweepAndPruneElem* a, AABBSweepAndPruneElem* b)
	{
		return TestAABBCollision(a->GetAABB(), b->GetAABB());
	}

	//Simple collision detection
	void SweepAndPruneCollisionDetector::CheckForCollisionsSimple()
	{
		/*
		vector<shared_ptr<AABB> >::iterator it, itEnd;

		//Set All not colliding first
		for(it = m_AABBs.begin(), itEnd = m_AABBs.end() ; it != itEnd ; it++)
		{
			(*it)->SetColliding(false);
		}

		for(it = m_AABBs.begin(), itEnd = m_AABBs.end() ; it != itEnd ; it++)
		{
			vector<shared_ptr<AABB> >::iterator it2 = it+1;
			for( ; it2 != itEnd ; it2++ )
			{
				if(TestAABBCollision((*it), (*it2)))
				{
					(*it)->SetColliding(true);
					(*it2)->SetColliding(true);
				}
			}
		}
		*/
	}

	void SweepAndPruneCollisionDetector::PerformTraversal()
	{
		list<SweepAndPruneListElem*> activeLists[3];
		list<CollisionPair> possiblyColliding[3];

		//1st get possibly colliding list
		for(int i = 0 ; i < 3 ; i++)
		{
			SweepAndPruneListElem* pElem = m_ListHead[i];

			while( pElem->GetValue(i) < FLT_MAX )
			{
				if(pElem->GetMinMax() == MIN_ELEM)
				{
					//Go thro' active list and add a potential collider for all in there.
					list<SweepAndPruneListElem*>::iterator it, itEnd;
					for(it = activeLists[i].begin(), itEnd = activeLists[i].end() ; 
							it!=itEnd ; it++)
					{
						//Generate possible Colliding for these
						possiblyColliding[i].push_back(CollisionPair((*it)->GetParent(), pElem->GetParent()));
					}

					activeLists[i].push_back(pElem);
				}
				else
				{
					activeLists[i].remove(pElem);
				}
				pElem = pElem->GetRight(i);
			}
		}
		//Now have to check for overlapping possiblyColliding
		list<CollisionPair>::iterator it, itEnd;
		for(it = possiblyColliding[0].begin(), itEnd = possiblyColliding[0].end();
				it != itEnd ;
				it++)
		{
			list<CollisionPair>::iterator it2, it2End;
			for(it2 = possiblyColliding[1].begin(), it2End = possiblyColliding[1].end();
					it2 != it2End ;
					it2++)
			{
				//Early out, if not in x AND y, then no point in checking z
				if( ( ((*it).GetA() == (*it2).GetA()) && ((*it).GetB() == (*it2).GetB()) ) ||
						( ((*it).GetB() == (*it2).GetA()) && ((*it).GetA() == (*it2).GetB()) ) )
				{
					list<CollisionPair>::iterator it3, it3End;
					for(it3 = possiblyColliding[2].begin(), it3End = possiblyColliding[2].end();
							it3 != it3End ;
							it3++)
					{
						//Early out, check if in x AND y AND z
						if( ( ((*it2).GetA() == (*it3).GetA()) && ((*it2).GetB() == (*it3).GetB()) ) ||
								( ((*it2).GetB() == (*it3).GetA()) && ((*it2).GetA() == (*it3).GetB()) ) )
						{
							if(TestAABBCollision((*it).GetA(), (*it).GetB()))
							{
								if( ! HasCollisionPair((*it).GetA(), (*it).GetB()))
								{
									AddCollisionPair((*it).GetA(), (*it).GetB());
								}
							}
						}
					}
				}
			}
		}
	}
	
	void SweepAndPruneCollisionDetector::CheckForCollisions()
	{
		//CheckForCollisionsSimple();
		vector<AABBSweepAndPruneElem* >::iterator it, itEnd;
		for( it = m_AABBs.begin(), itEnd = m_AABBs.end() ; it != itEnd ; it++ )
		{
			(*it)->GetAABB()->SetColliding(false);
		    (*it)->UpdateMinMax();
		}
		for( it = m_AABBs.begin(), itEnd = m_AABBs.end() ; it != itEnd ; it++ )
		{
			UpdateAABBPosition( (*it) );
		}
		PerformTraversal();
	}

	/*
	void SweepAndPruneCollisionDetector::InsertAABBIntoList(AABB* obj)
	{
		// For all three axes
		for (int i = 0; i < 3; i++) {
			// Search from start of list
			Elem *pElem = gListHead[i];
			// Insert min cell at position where pElem points to first larger element.
			// Assumes large sentinel value guards from falling off end of list
			while (pElem->value[i] < pAABB->min.value[i])
				pElem = pElem->pRight[i];
			pAABB->min.pLeft[i] = pElem->pLeft[i];
			pAABB->min.pRight[i] = pElem;
			pElem->pLeft[i]->pRight[i] = &pAABB->min;
			pElem->pLeft[i] = &pAABB->min;
			// Insert max cell in the same way. Can continue searching from last
			// position as list is sorted. Also assumes sentinel value present
			while (pElem->value[i] < pAABB->max.value[i])
				pElem = pElem->pRight[i];
			pAABB->max.pLeft[i] = pElem->pLeft[i];
			pAABB->max.pRight[i] = pElem;
			pElem->pLeft[i]->pRight[i] = &pAABB->max;
			pElem->pLeft[i] = &pAABB->max;
		}
		// Now scan through list and add overlap pairs for all objects that
		// this AABB intersects. This pair tracking could be incorporated into
		// the loops above, but is not done here to simplify the code
		for (Elem *pElem = gListHead[0]; ; ) {
			if (pElem->minmax == MIN_ELEM) {
				if (pElem->value[0] > pAABB->max.value[0])
					break;
				if (AABBOverlap(pAABB, GetAABB(pElem)))
					AddCollisionPair(pAABB, GetAABB(pElem));
			} else if (pElem->value[0] < pAABB->min.value[0])
				break;
		}
	}

	// This updating code assumes all other elements of list are sorted
	void UpdateAABBPosition(AABB *pAABB)
	{
		// For all three axes
		for (int i = 0; i < 3; i++) {
			Elem *pMin = &pAABB->min, *pMax = &pAABB->max, *t;
			// Try to move min element to the left. Move the roaming pointer t left
			// for as long as it points to elem with value larger than pMin’s. While
			// doing so, keep track of the update status of any AABBs passed over
			for (t = pMin->pLeft[i]; pMin->value[i] < t->value[i]; t = t->pLeft[i])
				if (t->minmax == MAX_ELEM)
					if (AABBOverlap(pAABB, GetAABB(t)))
						if (!HasCollisionPair(pAABB, GetAABB(t)))
							AddCollisionPair(pAABB, GetAABB(t));
			// If t moves from its original position, move pMin into new place
			if (t != pMin->pLeft[i])
				MoveElement(i, pMin, t);


	}
	*/
}
