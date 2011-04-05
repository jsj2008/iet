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

namespace FiniteStateMachine
{
    public enum AgentType
    {
        miner,
        minersWife,
        sheriff,
        outlaw,
        undertaker
    }

    abstract public class Agent
    {
        private static int agents = 0; 

        // Every agent has a numerical id that is set when it is created
        protected int id;
        public int Id
        {
            get { return id; }
            set { id = value; }
        }

        public StateMachine<Agent> StateMachine
        {
            get;
            set;
        }

        protected float m_Speed;
        public float Speed
        {
            get { return m_Speed; }
            set { m_Speed = value; }
        }

        protected Location location;
        public Location Location
        {
            get { return location; }
            set { location = value; }
        }

        protected AgentType agentType;
        public AgentType AgentType
        {
            get { return agentType; }
            set { agentType = value; }
        }

        protected Vector2 m_Pos; //Updated on every update()
        public Vector2 Pos
        {
            get { return m_Pos; }
            set { m_Pos = value; }
        }

        public Agent()
        {
            id = agents++;
            m_Pos = new Vector2();
            m_Speed = 0.9f;
        }

        // Any agent must implement these methods
        abstract public void Update();
        abstract public bool HandleMessage(Telegram telegram);
    }
}