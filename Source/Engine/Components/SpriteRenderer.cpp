#include "SpriteRenderer.h"
#include "../Renderer/Renderer.h"
namespace bonzai {
	void SpriteRenderer::update(float deltatime) {
		// No update logic needed for static sprite rendering
	}

	void SpriteRenderer::draw(class Renderer& renderer) {
		renderer.drawTexture(resources().get<Texture>(textureName, renderer).get(),
			owner->transform.position.x, owner->transform.position.y,
			owner->transform.rotation,owner->transform.scale	);
	}
}