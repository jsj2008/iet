using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    class Sheriff : Agent
    {
        private int goldCarrying;
        public int GoldCarrying
        {
            get { return goldCarrying; }
            set { goldCarrying = value; }
        }

        // Here is the StateMachine that the Miner uses to drive the agent's behaviour
        private StateMachine<Sheriff> stateMachine;
        public StateMachine<Sheriff> StateMachine
        {
            get { return stateMachine; }
            set { stateMachine = value; }
        }
	
        // The constructor invokes the base class constructor, which then creates 
        // an id for the new agent object and then creates and initalises the agent's
        // StateMachine
        public Sheriff() : base()
        {
            stateMachine = new StateMachine<Sheriff>(this);
            stateMachine.CurrentState = new PatrolState();
            stateMachine.GlobalState = new SheriffGlobalState();
            location = Location.sheriffsOffice;
            agentType = AgentType.sheriff;
        }

        // This method is invoked by the Game object as a result of XNA updates 
        public override void Update()
        {
            stateMachine.Update();
        }

        // This method is invoked when the agent receives a message
        public override bool HandleMessage(Telegram telegram)
        {
            return stateMachine.HandleMessage(telegram);    
        }
    }
}
