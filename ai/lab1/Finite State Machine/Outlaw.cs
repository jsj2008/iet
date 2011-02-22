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

        //Location of the outlaw
        private Location location;
        public Location OutlawLocation
        {
            get { return location; }
            set { location = value; }
        }

        private int goldCarrying;
        public int GoldCarrying
        {
            get { return goldCarrying; }
            set { goldCarrying = value; }
        }

        public Outlaw() : base()
        {
            stateMachine = new StateMachine<Outlaw>(this);
            stateMachine.CurrentState = new Lurk();
            stateMachine.GlobalState = new OutlawGlobalState();
            goldCarrying = 0;
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
