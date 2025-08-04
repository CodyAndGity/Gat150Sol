#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
namespace bonzai {
	class Font {
	public:
		Font() = default;
		~Font();

		bool load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* ttfFont{ nullptr };
	};

}