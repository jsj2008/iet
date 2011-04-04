using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine.pathfinding
{
    public interface IPathFinder
    {
        IPriorityQueue PathFind(IPfNode startNode, IPfNode endNode);
    }
}
