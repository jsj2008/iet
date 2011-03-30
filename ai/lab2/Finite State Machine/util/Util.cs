using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine.util
{
    class Util
    {
        public static Random m_Random = new Random();

        public static T RandomEnum<T>()
        {
            T[] values = (T[])Enum.GetValues(typeof(T));
            return values[m_Random.Next(0, values.Length)];
        }

    }
}
