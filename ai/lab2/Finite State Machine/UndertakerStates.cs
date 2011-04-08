using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{

    class Hover : State<Undertaker>
    {
        public override void Enter(Undertaker agent)
        {
            Printer.Print(agent.Id, "Hovering in the undertakers office");
            agent.Location = Location.undertakers;
        }

        public override void Execute(Undertaker agent)
        {
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
        public override void Enter(Undertaker agent)
        {
            Printer.Print(agent.Id, "Searching for the body");
            agent.Location = Location.undertakers;
        }

        public override void Execute(Undertaker agent)
        {
            agent.CurrentBody = DeadBodyManager.GetInstance().GetFirst();

            //Go to location in one step, maybe make this longer?
            agent.Location = agent.CurrentBody.Location;
            Printer.Print(agent.Id, "Found body at location :" + agent.Location);

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
        public override void Enter(Undertaker agent)
        {
            Printer.Print(agent.Id, "Dragging body to cemetary");
        }

        public override void Execute(Undertaker agent)
        {
            agent.CurrentBody = DeadBodyManager.GetInstance().GetFirst();

            //Go to location in one step, maybe make this longer?
            agent.Location = Location.cemetary;
            agent.CurrentBody.Location = Location.cemetary;
            Printer.Print(agent.Id, "Finished dragging body to cemetary");

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
