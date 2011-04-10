using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using FiniteStateMachine.core;
using FiniteStateMachine.core.types;
using FiniteStateMachine.util;

namespace FiniteStateMachine.map
{
    //Used to create the map.
    class SquareFactory
    {
        private static SquareFactory m_Instance = new SquareFactory();

        private SquareFactory()
        {
        }

        public static SquareFactory GetInstance()
        {
            return m_Instance;
        }

        //Returns a square randomly initialised to one of the entries in the SquareType enum
        protected Square CreateRandomSquare(float x, float y)
        {
            SquareType type = Util.RandomEnum<SquareType>();
            return new Square(type, new Vector2(x,y));
        }

        //This will initialize the mountains and plains as squares.
        public void InitialMapPopulation()
        {
            //Populate the columns and rows
            for (int i = 0; (i * Constants.SQUARE_SIDE) < Constants.SCREEN_HEIGHT; i++)
            {
                for (int j = 0; (j * Constants.SQUARE_SIDE) < Constants.SCREEN_WIDTH; j++)
                {
                    Square square = CreateRandomSquare((j * Constants.SQUARE_SIDE), (i * Constants.SQUARE_SIDE));
                    SquareManager.GetInstance().AddSquare(square);
                }
            }
        }
    }
}
