#pragma once
#include "Resources/Resource.h"
#include "Renderer.h"
#include "Math/Vector2.h"
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

namespace bonzai {

	class Texture :public Resource{
	public:
		Texture() = default;
		~Texture();

		bool load(const std::string& filename, class Renderer& renderer);
		vec2 getSize();
		friend class Renderer;
	struct SDL_Texture* texture{ nullptr };

	private:
	};
}