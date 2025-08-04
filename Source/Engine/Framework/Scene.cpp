#include "Scene.h"
#include "../Framework/Actor.h"
#include "../Renderer/Renderer.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
namespace bonzai {
	void Scene::update(float deltaTime) {
		for (auto& actor : actors) {
			actor->update(deltaTime);
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

		for (auto& actorA : actors) {
			for (auto& actorB : actors) {
				if (actorA == actorB || actorA->destroyed || actorB->destroyed) continue; //skip self, just in case the're destroyed
				float distance = (actorA->transform.position - actorB->transform.position).length();
				if(distance <= (actorA->getRadius() + actorB->getRadius())) {
					actorA->onCollision(actorB.get());
					actorB->onCollision(actorA.get());
				}
			}
		}
		//check for collisions


	}
	void Scene::draw(class Renderer& renderer) {
		for (auto& actor : actors) {
			actor->draw(renderer);
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