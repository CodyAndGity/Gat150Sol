#include "SpriteRenderer.h"
#include "../Renderer/Renderer.h"
#include "Engine.h"
namespace bonzai {
	void SpriteRenderer::update(float deltaTime) {
		// No update logic needed for static sprite rendering
	}

	void SpriteRenderer::draw(class Renderer& renderer) {
		renderer.drawTexture(resources().get<Texture>(textureName, renderer).get(),
			owner->transform.position.x, owner->transform.position.y,
			owner->transform.rotation,owner->transform.scale	);
	}
	bonzai::vec3 SpriteRenderer::getColor()	{
		return resources().get<Texture>(textureName, bonzai::getEngine().getRenderer()).get()->color;
		
	}
	void SpriteRenderer::setColor(vec3 color) {
		resources().get<Texture>(textureName, bonzai::getEngine().getRenderer()).get()->color=color;
	}

}