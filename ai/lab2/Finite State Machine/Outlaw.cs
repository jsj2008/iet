using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    public class Outlaw : Agent
    {
        //Outlaw's state machine
        private StateMachine<Outlaw> stateMachine;
        public StateMachine<Outlaw> StateMachine
        {
            get { return stateMachine; }
            set { stateMachine = value; }
        }

        private int goldCarrying;
        public int GoldCarrying
        {
            get { return goldCarrying; }
            set { goldCarrying = value; }
        }

        protected bool dead;
        public bool Dead
        {
            get { return dead; }
            set { dead = value; }
        }

        public Outlaw() : base()
        {
            stateMachine = new StateMachine<Outlaw>(this);
            stateMachine.CurrentState = new Lurk();
            stateMachine.GlobalState = new OutlawGlobalState();
            goldCarrying = 0;
            agentType = AgentType.outlaw;
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
