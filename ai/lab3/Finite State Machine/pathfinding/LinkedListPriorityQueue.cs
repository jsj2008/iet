using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine.pathfinding
{
    class PqElem
    {
        protected PqElem m_Next;
        //protected PqElem m_Prev;
        protected float m_Priority;
        protected IPfNode m_Data;

        public PqElem(IPfNode node, float priority)
        {
            m_Data = node;
            m_Priority = priority;
            m_Next = null;
        }

        public IPfNode Data
        {
            get { return m_Data; }
            set { m_Data = value; }
        }

        public float Priority
        {
            get { return m_Priority; }
            set { m_Priority = value; }
        }

        public PqElem Next
        {
            get { return m_Next; }
            set { m_Next = value; }
        }
    }

    class LinkedListPriorityQueue : IPriorityQueue
    {
        protected PqElem m_Lowest;

        public LinkedListPriorityQueue()
        {
            //Set up lowest element
            m_Lowest = null;
            /*
            m_Lowest = new PqElem();
            IPfNode node = new GraphPfNode();
            m_Lowest.Data = node;
            m_Lowest.Rank = float.MinValue;
            m_Lowest.Next = null;
             */
        }

        public void Add(IPfNode node, float priority)
        {
            PqElem elem = new PqElem(node, priority);

            //Check for case when it is the first element added.
            if (m_Lowest == null)
            {
                m_Lowest = elem;
                return;
            }

            PqElem searchElem = m_Lowest;
            PqElem prevElem = null;
            //Search for position in linked list to add
            while ((searchElem != null) &&
                (searchElem.Priority < elem.Priority))
            {
                prevElem = searchElem;
                searchElem = searchElem.Next;
            }
            //Found position, now modify next pointers
            if (prevElem == null)
            {
                //Case where we add a new start
                PqElem oldLowest = m_Lowest;
                m_Lowest = elem;
                elem.Next = oldLowest;
            }
            else
            {
                prevElem.Next = elem;
                elem.Next = searchElem;
            }
        }

        public bool IsMember(IPfNode node)
        {
            PqElem searchElem = m_Lowest;
            while (searchElem != null)
            {
                if (searchElem.Data.Equals(node))
                {
                    return true;
                }
                searchElem = searchElem.Next;
            }
            return false;
        }

        public void Remove(IPfNode node)
        {
            PqElem searchElem = m_Lowest;
            PqElem prevElem = null;
            //Search for element in linked list to delete
            while (searchElem != null)
            {
                if (searchElem.Data.Equals(node))
                {
                    //Found node so delete.
                    prevElem.Next = searchElem.Next;
                    searchElem = null;
                    return;
                }
                prevElem = searchElem;
                searchElem = searchElem.Next;
            }
        }

        public IPfNode PopLowest()
        {
            IPfNode lowest = m_Lowest.Data;
            m_Lowest = m_Lowest.Next;
            return lowest;
        }

        public IPfNode PeekLowest()
        {
            if (m_Lowest != null)
            {
                return m_Lowest.Data;
            }
            else
            {
                return null;
            }
        }

    }
}
