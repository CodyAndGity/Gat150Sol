#include "Renderer.h"
#include "Texture.h"

namespace bonzai {

    bool Renderer::initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            Logger::Error("SDL_Init Error: ", SDL_GetError());
           
            return false;
        }

        if (!TTF_Init()) {
			Logger::Error("TTF_Init Error: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    bool Renderer::createWindow(const std::string& name, int width, int height, bool fullscreen)   {
		this->width = width;
		this->height = height;

        window = SDL_CreateWindow(name.c_str(), width, height, fullscreen ? SDL_WINDOW_FULLSCREEN:0);
        if (window == nullptr) {
			Logger::Error("Failed to create SDL Window: {}", SDL_GetError());
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == nullptr) {
			Logger::Error("Failed to create SDL Renderer: {}", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
		SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        return true;
    }

    void Renderer::drawTexture(Texture& texture, float x, float y){
        vec2 size = texture.getSize();

            SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = size.x;
        destRect.h = size.y;

        
        SDL_RenderTexture(renderer, texture.texture, NULL, &destRect);
    }
    void Renderer::drawTexture(Texture& texture, float x, float y, float angle, float scale ) {
        vec2 size = texture.getSize();

        SDL_FRect destRect;
        destRect.w = size.x *scale;
        destRect.h = size.y * scale;
        destRect.x = x- destRect.w * 0.5f;
        destRect.y = y- destRect.h * 0.5f;
		;

        SDL_RenderTextureRotated(renderer, texture.texture, NULL, &destRect,angle,NULL,SDL_FLIP_NONE);
		SDL_SetTextureColorModFloat(texture.texture, texture.color.r, texture.color.g, texture.color.b);
    }

    void Renderer::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);

    }

    void Renderer::setColor(float r, float g, float b, float a) {
		SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
    }

    void Renderer::drawLine(float x1, float y1, float x2, float y2) {
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }

    void Renderer::drawPoint(float x1, float y1) {
		SDL_RenderPoint(renderer, x1, y1);
    }

    void  Renderer::clear() {
        SDL_RenderClear(renderer);
    }

    void Renderer::present() {
        SDL_RenderPresent(renderer);
    }

    void Renderer::shutdown() {
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
}