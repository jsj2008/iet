using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    public class Lurk : State<Outlaw>
    {
        public Lurk()
        {
            stateLocation = Location.outlawCamp;
        }

        public override void Enter(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "Lurking in my outlaw camp, they won't know what hit 'em.");
            outlaw.Location = stateLocation;
        }

        public override void Execute(Outlaw outlaw)
        {
            Random random = new Random();
            int moveChoice = random.Next(2);
            if (moveChoice == 0)
            {
                //Move to new location
                if (outlaw.Location == Location.outlawCamp)
                {
                    Printer.Print(outlaw.Id, "Lurking in the cemetary, no one will look for me here.");
                    LurkLoop lurkLoop = new LurkLoop(Location.cemetary);
                    outlaw.StateMachine.ChangeState(lurkLoop);
                }
                else
                {
                    Printer.Print(outlaw.Id, "Lurking in my outlaw camp, they won't know what hit 'em.");
                    LurkLoop lurkLoop = new LurkLoop(Location.outlawCamp);
                    outlaw.StateMachine.ChangeState(lurkLoop);
                }
            }
            int robBankChoice = random.Next(10);
            if (robBankChoice == 0)
            {
                //Rob the bank.
                outlaw.StateMachine.ChangeState(new RobBankForGold());
            }
        }

        public override void Exit(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "Ah, goin' to rob me some sweet, sweet gold!");
        }

        public override bool OnMesssage(Outlaw agent, Telegram telegram)
        {
            return false;
        }
    }

    public class LurkLoop : State<Outlaw>
    {
        public LurkLoop(Location location)
        {
            stateLocation = location;
        }

        public override void Enter(Outlaw outlaw)
        {
        }

        public override void Execute(Outlaw outlaw)
        {
            Random random = new Random();
            int moveChoice = random.Next(2);
            if (moveChoice == 0)
            {
                //Move to new location
                if (outlaw.Location == Location.outlawCamp)
                {
                    Printer.Print(outlaw.Id, "Lurking in the cemetary, no one will look for me here.");
                    LurkLoop lurkLoop = new LurkLoop(Location.cemetary);
                    outlaw.StateMachine.ChangeState(lurkLoop);
                }
                else
                {
                    Printer.Print(outlaw.Id, "Lurking in my outlaw camp, they won't know what hit 'em.");
                    LurkLoop lurkLoop = new LurkLoop(Location.outlawCamp);
                    outlaw.StateMachine.ChangeState(lurkLoop);
                }
            }
            int robBankChoice = random.Next(10);
            if (robBankChoice == 0)
            {
                //Rob the bank.
                outlaw.StateMachine.ChangeState(new RobBankForGold());
            }
        }

        public override void Exit(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "Ah, goin' to rob me some sweet, sweet gold!");
        }

        public override bool OnMesssage(Outlaw agent, Telegram telegram)
        {
            return false;
        }
    }

    public class RobBankForGold : State<Outlaw>
    {
        public RobBankForGold()
        {
            stateLocation = Location.bank;
        }

        public override void Enter(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "About to rob bank for lot's o' gold!");
            outlaw.Location = stateLocation;
        }

        public override void Execute(Outlaw outlaw)
        {
            Random random = new Random();
            int amountOfRobbedGold = random.Next(1, 10);
            outlaw.GoldCarrying += amountOfRobbedGold;
            Printer.Print(outlaw.Id, "Robbed " + amountOfRobbedGold + " gold! Mwhahahahaha! ");
            //Finished Robbing bank so let's go back to lurking...
            outlaw.StateMachine.ChangeState(new Lurk());
        }

        public override void Exit(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "Robbed 'em blind! This will be known as the time they almost caught...");
        }

        public override bool OnMesssage(Outlaw agent, Telegram telegram)
        {
            return false;
        }
    }

    public class Died : State<Outlaw>
    {
        public Died(Location location)
        {
            stateLocation = location;
        }

        public override void Enter(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "I've died!");
        }

        public override void Execute(Outlaw outlaw)
        {
            outlaw.Location = Location.outlawCamp;
            outlaw.StateMachine.ChangeState(new Lurk());
        }

        public override void Exit(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "Yes I've respawned and I'm ah back in business!");
        }

        public override bool OnMesssage(Outlaw agent, Telegram telegram)
        {
            return false;
        }
    }

    public class OutlawGlobalState : State<Outlaw>
    {
        public override void Enter(Outlaw outlaw)
        {
        }

        public override void Execute(Outlaw outlaw)
        {
        }

        public override void Exit(Outlaw outlaw)
        {
        }

        public override bool OnMesssage(Outlaw outlaw, Telegram telegram)
        {
            switch (telegram.messageType)
            {
                case MessageType.ShootAgent:
                    outlaw.Dead = true;
                    Printer.Print(outlaw.Id, "Oh no! I've died and lost all of my money! " + outlaw.GoldCarrying + " gold!");
                    outlaw.GoldCarrying = 0;
                    outlaw.StateMachine.ChangeState(new Died(outlaw.Location));
                    //TODO: Spawn dead body in this location.
                    return true;
                default:
                    return false;
            }
        }
    }
}
