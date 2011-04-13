#ifndef  TEXTURELOADER_H
#define  TEXTURELOADER_H

#include <string>

/*
 * =====================================================================================
 *        Class: TextureLoader
 *  Description:
 * =====================================================================================
 */
class TextureLoader
{
	public:

		static TextureLoader& GetInstance();

		void Init();

		bool IsInit()
		{
			return m_IsInit;
		}

		int GetNextTextureId()
		{
			return m_CurrentTextureId++;
		}

		bool LoadTexture(const char* filename, int textureId);

	protected:

		TextureLoader();

		virtual ~TextureLoader();

		static TextureLoader m_Instance;
		int m_CurrentTextureId;
		bool m_IsInit;
	private:
};

#endif   // TEXTURELOADER_H
