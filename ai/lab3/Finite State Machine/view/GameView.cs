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
using FiniteStateMachine.core;

namespace FiniteStateMachine.view
{
    class GameView
    {

        public GameView()
        {
        }

        public void DrawTransparentRouteHighlight(Vector2 pos, float scale, SpriteBatch spriteBatch)
        {
            Color color = new Color(1.0f, 1.0f, 1.0f, 0.01f);
            spriteBatch.Draw(Game1.m_HighlightTexture,
                pos, //Pos
                null,
                color,
                0,
                new Vector2(0, 0),
                scale, //scale
                SpriteEffects.None,
                0);
        }

        public void DrawTransparentCharacterOnHighlight(Vector2 pos, float scale, SpriteBatch spriteBatch)
        {
            Color color = new Color(1.0f, 1.0f, 1.0f, 0.1f);
            spriteBatch.Draw(Game1.m_Highlight2Texture,
                pos, //Pos
                null,
                color,
                0,
                new Vector2(0, 0),
                scale, //scale
                SpriteEffects.None,
                0);
        }

        public void DrawSquares(float scale, GameModel model, SpriteBatch spriteBatch)
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
                            scale, //scale
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
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.bank):
                        spriteBatch.Draw(Game1.m_BankSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.cemetary):
                        spriteBatch.Draw(Game1.m_CemetarySquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.goldMine):
                        spriteBatch.Draw(Game1.m_GoldMineSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.outlawCamp):
                        spriteBatch.Draw(Game1.m_OutlawCampSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.saloon):
                        spriteBatch.Draw(Game1.m_SaloonSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.shack):
                        spriteBatch.Draw(Game1.m_ShackSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.sheriffsOffice):
                        spriteBatch.Draw(Game1.m_SheriffsOfficeSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    case (SquareType.undertakers):
                        spriteBatch.Draw(Game1.m_UnderTakersSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            scale, //scale
                            SpriteEffects.None,
                            0);
                        break;
                    default:
                        /*
                        spriteBatch.Draw(Game1.m_BankSquareTexture,
                            square.Pos, //Pos
                            null,
                            Color.White,
                            0,
                            new Vector2(0, 0),
                            1, //scale
                            SpriteEffects.None,
                            0);
                         */
                        break;
                }
                if (square.Route)
                {
                    DrawTransparentRouteHighlight(square.Pos, scale, spriteBatch);
                }
                else if (square.CharacterOn)
                {
                    DrawTransparentCharacterOnHighlight(square.Pos, scale, spriteBatch);
                }
            }
        }

        public void DrawAgents(float scale, GameModel model, SpriteBatch spriteBatch)
        {
            foreach (Agent agent in AgentManager.Agents)
            {
                if (agent is Miner)
                {
                    spriteBatch.Draw(Game1.m_MinerTexture,
                        agent.Pos, //Pos
                        null,
                        Color.White,
                        0,
                        new Vector2(0, 0),
                        scale, //scale
                        SpriteEffects.None,
                        0);
                }
                else if (agent is MinersWife)
                {
                    spriteBatch.Draw(Game1.m_MinersWifeTexture,
                        agent.Pos, //Pos
                        null,
                        Color.White,
                        0,
                        new Vector2(0, 0),
                        scale, //scale
                        SpriteEffects.None,
                        0);
                }
                else if (agent is Outlaw)
                {
                    spriteBatch.Draw(Game1.m_OutlawTexture,
                        agent.Pos, //Pos
                        null,
                        Color.White,
                        0,
                        new Vector2(0, 0),
                        scale, //scale
                        SpriteEffects.None,
                        0);
                }
                else if (agent is Sheriff)
                {
                    spriteBatch.Draw(Game1.m_SheriffTexture,
                        agent.Pos, //Pos
                        null,
                        Color.White,
                        0,
                        new Vector2(0, 0),
                        scale, //scale
                        SpriteEffects.None,
                        0);
                }
                else if (agent is Undertaker)
                {
                    spriteBatch.Draw(Game1.m_UndertakerTexture,
                        agent.Pos, //Pos
                        null,
                        Color.White,
                        0,
                        new Vector2(0, 0),
                        scale, //scale
                        SpriteEffects.None,
                        0);
                }
            }
        }

        public void Draw(GameModel model, SpriteBatch spriteBatch)
        {
            float scale = ((float)Constants.SQUARE_SIDE / 100.0f);
            DrawSquares(scale, model, spriteBatch);
            DrawAgents(scale, model, spriteBatch);
        }
    }
}
