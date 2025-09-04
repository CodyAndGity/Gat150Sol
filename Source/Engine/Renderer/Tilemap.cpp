#include "EngineMinimal.h"
#include "Tilemap.h"

namespace bonzai {
	bool Tilemap::load(const std::string& filename, class Renderer& renderer) {
		// load json
		bonzai::json::document_t document;
		if (!bonzai::json::load(filename, document)) {
			Logger::Error("Could not load Tilemap json {}", filename);
			return false;
		}

		// read tilemap data
		JSON_READ(document, tileheight);
		JSON_READ(document, tilewidth);

		// read tilemap layers
		if (JSON_HAS(document, layers)) {
			for (auto& layerValue : JSON_GET(document, layers).GetArray()) {
				Layer layer;

				JSON_READ_NAME(layerValue, "height", layer.height);
				JSON_READ_NAME(layerValue, "width", layer.width);
				JSON_READ_NAME(layerValue, "data", layer.data);

				// load texture from properties
				if (JSON_HAS(layerValue, properties)) {
					for (auto& propertyValue : JSON_GET(layerValue, properties).GetArray()) {

						std::string name;
						JSON_READ(propertyValue, name);

						// check if property name is TextureName
						
						if (equalsIgnoreCase(name, "TextureName")) {
							// read texture name value (texture name)
							std::string value;
							JSON_READ(propertyValue, value);

							layer.texture = resources().get<Texture>(value, renderer);
							if (!layer.texture) {
								Logger::Warning("Could not read tilemap layer texture {}.", value);
								return false;
							}
						}
						else if (equalsIgnoreCase(name, "Collision")) {
							JSON_READ_NAME(propertyValue, "value", layer.hasCollision);

						}
					}
				}

				layers.push_back(layer);
			}
		}

		return true;
	}

	rect Tilemap::getTextureRect(const Layer& layer, int tileId) {
		if (tileId == 0) return {}; // empty tile

		// calculate tiles per row from texture size
		vec2 textureSize = layer.texture->getSize();
		int tilesPerRow = (int)(textureSize.x / layer.width);

		int column = (tileId - 1) % tilesPerRow; // Tiled uses 1-based indexing
		int row = (tileId - 1) / tilesPerRow;

		return rect{
			(float)(column*tilewidth),
			(float)(row * tileheight),
			(float)(tilewidth),
			(float)(tileheight)
		};
	}

	vec2 Tilemap::getPosition(const Layer& layer, int tileIndex) {
		int tileX = tileIndex % layer.width;
		int tileY = tileIndex / layer.width;
		return vec2{(float)tileX*tilewidth,(float)tileY*tileheight};
	}
}