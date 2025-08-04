#include "Renderer.h"
#include <SDL3/SDL.h>

namespace bonzai {

    bool Renderer::initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    bool Renderer::createWindow(const std::string& name, int width, int height)   {
		this->width = width;
		this->height = height;
        window = SDL_CreateWindow(name.c_str(), width, height, 0);
        if (window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
        return true;
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