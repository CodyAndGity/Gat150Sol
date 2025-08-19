#include "Component.h"
#include "Object.h"
#include "Components/RendererComponent.h"
namespace bonzai {
	FACTORY_REGISTER(Actor);


	void Actor::update(float deltaTime) {
		if (destroyed) return;

		if (lifespan > 0) {
			lifespan -= deltaTime;
			if (lifespan <= 0) {
				destroyed = true;
				return;
			}

		}
		//Update all components
		for (auto& component : components) {
			if (component->active) {
				component->update(deltaTime);
			}
		}

	}

	void Actor::draw(Renderer& renderer) {
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
	void Actor::addComponent(std::unique_ptr<Component> component){
		component->owner = this;
		components.push_back(std::move(component));
	}
	void Actor::read(const json::value_t& value) {
		Object::read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);

		if (JSON_HAS(value, transorm)) {
			transform.read(JSON_Get(value,transform));
		}
		
	}
}



