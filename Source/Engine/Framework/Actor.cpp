#include "../Framework/Actor.h"
#include "../Renderer/Model.h"
void bonzai::Actor::update(float deltaTime) {
	if (destroyed) return;
	if (lifespan != 0) {
		lifespan -= deltaTime;
		destroyed = lifespan <= 0;
	}
	if (velocity.x != velocity.x) {
		return;
	}
	transform.position += velocity * deltaTime;
	velocity *= (1.0f / (1.0f + damping)); // Dampen the velocity to simulate friction
}

void bonzai::Actor::draw(Renderer& renderer) {
	if (destroyed) return;
	renderer.drawTexture(texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	
}

float bonzai::Actor::getRadius(){
	 return (texture) ? (texture->getSize().length() * 0.5f * transform.scale *0.9f): 0.0f; 
	
}
