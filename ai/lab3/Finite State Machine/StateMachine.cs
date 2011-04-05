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
    // This class implements normal states, global states and state blips for a given agent.
    // The agent should create its own StateMachine when its constructor is called.
    public class StateMachine<T> where T : Agent
    {
        private T owner;

        private bool m_CurrentlyPathfinding;

        // This holds the current state for the state machine
        private State<T> currentState = null;
        public State<T> CurrentState
        {
            get { return currentState; }
            set { currentState = value; }
        }

        // The agent's previous state is needed to implement state blips
        private State<T> previousState = null;
        public State<T> PreviousState
        {
            get { return previousState; }
            set { previousState = value; }
        }

        // The agent's global state is always executed, if it exists
        private State<T> globalState = null;
        public State<T> GlobalState
        {
            get { return globalState; }
            set { globalState = value; }
        }

        // What a lovely constructor
        public StateMachine(T agent)
        {
            owner = agent;
            m_CurrentlyPathfinding = false;
        }

        // This is called by the Agent whenever the Game invokes the Agent's Update() method
        public void Update()
        {
            if (globalState != null)
            {
                globalState.Execute(owner);
            }
            if (currentState != null)
            {
                currentState.Execute(owner);
            }
        }

        // This method attempts to deliver a message first via the global state, and if that fails
        // via the current state
        public bool HandleMessage(Telegram telegram)
        {
            if (globalState != null)
            {
                if (globalState.OnMesssage(owner, telegram))
                {
                    return true;
                }

            }
            if (currentState != null)
            {
                if (currentState.OnMesssage(owner, telegram))
                {
                    return true;
                }
            }
            return false;
        }

        // Switch to a new state and save the old one, so we can revert to it later if it's a state blip
        public void ChangeState(State<T> newState)
        {
            if ( ! m_CurrentlyPathfinding)
            {
                previousState = currentState; //Save state before pathfinding
                currentState.Exit(owner);
                //Now put pathfinding state in between...
                currentState = new PfState<T>(newState,
                    previousState.StateLocation(),
                    newState.StateLocation());
                currentState.Enter(owner);
                m_CurrentlyPathfinding = true;
            }
            else
            {
                //Finished pathfinding to location.
                currentState.Exit(owner);

                currentState = newState;
                currentState.Enter(owner);
                m_CurrentlyPathfinding = false;
            }
        }

        // Invoked when a state blip is finished
        public void RevertToPreviousState()
        {
            ChangeState(previousState);
        }

        // Checks whether the machine is in a given state
        public Boolean IsInState(State<T> state)
        {
            return state.Equals(currentState);
        }	
    }
}