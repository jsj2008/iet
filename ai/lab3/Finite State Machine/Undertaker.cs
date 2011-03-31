using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    class Undertaker : Agent
    {
        private StateMachine<Undertaker> stateMachine;
        public StateMachine<Undertaker> StateMachine
        {
            get { return stateMachine; }
            set { stateMachine = value; }
        }

        private DeadBody currentBody;
        public DeadBody CurrentBody
        {
            get { return currentBody; }
            set { currentBody = value; }
        }

        public Undertaker() : base()
        {
            stateMachine = new StateMachine<Undertaker>(this);
            stateMachine.CurrentState = new Hover();
            stateMachine.GlobalState = new UndertakerGlobalState();
            location = Location.undertakers;
            agentType = AgentType.undertaker;
        }

        public override void Update()
        {
            stateMachine.Update();
        }

        public override bool HandleMessage(Telegram telegram)
        {
            return stateMachine.HandleMessage(telegram);
        }
    }
}
