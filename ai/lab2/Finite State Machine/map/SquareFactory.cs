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
            //SquareType type = Util.RandomEnum<SquareType>();

            SquareType type;
            int r = Util.m_Random.Next(2);
            if (r == 0)
            {
                type = SquareType.Plain;
            }
            else
            {
                type = SquareType.Mountain;
            }
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

        private SquareType GetSquareTypeFromLocation(Location location)
        {
            switch (location)
            {
                case (Location.bank):
                    return SquareType.bank;
                case (Location.cemetary):
                    return SquareType.cemetary;
                case(Location.goldMine):
                    return SquareType.goldMine;
                case(Location.outlawCamp):
                    return SquareType.outlawCamp;
                case(Location.saloon):
                    return SquareType.saloon;
                case(Location.shack):
                    return SquareType.shack;
                case(Location.sheriffsOffice):
                    return SquareType.sheriffsOffice;
                case(Location.undertakers):
                    return SquareType.undertakers;
                default:
                    return 0;
            }
        }

        //A valid position is one which does not overlap with any other key Locations
        private bool ValidPosition(float x, float y)
        {
            Vector2 myPos = new Vector2(x, y);
            float closestD = float.MaxValue;
            Square closestSquare;
            bool valid = false; //true if not on other key location
            int idToRemove = -1;

            foreach (Square square in SquareManager.GetInstance().GetSquares())
            {
                if ((square.Type != SquareType.Mountain) &&
                    (square.Type != SquareType.Plain))
                {
                    //This is a key location, so we test to see if it is the closest.
                    if (Vector2.Distance(myPos, square.Pos) < closestD)
                    {
                        closestSquare = square;
                        closestD = Vector2.Distance(myPos, square.Pos);
                    }
                    /*
                    if ((square.Pos.X == x) && (square.Pos.Y == y))
                    {
                        return false;
                    }
                     */
                }
                else if ((square.Pos.X == x) && (square.Pos.Y == y))
                {
                    //Square is not a key location, so we get rid of it.
                    //SquareManager.GetInstance().Remove(square.Id);
                    idToRemove = square.Id;
                    valid = true;
                }
            }

            if (valid)
            {
                //It is on a non-key location, so now ensure it is not very close to a key location
                if (closestD <= (Constants.SQUARE_SIDE * 2.0f))
                {
                    //Too close to another location
                    return false;
                }
                else
                {
                    SquareManager.GetInstance().Remove(idToRemove);
                    return true;
                }
            }
            else
            {
                return false;
            }
        }

        private Vector2 GetKeyLocationPos()
        {
            int x, y;
            x = Util.m_Random.Next((Constants.SCREEN_WIDTH / Constants.SQUARE_SIDE) - 1);
            y = Util.m_Random.Next((Constants.SCREEN_HEIGHT / Constants.SQUARE_SIDE) - 1);
            //Keep trying random positions until one comes up which is valid
            while (!ValidPosition(x * Constants.SQUARE_SIDE, y * Constants.SQUARE_SIDE))
            {
                x = Util.m_Random.Next((Constants.SCREEN_WIDTH / Constants.SQUARE_SIDE) - 1);
                y = Util.m_Random.Next((Constants.SCREEN_HEIGHT / Constants.SQUARE_SIDE) - 1);
            }
            return new Vector2(x * Constants.SQUARE_SIDE, y * Constants.SQUARE_SIDE);
        }

        private void AddLocationSquare(Location location)
        {
            Square square = new Square(GetSquareTypeFromLocation(location), GetKeyLocationPos());
            SquareManager.GetInstance().AddLocationSquare(location, square);
        }

        public void PopulateMapWithWestWorld()
        {
            //Add all locations to the world
            foreach (Location location in Enum.GetValues(typeof(Location)))
            {
                AddLocationSquare(location);
            }
        }
    }
}
