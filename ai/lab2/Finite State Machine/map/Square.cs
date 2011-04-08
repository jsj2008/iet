using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using FiniteStateMachine.core.types;

namespace FiniteStateMachine.map
{
    //A square in the game world.
    class Square
    {
        protected SquareType m_Type;
        protected Vector2 m_Pos;
        protected int m_Id;
        private static int m_SquareCnt = 0; 

        public int Id
        {
            get { return m_Id; }
            set { m_Id = value; }
        }

        public Vector2 Pos
        {
            get { return m_Pos; }
        }

        public SquareType Type
        {
            get { return m_Type; }
        }

        public Square(SquareType type, Vector2 pos)
        {
            m_Id = m_SquareCnt++;
            m_Type = type;
            m_Pos = pos;
        }

        public int GetMovementCost()
        {
            switch (m_Type)
            {
                case (SquareType.Mountain):
                    return 2;
                case (SquareType.Plain):
                    return 1;
                default:
                    //TODO : Handle this in more graceful way.
                    return -1;
            }
        }
    }
}
