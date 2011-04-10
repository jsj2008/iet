using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine.map;

namespace FiniteStateMachine.model
{
    class GameModel
    {
        List<Square> m_Squares;

        public List<Square> Squares
        {
            get { return m_Squares; }
            set { m_Squares = value; }
        }

        public GameModel()
        {
        }


    }
}
