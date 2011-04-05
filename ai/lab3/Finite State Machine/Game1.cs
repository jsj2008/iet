using System;
using System.Collections.Generic;
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
using FiniteStateMachine.view;
using FiniteStateMachine.map;
using FiniteStateMachine.pathfinding;

namespace FiniteStateMachine
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        Miner Bob;
        MinersWife Elsa;
        Outlaw Jesse;
        Sheriff Wyatt;
        Undertaker Vincent;
        SpriteBatch spriteBatch;
        SpriteFont spriteFont;

        public static Texture2D m_MountainSquareTexture;
        public static Texture2D m_PlainSquareTexture;
        public static Texture2D m_BankSquareTexture;
        public static Texture2D m_CemetarySquareTexture;
        public static Texture2D m_GoldMineSquareTexture;
        public static Texture2D m_OutlawCampSquareTexture;
        public static Texture2D m_SaloonSquareTexture;
        public static Texture2D m_ShackSquareTexture;
        public static Texture2D m_SheriffsOfficeSquareTexture;
        public static Texture2D m_UnderTakersSquareTexture;
        public static Texture2D m_HighlightTexture;
        public static Texture2D m_Highlight2Texture;

        public static Texture2D m_MinerTexture;
        public static Texture2D m_MinersWifeTexture;
        public static Texture2D m_OutlawTexture;
        public static Texture2D m_SheriffTexture;
        public static Texture2D m_UndertakerTexture;

        private GameModel m_Model;
        private GameView m_GameView;

        private PfNodeFactory m_PfNodeFactory;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferHeight = 600;
            graphics.PreferredBackBufferWidth = 800;
            graphics.ApplyChanges();
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // Here's a little hack: The Miner and MinersWife must know each other's id in
            // order to communicate.  We calculate them inside each agent based on their
            // creation order, so the pair must always be created in this sequence.
            Bob = new Miner();
            Elsa = new MinersWife();
            Jesse = new Outlaw();
            Wyatt = new Sheriff();
            Vincent = new Undertaker();
            AgentManager.AddAgent(Bob);
            AgentManager.AddAgent(Elsa);
            AgentManager.AddAgent(Jesse);
            AgentManager.AddAgent(Wyatt);
            AgentManager.AddAgent(Vincent);

            //Create map and pathfinding graph
            SquareFactory.GetInstance().InitialMapPopulation();
            SquareFactory.GetInstance().PopulateMapWithWestWorld();
            m_PfNodeFactory = new PfNodeFactory();
            m_PfNodeFactory.CreatePfGraphFromWorldGeom(SquareManager.GetInstance());

            m_Model = new GameModel();
            m_GameView = new GameView();

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            spriteFont = Content.Load<SpriteFont>("Arial");
            m_PlainSquareTexture = Content.Load<Texture2D>(@SquareType.Plain.ToString());
            m_MountainSquareTexture = Content.Load<Texture2D>(@SquareType.Mountain.ToString());
            m_BankSquareTexture = Content.Load<Texture2D>(@SquareType.bank.ToString());
            m_CemetarySquareTexture = Content.Load<Texture2D>(@SquareType.cemetary.ToString());
            m_GoldMineSquareTexture = Content.Load<Texture2D>(@SquareType.goldMine.ToString());
            m_OutlawCampSquareTexture = Content.Load<Texture2D>(@SquareType.outlawCamp.ToString());
            m_SaloonSquareTexture = Content.Load<Texture2D>(@SquareType.saloon.ToString());
            m_ShackSquareTexture = Content.Load<Texture2D>(@SquareType.shack.ToString());
            m_SheriffsOfficeSquareTexture = Content.Load<Texture2D>(@SquareType.sheriffsOffice.ToString());
            m_UnderTakersSquareTexture = Content.Load<Texture2D>(@SquareType.undertakers.ToString());
            m_HighlightTexture = Content.Load<Texture2D>("highlight");
            m_Highlight2Texture = Content.Load<Texture2D>("highlight_2");


            m_MinerTexture = Content.Load<Texture2D>("miner");
            m_MinersWifeTexture = Content.Load<Texture2D>("minerswife");
            m_OutlawTexture = Content.Load<Texture2D>("outlaw");
            m_SheriffTexture = Content.Load<Texture2D>("sheriff");
            m_UndertakerTexture = Content.Load<Texture2D>("undertaker");
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                this.Exit();
            Message.gameTime = gameTime;
            Bob.Update();
            Bob.Speed = ((float)gameTime.ElapsedGameTime.Milliseconds) * 0.1f;
            //Bob.Speed = 0.00001f;
            Elsa.Update();
            Jesse.Update();
            Wyatt.Update();
            Vincent.Update();

            Message.SendDelayedMessages();

            //Get squares from squaremanager to be displayed
            m_Model.Squares = SquareManager.GetInstance().GetSquares();
            IPriorityQueue[] seq = new IPriorityQueue[PfNodeManager.GetInstance().GetSequences().Count];
            PfNodeManager.GetInstance().GetSequences().CopyTo(seq);
            m_Model.Sequences = seq;
            m_Model.SetSquaresFromSequences();

            /*
            Agent[] agents = AgentManager.Agents.ToArray();
            for (int i = 0 ; i < agents.Length ; i++)
            {
                Agent agent = agents[i];
                agent.Pos = SquareManager.GetInstance().GetLocationSquare(agent.Location).Pos;
            }
             */

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

            spriteBatch.Begin();
            m_GameView.Draw(m_Model, spriteBatch);
            spriteBatch.End();
            //Printer.Draw(spriteBatch, spriteFont);
            
            //base.Draw(gameTime);
        }
    }
}
