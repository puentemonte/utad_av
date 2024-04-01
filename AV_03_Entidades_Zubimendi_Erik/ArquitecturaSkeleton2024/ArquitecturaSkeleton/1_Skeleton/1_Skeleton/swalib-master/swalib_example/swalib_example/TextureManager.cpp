//#include "TextureManager.h"
//#include "../../common/core.h"
//
//TextureManager::TextureManager()
//{
//
//}
//
//TextureManager* TextureManager::Get()
//{
//	if (m_TextureManager != nullptr)
//	{
//		m_TextureManager = new TextureManager();
//	}
//	return m_TextureManager;
//}
//
//void TextureManager::LoadTexture(const char* _file, bool _bWrap)
//{
//	CORE_LoadPNG(_file, _bWrap);
//}
//
//void TextureManager::UnloadTexture(GLuint _texture)
//{
//	CORE_UnloadPNG(_texture);
//}
//
////void TextureManager::AddTexture(Sprite* _sprite)
////{
////	m_Textures.push_back(_sprite);
////}
//
////std::vector<Sprite*> TextureManager::GetTextures()
////{
////	return m_Textures;
////}
