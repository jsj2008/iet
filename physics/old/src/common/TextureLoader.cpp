#include "TextureLoader.hpp"

#include <assert.h>
#include <common/tga.h> 

TextureLoader TextureLoader::m_Instance;

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::Init()
{
	m_CurrentTextureId = 0;
	m_IsInit = true;
}

TextureLoader& TextureLoader::GetInstance()
{
	if( ! TextureLoader::m_Instance.IsInit())
	{
		TextureLoader::m_Instance.Init();
	}
	return TextureLoader::m_Instance;
}

bool TextureLoader::LoadTexture(const char* filename, int textureId)
{
    if (!loadTGA (filename, textureId))
    {
		assert( 0 && "Texture not found!" );
		return false;
    }
	return true;
}
