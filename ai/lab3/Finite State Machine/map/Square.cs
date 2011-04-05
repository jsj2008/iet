using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using FiniteStateMachine.core.types;
using FiniteStateMachine.core;

namespace FiniteStateMachine.map
{
    //A square in the game world.
    class Square
    {
        protected SquareType m_Type;
        protected Vector2 m_Pos;
        protected int m_Id;
        private static int m_SquareCnt = 0;
        protected bool m_Route;
        protected bool m_CharacterOn;

        public bool Route
        {
            get { return m_Route; }
            set { m_Route = value; }
        }

        public bool CharacterOn
        {
            get { return m_CharacterOn; }
            set { m_CharacterOn = value; }
        }

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

        //Grid positions
        public int GridX()
        {
            return (int)(m_Pos.X / Constants.SQUARE_SIDE);
        }

        public int GridY()
        {
            return (int)(m_Pos.Y / Constants.SQUARE_SIDE);
        }

        public Square(SquareType type, Vector2 pos)
        {
            m_Id = m_SquareCnt++;
            m_Type = type;
            m_Pos = pos;
            m_Route = false;
            m_CharacterOn = false;
        }

        public int GetMovementCost()
        {
            switch (m_Type)
            {
                case (SquareType.Mountain):
                    return 20;
                case (SquareType.Plain):
                    return 1;
                default:
                    //TODO : Handle this in more graceful way.
                    return 0;
            }
        }
    }
}
