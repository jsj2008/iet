using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace FiniteStateMachine.pathfinding
{
    class AStarPathFinder : IPathFinder
    {

        private float MovementCost(IPfNode a, IPfNode b)
        {
            return a.GetCost() + b.GetCost();
        }

        private float H(IPfNode a, IPfNode b)
        {
            return Vector2.DistanceSquared(a.Pos, b.Pos);
        }

        //Use A-Star algorithm to find the shortest path from the start node 
        // to the end node.
        public IPriorityQueue PathFind(IPfNode startNode, IPfNode endNode)
        {
            IPriorityQueue open = new LinkedListPriorityQueue();
            open.Add(startNode, 0);
            IPriorityQueue closed = new LinkedListPriorityQueue();

            int closedI = 0;

            //Continue until lowest ranked node is the end node.
            while (! open.PeekLowest().Equals(endNode))
            {
                IPfNode current = open.PopLowest();
                closed.Add(current, closedI++); //This is so that the closed queue is ordered correctly
                IPfNode[] neighbours = current.GetNeighbours();
                for (int i = 0; i < neighbours.Length ; i++)
                {
                    IPfNode neighbour = neighbours[i];
                    float cost = current.G + MovementCost(current, neighbour);
                    if (open.IsMember(neighbour) &&
                        cost < neighbour.G )
                    {
                        //New path is better so remove
                        open.Remove(neighbour);
                    }
                    //For inadmissable heuristics which may not get the shortest path.
                    if (closed.IsMember(neighbour) &&
                        cost < neighbour.G)
                    {
                        closed.Remove(neighbour);
                    }
                    //Not in closed set or open set so let's add to open set.
                    //Also calculate distance travelled so far.
                    if ((!open.IsMember(neighbour)) && (!closed.IsMember(neighbour)))
                    {
                        neighbour.G = cost;
                        open.Add(neighbour, neighbour.G + H(neighbour, endNode));
                        neighbour.Parent = current;
                    }
                }
            }
            return closed;
        }
    }
}
