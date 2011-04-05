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
        protected List<IPriorityQueue> m_Queues; //Used for storing pathfinding paths which are displayed

        private PfNodeManager()
        {
            m_Queues = new List<IPriorityQueue>();
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

        public void AddSequence(IPriorityQueue queue)
        {
            m_Queues.Add(queue);
        }

        public void RemoveSequence(IPriorityQueue queue)
        {
            m_Queues.Remove(queue);
        }

        public List<IPriorityQueue> GetSequences()
        {
            return m_Queues;
        }

        public int? FindKey(IPfNode value)
        {
            foreach (var pair in m_SquareToPfNode)
            {
                if (pair.Value == value)
                {
                    return pair.Key;
                }
            }
            return null;
        }
    }
}
