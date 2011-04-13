using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine.map;

namespace FiniteStateMachine
{
    class Hover : State<Undertaker>
    {
        public Hover()
        {
            stateLocation = Location.undertakers;
        }

        public override void Enter(Undertaker agent)
        {
            Printer.Print(agent.Id, "Hovering in the undertakers office");
            agent.Location = stateLocation;
        }

        public override void Execute(Undertaker agent)
        {
            agent.Pos = SquareManager.GetInstance().GetLocationSquare(agent.Location).Pos;
        }

        public override void Exit(Undertaker agent)
        {
        }

        public override bool OnMesssage(Undertaker agent, Telegram telegram)
        {
            switch (telegram.messageType)
            {
                case MessageType.Gunfight:
                    Printer.Print(agent.Id, "Oh goodie, another dead body. I will go and search for it now. Ah love ma job!");
                    agent.StateMachine.ChangeState(new SearchForBody());
                    return true;
                default:
                    return false;
            }           
        }
    }

    class SearchForBody : State<Undertaker>
    {
        public SearchForBody()
        {
            stateLocation = Location.undertakers;
        }

        public override void Enter(Undertaker agent)
        {
            Printer.Print(agent.Id, "Searching for the body");
            agent.Location = stateLocation;
        }

        public override void Execute(Undertaker agent)
        {
            agent.CurrentBody = DeadBodyManager.GetInstance().PopFirst();

            agent.StateMachine.ChangeState(new SearchForBodyLoop(agent.CurrentBody.Location));
        }

        public override void Exit(Undertaker agent)
        {
        }

        public override bool OnMesssage(Undertaker agent, Telegram telegram)
        {
            return false;
        }
    }

    class SearchForBodyLoop : State<Undertaker>
    {
        public SearchForBodyLoop(Location location)
        {
            stateLocation = location;
        }

        public override void Enter(Undertaker agent)
        {
            agent.Location = stateLocation;
            Printer.Print(agent.Id, "Found body at location :" + agent.Location);

        }

        public override void Execute(Undertaker agent)
        {
            //Now go to drag state.
            agent.StateMachine.ChangeState(new DragBody());
        }

        public override void Exit(Undertaker agent)
        {
        }

        public override bool OnMesssage(Undertaker agent, Telegram telegram)
        {
            return false;
        }
    }

    class DragBody : State<Undertaker>
    {
        public DragBody()
        {
            stateLocation = Location.cemetary;
        }

        public override void Enter(Undertaker agent)
        {
            Printer.Print(agent.Id, "Dragged body to cemetary");
            agent.Location = Location.cemetary;
        }

        public override void Execute(Undertaker agent)
        {
            //Go to location in one step, maybe make this longer?
            agent.CurrentBody.Location = Location.cemetary;

            //Now go to hover state again.
            agent.StateMachine.ChangeState(new Hover());
        }

        public override void Exit(Undertaker agent)
        {
        }

        public override bool OnMesssage(Undertaker agent, Telegram telegram)
        {
            return false;
        }
    }

    class UndertakerGlobalState : State<Undertaker>
    {
        public override void Enter(Undertaker agent)
        {
        }

        public override void Execute(Undertaker agent)
        {
        }

        public override void Exit(Undertaker agent)
        {
        }

        public override bool OnMesssage(Undertaker agent, Telegram telegram)
        {
            return false;
        }
    }
}
