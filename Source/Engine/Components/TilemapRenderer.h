#pragma once
#include "RendererComponent.h"

namespace bonzai {
	class TilemapRenderer : public RendererComponent {
	public:
		TilemapRenderer() = default;
		TilemapRenderer(const TilemapRenderer& other);

		CLASS_PROTOTYPE(TilemapRenderer)

		void start() override;
		void update(float dt) override;
		void draw(Renderer& renderer) override;

		void read(const json::value_t& value) override;

	private:
		std::string tilemapName;
		res_t<class Tilemap> tilemap;

		std::vector<std::unique_ptr<PhysicsBody>> physicsBodies;
	};
}
