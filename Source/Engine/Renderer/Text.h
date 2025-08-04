#pragma once
#include "Font.h"
#include "Renderer.h"
#include "../Math/Vector3.h"
#include <string>
#include <SDL3/SDL.h>
#include <memory>
namespace bonzai {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : font{ font } {}
		~Text();

		bool create(Renderer& renderer, const std::string& text, const vec3& color);
		void draw(Renderer& renderer, float x, float y);

	private:
		std::shared_ptr<Font> font{ nullptr };
		SDL_Texture* texture{ nullptr };
	};


}