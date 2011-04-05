using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine.core;

namespace FiniteStateMachine.map
{
    //Central location to manage squares.
    class SquareManager
    {
        private static SquareManager m_Instance = new SquareManager();
        protected Dictionary<int, Square> m_Squares;
        protected Dictionary<Location, int> m_LocationToSquare;
        protected Square[,] m_SquareGrid; //Row x Col of squares

        private SquareManager()
        {
            m_Squares = new Dictionary<int, Square>();
            m_LocationToSquare = new Dictionary<Location, int>();
            m_SquareGrid = new Square[Constants.SCREEN_HEIGHT/Constants.SQUARE_SIDE, 
                Constants.SCREEN_WIDTH/Constants.SQUARE_SIDE];
        }

        public static SquareManager GetInstance()
        {
            return m_Instance;
        }

        public void AddSquare(Square square)
        {
            //This is for generic squares like plain and mountains
            m_Squares.Add(square.Id, square);
            m_SquareGrid[square.GridY(), square.GridX()] = square;
        }

        public void AddLocationSquare(Location location, Square square)
        {
            //Add a location at a given square, this is for West World locations.
            m_Squares.Add(square.Id, square);
            m_SquareGrid[square.GridY(),square.GridX()] = square;
            //m_LocationToSquare.Add(location, square.Id);
            m_LocationToSquare[location] = square.Id;
        }

        public List<Square> GetSquares()
        {
            List<Square> squares = new List<Square>(m_Squares.Values);
            return squares;
        }

        public Square GetSquare(int id)
        {
            return m_Squares[id];
        }

        public Square GetLocationSquare(Location location)
        {
            return m_Squares[m_LocationToSquare[location]];
        }

        public Square GetSquareFromGrid(int i, int j)
        {
           return m_SquareGrid[i, j];
        }

        public int MaxGridI()
        {
            return Constants.SCREEN_HEIGHT/Constants.SQUARE_SIDE;
        }

        public int MaxGridJ()
        {
            return Constants.SCREEN_WIDTH/Constants.SQUARE_SIDE;
        }

        //For non-west world locations, west-world locations will need a remove from both maps.
        public void Remove(int id)
        {
            m_Squares.Remove(id);
        }
    }
}
