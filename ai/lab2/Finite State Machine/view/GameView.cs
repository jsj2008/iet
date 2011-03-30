using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;
using FiniteStateMachine.core.types;
using FiniteStateMachine.model;
using FiniteStateMachine.map;

namespace FiniteStateMachine.view
{
    class GameView
    {

        public GameView()
        {
        }

        public void Draw(GameModel model, SpriteBatch spriteBatch)
        {
            foreach (Square square in model.Squares)
            {
                switch (square.Type)
                {
                    case (SquareType.Mountain):
                        spriteBatch.Draw(Game1.m_MountainSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            1, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.Plain):
                        spriteBatch.Draw(Game1.m_PlainSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            1, //scale
                            SpriteEffects.None,
                            0);
                        break;
                }
            }
        }
    }
}
