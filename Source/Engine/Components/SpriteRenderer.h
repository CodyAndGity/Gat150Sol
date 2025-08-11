#pragma once

#include "Components/RendererComponent.h"
namespace bonzai {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
	public:
		void update(float deltatime) override;
		void draw(class Renderer& renderer) override;
	};
}