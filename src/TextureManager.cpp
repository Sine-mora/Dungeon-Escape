#include "TextureManager.h"
#include <Renderer/Renderer2D.h>

SDL_Color TextureManager::s_tintColor{ 255, 255, 255, 255 };

SharedTexture TextureManager::LoadTexture(const char* fileName) {
    SharedTexture texture = std::make_shared<K9::Texture>();
    if (texture->Load(fileName))
    {
        return texture;
    }
    return nullptr;
}

void TextureManager::Draw(const SharedTexture& texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
    K9::Renderer2D::Ref().DrawTexture(texture, sourceRectangle, destinationRectangle, s_tintColor, flip);
}
