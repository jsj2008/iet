using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace FiniteStateMachine.pathfinding
{
    public interface IPfNode
    {
        IPfNode[] GetNeighbours();

        float G
        {
            get;
            set;
        }

        IPfNode Parent
        {
            get;
            set;
        }

        float GetCost();

        Vector2 Pos
        {
            get;
        }

        void AddNeighbour(IPfNode node);
    }
}
