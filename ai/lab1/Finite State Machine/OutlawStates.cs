using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    public class Lurk : State<Outlaw>
    {
        public override void Enter(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "Lurking in my outlaw camp, they won't know what hit 'em.");
            outlaw.OutlawLocation = Location.outlawCamp;
        }

        public override void Execute(Outlaw outlaw)
        {
            Random random = new Random();
            int moveChoice = random.Next(2);
            if (moveChoice == 0)
            {
                //Move to new location
                if (outlaw.OutlawLocation == Location.outlawCamp)
                {
                    Printer.Print(outlaw.Id, "Lurking in the cemetary, no one will look for me here.");
                    outlaw.OutlawLocation = Location.cemetary;
                }
                else
                {
                    Printer.Print(outlaw.Id, "Lurking in my outlaw camp, they won't know what hit 'em.");
                    outlaw.OutlawLocation = Location.outlawCamp;
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
        public override void Enter(Outlaw outlaw)
        {
            Printer.Print(outlaw.Id, "About to rob bank for lot's o' gold!");
            outlaw.OutlawLocation = Location.bank;
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
            return false;
        }
    }
}
