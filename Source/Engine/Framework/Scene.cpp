#include "Scene.h"
#include "Core/Json.h"
#include "../Renderer/Renderer.h"
#include "Components/ColliderComponent.h"

namespace bonzai {

	void Scene::read(const json::value_t& value) {
		//read actors
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::getInstance().create<Actor>("Actor");
				actor->read(actorValue);
				addActor(std::move(actor));
			}
		}

	}
	void Scene::update(float deltaTime) {
		for (auto& actor : actors) {
			if (actor->active) {
				actor->update(deltaTime);
			}
		}
		//remove destroyed actors
		for (auto iterator = actors.begin(); iterator != actors.end();) {
			if ((*iterator)->destroyed) {
				 iterator= actors.erase(iterator);
			}
			else {
				iterator++;
			}
		}

		//check for collisions
		for (auto& actorA : actors) {
			for (auto& actorB : actors) {
				if (actorA == actorB || actorA->destroyed || actorB->destroyed) continue; //skip self, just in case the're destroyed
				auto colliderA = actorA->getComponent<ColliderComponent>();
				auto colliderB = actorB->getComponent<ColliderComponent>();

				if (colliderA == nullptr || colliderB == nullptr) continue; //skip if no collider

				if (colliderA->checkCollision(*colliderB)) {
					actorA->onCollision(actorB.get());
					actorB->onCollision(actorA.get());
				}
				
			}
		}


	}
	void Scene::draw(class Renderer& renderer) {
		for (auto& actor : actors) {
			if (actor->active) {
				actor->draw(renderer);
			}
		}
	}
	void Scene::addActor(std::unique_ptr<class Actor> actor)	{
		actor->scene = this; // Set the scene pointer for the actor
		actors.push_back(std::move(actor));

	}

	void Scene::removeAllActors()	{
		actors.clear();
	}
	
}