#include "SpriteRenderer.h"
#include "../Renderer/Renderer.h"
#include "Engine.h"
namespace bonzai {
	FACTORY_REGISTER(SpriteRenderer)


	void SpriteRenderer::start(){
		// get texture resource if texture doesn't exist and there's a texture name
		if ((!texture) && (textureName!="")) {
			texture = resources().get<Texture>(textureName, getEngine().getRenderer());
		}
		 

	}
	void SpriteRenderer::update(float deltaTime) {
		// No update logic needed for static sprite rendering
	}

	void SpriteRenderer::draw(class Renderer& renderer) {
		//texture = resources().get<Texture>(textureName, renderer);
		if (texture) {
			
			if (textureRect.w > 0 && textureRect.h > 0) {
				renderer.drawTexture(*texture,
					textureRect,
					
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
			else {
				renderer.drawTexture(*texture,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
		
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