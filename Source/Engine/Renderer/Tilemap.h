#pragma once

namespace bonzai {
	class Tilemap : public Resource {
	public:
		struct Layer {
			int height{ 0 };
			int width{ 0 };
			bool hasCollision{ true };
			std::vector<int> data;
			res_t<Texture> texture;
		};

	public:
		Tilemap() = default;
		~Tilemap() = default;

		bool load(const std::string& filename, class Renderer& renderer);

		const std::vector<Layer>& getLayers() const { return layers; }
		rect getTextureRect(const Layer& layer, int tileId);
		vec2 getPosition(const Layer& layer, int tileIndex);

	private:
		int tileheight{ 0 };
		int tilewidth{ 0 };

		std::vector<Layer> layers;
	};
}
