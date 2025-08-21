#pragma once

#include "Components/RendererComponent.h"
namespace bonzai {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
	public:
		CLASS_PROTOTYPE(SpriteRenderer)
		void update(float deltaTime) override;
		void draw(class Renderer& renderer) override;
		bonzai::vec3 getColor();
		void setColor(vec3 color);
		void read(const json::value_t& value) override;

	private:
	};
}