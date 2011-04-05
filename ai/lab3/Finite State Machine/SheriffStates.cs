using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    class PatrolState : State<Sheriff>
    {
        public PatrolState()
        {
            stateLocation = Location.sheriffsOffice;
        }

        public override void Enter(Sheriff agent)
        {
            Printer.Print(agent.Id, "Starting Patrol...");
        }

        public override void Execute(Sheriff agent)
        {
            //Pick a new location and go to it in a loop.
            Random random = new Random();
            int moveChoice = random.Next(FSMConstants.nLocations);
            int newLocation = (((int)agent.Location) + moveChoice) % FSMConstants.nLocations;
            while ((newLocation == (int)Location.outlawCamp) || (newLocation == (int)agent.Location))
            {
                //Can't go to outlaw camp so keep trying a new location, 
                //and it needs to be different from current location
                moveChoice = random.Next(FSMConstants.nLocations);
                newLocation = (((int)agent.Location) + moveChoice) % FSMConstants.nLocations;
            }
            Printer.Print(agent.Id, "Patrolling location..." + newLocation);
            //agent.Location = (Location)newLocation;
            agent.StateMachine.ChangeState(new PatrolStateLoop((Location)newLocation));
        }

        public override void Exit(Sheriff agent)
        {
            Printer.Print(agent.Id, "Goin' to rop my new found wealth off at the bank!");
        }

        public override bool OnMesssage(Sheriff agent, Telegram telegram)
        {
            return false;
        }
    }

    class PatrolStateLoop : State<Sheriff>
    {
        public PatrolStateLoop(Location location)
        {
            stateLocation = location;
        }

        public override void Enter(Sheriff agent)
        {
            agent.Location = stateLocation;
            //Dispatch a message to all other agents as we enter a new location.
            for (int i = 0; i < AgentManager.GetNAgents(); i++)
            {
                if (i != agent.Id) //Don't check ourselves
                {
                    Agent receiver = AgentManager.GetAgent(i);
                    if (receiver.Location == agent.Location)
                    {
                        if (receiver.AgentType == AgentType.outlaw)
                        {
                            Printer.Print(agent.Id, "Ye be paying for your misdeeds!");
                            Outlaw outlaw = (Outlaw)receiver;
                            int stolenGold = outlaw.GoldCarrying;
                            agent.GoldCarrying += stolenGold;
                            Message.DispatchMessage(0, agent.Id, outlaw.Id, MessageType.ShootAgent);
                            Printer.Print(agent.Id, "Got em! And also got " + stolenGold + " gold");
                            agent.StateMachine.ChangeState(new DropOffMoneyState());

                            DeadBodyManager.GetInstance().AddBody(new DeadBody(outlaw.Location));
                            //Send message to undertaker to clean this mess up.
                            Message.DispatchMessage(0, agent.Id, GetUndertaker().Id, MessageType.Gunfight);
                        }
                        else
                        {
                            Printer.Print(agent.Id, "Why hello there youngun'. fancy meeting you round here.");
                        }
                    }
                }
            }
        }

        public Undertaker GetUndertaker()
        {
            for (int i = 0; i < AgentManager.GetNAgents(); i++)
            {
                Agent agent = AgentManager.GetAgent(i);
                if (agent.AgentType == AgentType.undertaker)
                {
                    return (Undertaker)agent;
                }
            }
            return null;
        }

        public override void Execute(Sheriff agent)
        {
            //Pick a new location and go to it in a loop.
            Random random = new Random();
            int moveChoice = random.Next(FSMConstants.nLocations);
            int newLocation = (((int)agent.Location) + moveChoice) % FSMConstants.nLocations;
            while ((newLocation == (int)Location.outlawCamp) || (newLocation == (int)agent.Location))
            {
                //Can't go to outlaw camp so keep trying a new location, 
                //and it needs to be different from current location
                moveChoice = random.Next(FSMConstants.nLocations);
                newLocation = (((int)agent.Location) + moveChoice) % FSMConstants.nLocations;
            }
            Printer.Print(agent.Id, "Patrolling location..." + newLocation);
            //agent.Location = (Location)newLocation;
            agent.StateMachine.ChangeState(new PatrolStateLoop((Location)newLocation));
        }

        public override void Exit(Sheriff agent)
        {
            Printer.Print(agent.Id, "Goin' to rop my new found wealth off at the bank!");
        }

        public override bool OnMesssage(Sheriff agent, Telegram telegram)
        {
            return false;
        }
    }

    class DropOffMoneyState : State<Sheriff>
    {
        public override void Enter(Sheriff agent)
        {
            Printer.Print(agent.Id, "Dropping off Money to bank...");
        }

        public override void Execute(Sheriff agent)
        {
            agent.Location = Location.bank;
            //Drop off money to bank, so not carrying any anymore.
            agent.GoldCarrying = 0;
            agent.StateMachine.ChangeState(new CelebrateState());
        }

        public override void Exit(Sheriff agent)
        {
            Printer.Print(agent.Id, "Heading to the saloon for some mighty fine whiskey.");
        }

        public override bool OnMesssage(Sheriff agent, Telegram telegram)
        {
            return false;
        }
    }

    class CelebrateState : State<Sheriff>
    {

        public CelebrateState()
        {
            stateLocation = Location.saloon;
        }

        public override void Enter(Sheriff agent)
        {
            agent.Location = stateLocation;
            Printer.Print(agent.Id, "Going to the saloon to celebrate some mighty fine work...");
        }

        public override void Execute(Sheriff agent)
        {
            Printer.Print(agent.Id, "Drinking whiskey at the saloon, oh life is good!");
        }

        public override void Exit(Sheriff agent)
        {
            Printer.Print(agent.Id, "Got to get back to work");
        }

        public override bool OnMesssage(Sheriff agent, Telegram telegram)
        {
            return false;
        }
    }

    class SheriffGlobalState : State<Sheriff>
    {
        public override void Enter(Sheriff agent)
        {
        }

        public override void Execute(Sheriff agent)
        {
        }

        public override void Exit(Sheriff agent)
        {
        }

        public override bool OnMesssage(Sheriff agent, Telegram telegram)
        {
            return false;
        }
    }
}
