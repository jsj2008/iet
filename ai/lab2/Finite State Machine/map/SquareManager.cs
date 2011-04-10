using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FiniteStateMachine.map
{
    //Central location to manage squares.
    class SquareManager
    {
        private static SquareManager m_Instance = new SquareManager();
        protected Dictionary<int, Square> m_Squares;
        protected Dictionary<Location, int> m_LocationToSquare;

        private SquareManager()
        {
            m_Squares = new Dictionary<int, Square>();
            m_LocationToSquare = new Dictionary<Location, int>();
        }

        public static SquareManager GetInstance()
        {
            return m_Instance;
        }

        public void AddSquare(Square square)
        {
            //This is for generic squares like plain and mountains
            m_Squares.Add(square.Id, square);
        }

        public void AddLocationSquare(Location location, Square square)
        {
            //Add a location at a given square, this is for West World locations.
            m_Squares.Add(square.Id, square);
            m_LocationToSquare.Add(location, square.Id);
        }

        public List<Square> GetSquares()
        {
            List<Square> squares = new List<Square>(m_Squares.Values);
            return squares;
        }
    }
}
