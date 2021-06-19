#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"
#include <Renderer/Texture.h>

using SharedTexture = std::shared_ptr<K9::Texture>;

class TextureManager
{
public:
    static SharedTexture LoadTexture(const char* fileName);
    static void Draw(const SharedTexture& texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);

private:
    static SDL_Color s_tintColor;
};

#endif
