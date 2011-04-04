using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine.core;

namespace FiniteStateMachine.pathfinding
{
    class PfNodeManager
    {
        protected Dictionary<int, IPfNode> m_SquareToPfNode;
        private static PfNodeManager m_Instance = new PfNodeManager();
        protected IPfNode[,] m_PfNodeGrid;

        private PfNodeManager()
        {
            m_SquareToPfNode = new Dictionary<int, IPfNode>();
            m_PfNodeGrid = new IPfNode[Constants.SCREEN_HEIGHT / Constants.SQUARE_SIDE,
                Constants.SCREEN_WIDTH / Constants.SQUARE_SIDE];
        }

        public static PfNodeManager GetInstance()
        {
            return m_Instance;
        }

        public void Add(int id, int i, int j, IPfNode node)
        {
            m_SquareToPfNode[id] = node;
            m_PfNodeGrid[i, j] = node;
        }


        public IPfNode Get(int id)
        {
            return m_SquareToPfNode[id];
        }
    }
}
