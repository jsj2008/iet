using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace FiniteStateMachine.pathfinding
{
    class PfNode : IPfNode
    {
        protected List<IPfNode> m_Neighbours;
        protected IPfNode m_Parent;
        protected float m_G; //Distance travelled so far.
        protected Vector2 m_Pos;
        protected float m_Cost;

        public PfNode(Vector2 pos, float cost)
        {
            m_Pos = pos;
            m_Cost = cost;
            m_G = -1.0f; //Should never be seen
            m_Parent = null;
            m_Neighbours = new List<IPfNode>();
        }

        public IPfNode[] GetNeighbours()
        {
            return m_Neighbours.ToArray();
        }

        public float G
        {
            get { return m_G; }
            set { m_G = value; }
        }

        public IPfNode Parent
        {
            get { return m_Parent; }
            set { m_Parent = value; }
        }

        public float GetCost()
        {
            return m_Cost;
        }

        public Vector2 Pos
        {
            get { return m_Pos; }
        }

        public void AddNeighbour(IPfNode node)
        {
            m_Neighbours.Add(node);
        }
    }
}
