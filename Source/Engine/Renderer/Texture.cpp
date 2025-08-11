#include "Texture.h"
#include "Renderer.h"

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
			Logger::Error("Could not load image: {}", filename);
            
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        texture = SDL_CreateTextureFromSurface(renderer.renderer,surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!texture){
			Logger::Error("Could not create texture from surface: {}", filename);
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

