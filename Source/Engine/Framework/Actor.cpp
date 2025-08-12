#include "Component.h"
#include "Object.h"
#include "Components/RendererComponent.h"
void bonzai::Actor::update(float deltaTime) {
	if (destroyed) return;

	if (lifespan > 0) {
		lifespan -= deltaTime;
		if (lifespan <= 0) {
			destroyed = true;
			return;
		}
		
	}
	
	for(auto& component : components) {
		if (component->active) {
			component->update(deltaTime);
		}
	}

}

void bonzai::Actor::draw(Renderer& renderer) {
	if (destroyed) return;

	for (auto& component : components) {
		if (component->active) {
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->draw(renderer);
			}
		}
	}
	//renderer.drawTexture(texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	
}

float bonzai::Actor::getRadius(){
	return 50.f;//(texture) ? (texture->getSize().length() * 0.5f * transform.scale *0.9f): 0.0f; 
	
}

void bonzai::Actor::addComponent(std::unique_ptr<Component> component){
	component->owner = this;
	components.push_back(std::move(component));
}
