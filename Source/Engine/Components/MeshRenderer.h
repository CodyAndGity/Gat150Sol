#pragma once


#include "Components/RendererComponent.h"
namespace bonzai {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;
	public:
		void update(float deltaTime) override;
		void draw(class Renderer& renderer) override;
		bonzai::vec3 getColor();
		void setColor(vec3 color);
		void read(const json::value_t& value) override;

	private:
	};
}