using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine.map;

namespace FiniteStateMachine.pathfinding
{
    class PfNodeFactory
    {

        public PfNodeFactory()
        {
        }

        //Creates the nodes to be used for pathfinding and adds them to the
        // singleton PfNodeManager's table.
        public void CreatePfGraphFromWorldGeom(SquareManager squareManager)
        {
            PfNode[,] nodes = new PfNode[squareManager.MaxGridI(), squareManager.MaxGridJ()];
            //1st create the nodes
            for (int i = 0; i < squareManager.MaxGridI(); i++)
            {
                for (int j = 0; j < squareManager.MaxGridJ(); j++)
                {
                    Square square = squareManager.GetSquareFromGrid(i, j);
                    nodes[i,j] = new PfNode(square.Pos, square.GetMovementCost());
                    //Add the node to the manager.
                    PfNodeManager.GetInstance().Add(square.Id, i, j, nodes[i, j]);
                }
            }

            //2nd, populate the neighbours
            for (int i = 0; i < squareManager.MaxGridI(); i++)
            {
                for (int j = 0; j < squareManager.MaxGridJ(); j++)
                {
                    //Add all 4 adjacent nodes (if they all exist)
                    if (i > 0)
                    {
                        nodes[i, j].AddNeighbour(nodes[i - 1, j]);
                    }
                    if (j > 0)
                    {
                        nodes[i, j].AddNeighbour(nodes[i, j-1]);
                    }
                    if (i < (squareManager.MaxGridI() - 1))
                    {
                        nodes[i, j].AddNeighbour(nodes[i+1, j]);
                    }
                    if (j < (squareManager.MaxGridJ() - 1))
                    {
                        nodes[i, j].AddNeighbour(nodes[i, j+1]);
                    }
                }
            }
        }
    }
}
