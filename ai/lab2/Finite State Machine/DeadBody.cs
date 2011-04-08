using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine
{
    class DeadBody
    {
        protected Location location;
        public Location Location
        {
            get { return location; }
            set { location = value; }
        }

        public DeadBody(Location location)
        {
            this.location = location;
        }
    }
}
