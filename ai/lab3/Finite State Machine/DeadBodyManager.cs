using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    class DeadBodyManager
    {
        protected List<DeadBody> deadBodies;
        protected static DeadBodyManager instance = new DeadBodyManager();

        public DeadBodyManager()
        {
            deadBodies = new List<DeadBody>();
        }

        public static DeadBodyManager GetInstance()
        {
            return instance;
        }

        public int AddBody(DeadBody body)
        {
            deadBodies.Add(body);
            return deadBodies.IndexOf(body);
        }

        public DeadBody GetBody(int id)
        {
            return deadBodies[id];
        }

        public DeadBody GetFirst()
        {
            return deadBodies[0];
        }

        public DeadBody PopFirst()
        {
            DeadBody body = deadBodies[0];
            deadBodies.RemoveAt(0);
            return body;
        }
    }
}
