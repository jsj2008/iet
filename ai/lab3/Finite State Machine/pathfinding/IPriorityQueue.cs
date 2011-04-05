using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine.pathfinding
{
    /**
     * Ordered low to high priority queue ADT.
     */
    public interface IPriorityQueue
    {
        void Add(IPfNode node, float priority);

        bool IsMember(IPfNode node);

        void Remove(IPfNode node);

        IPfNode PopLowest();

        IPfNode PeekLowest();

        //Used for rendering
        IPfNode[] AsArray();
    }
}
