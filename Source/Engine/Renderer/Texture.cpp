#include "Texture.h"
#include "Renderer.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include "../Math/Vector2.h"
namespace bonzai {
    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (texture) SDL_DestroyTexture(texture);
    }

    bool Texture::load(const std::string& filename, Renderer& renderer)
    {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface==nullptr){
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        texture = SDL_CreateTextureFromSurface(renderer.renderer,surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!texture){
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    vec2 Texture::getSize(){
        
        float w, h;
        SDL_GetTextureSize(texture, &w, &h);
		
		
        return { w, h };
		
    }


}

