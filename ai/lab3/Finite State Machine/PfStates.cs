using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine.map;
using FiniteStateMachine.pathfinding;
using Microsoft.Xna.Framework;

namespace FiniteStateMachine
{
    class PfState<T> : State<T> where T : Agent
    {
        State<T> m_DependantState;
        IPfNode m_StartNode, m_TargetNode;
        IPriorityQueue m_Path;

        public PfState(State<T> dependantState,
            Location startLocation,
            Location endLocation)
        {
            m_DependantState = dependantState;
            m_StartNode = PfNodeManager.GetInstance().Get(SquareManager.GetInstance().GetLocationSquare(startLocation).Id);
            m_TargetNode = PfNodeManager.GetInstance().Get(SquareManager.GetInstance().GetLocationSquare(endLocation).Id);

            Printer.Print(0, "Pathfinding constructor : Pathfinding towards " + endLocation + " from " + startLocation);
        }

        public override void Enter(T agent)
        {   
            //Set agent to being at the start location
            agent.Pos = m_StartNode.Pos;
            //Create Path
            AStarPathFinder pathFinder = new AStarPathFinder();
            m_Path = pathFinder.PathFind(m_StartNode, m_TargetNode);
        }

        public override void Execute(T agent)
        {
            //Printer.Print(agent.Id, "in Pathfinding Execute Method");
            //Move along path to next element in the list.
            IPfNode next = m_Path.PeekLowest();

            //if we have arrived, change to the dependant state
            if (next == null)
            {
                return;
                //agent.StateMachine.ChangeState(m_DependantState);
            }
            Printer.Print(agent.Id, "Pathfinder, seeking to Pos : " + next.Pos);
            Printer.Print(agent.Id, "Pathfinder, agent Pos : " + agent.Pos);

            //If we are close enough to the current node, move to the next one.
            if (Vector2.Distance(agent.Pos, next.Pos) < 1.0f)
            {
                m_Path.PopLowest();
                next = m_Path.PeekLowest();
                if (next == null)
                {
                    return;
                    //agent.StateMachine.ChangeState(m_DependantState);
                }
            }

            //Now that we have a target, we seek towards it.
            Vector2 direction = next.Pos - agent.Pos;
            direction.Normalize();
            agent.Pos += direction * agent.Speed;
        }

        public override void Exit(T agent)
        {
            ;
        }

        public override bool OnMesssage(T agent, Telegram telegram)
        {
            return false;
        }
    }
}
