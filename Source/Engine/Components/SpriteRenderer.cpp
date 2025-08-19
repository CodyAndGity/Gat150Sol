#include "SpriteRenderer.h"
#include "../Renderer/Renderer.h"
#include "Engine.h"
namespace bonzai {
	FACTORY_REGISTER(SpriteRenderer)
	void SpriteRenderer::update(float deltaTime) {
		// No update logic needed for static sprite rendering
	}

	void SpriteRenderer::draw(class Renderer& renderer) {
		auto texture = resources().get<Texture>(textureName, renderer).get();
		if (texture) {
		renderer.drawTexture(*texture,
			owner->transform.position.x, owner->transform.position.y,
			owner->transform.rotation, owner->transform.scale);
		}
	}
	bonzai::vec3 SpriteRenderer::getColor()	{
		return resources().get<Texture>(textureName, bonzai::getEngine().getRenderer()).get()->color;
		
	}
	void SpriteRenderer::setColor(vec3 color) {
		resources().get<Texture>(textureName, bonzai::getEngine().getRenderer()).get()->color=color;
	}
	void SpriteRenderer::read(const json::value_t& value) {
		Object::read(value);
		JSON_READ(value, textureName);


	}

}