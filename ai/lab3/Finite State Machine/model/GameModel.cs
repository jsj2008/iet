using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using FiniteStateMachine.map;
using FiniteStateMachine.pathfinding;

namespace FiniteStateMachine.model
{
    class GameModel
    {
        List<Square> m_Squares;
        IPriorityQueue[] m_Sequences;

        public List<Square> Squares
        {
            get { return m_Squares; }
            set { m_Squares = value; }
        }

        public IPriorityQueue[] Sequences
        {
            get { return m_Sequences; }
            set { m_Sequences = value; }
        }

        public void SetSquaresFromSequences()
        {
            foreach (Square square in m_Squares)
            {
                square.Route = false;
            }

            foreach(IPriorityQueue queue in m_Sequences)
            {
                IPfNode[] nodes = queue.AsArray();

                foreach(IPfNode node in nodes)
                {
                    //This is O(n) to find the squareId, not too bad..
                    int squareId = (int)PfNodeManager.GetInstance().FindKey(node);
                    Square square = SquareManager.GetInstance().GetSquare(squareId);
                    square.Route = true;
                }
                /*
                IPfNode node = queue.PeekLowest();
                while (node != null)
                {
                    //This is O(n) to find the squareId, not too bad..
                    int squareId = (int)PfNodeManager.GetInstance().FindKey(node);
                    Square square = SquareManager.GetInstance().GetSquare(squareId);
                    square.Route = true;
                    node = queue.PopLowest();
                }
                */
            }

        }

        public GameModel()
        {
        }


    }
}
