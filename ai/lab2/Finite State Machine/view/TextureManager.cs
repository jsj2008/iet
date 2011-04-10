using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using FiniteStateMachine.core.types;

namespace FiniteStateMachine.view
{
    class TextureManager
    {
        private static TextureManager m_Instance = new TextureManager();
        protected ContentManager m_ContentManager;
        Texture2D m_MountainSquareTexture;
        Texture2D m_PlainSquareTexture;

        Texture2D GetMountainSquareTexture()
        {
            return m_MountainSquareTexture;
        }

        Texture2D GetPlainSquareTexture()
        {
            return m_PlainSquareTexture;
        }

        private TextureManager()
        {

        }

        public static TextureManager GetInstance()
        {
            return m_Instance;
        }
    }
}
