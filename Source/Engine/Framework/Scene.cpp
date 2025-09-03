#include "Scene.h"
#include "Core/Json.h"
#include "../Renderer/Renderer.h"
#include "Components/ColliderComponent.h"

//temporary includes, just to test stuff
//#include "../Game/Game/Player.h"
//#include "../Game/Game/Enemy.h"
namespace bonzai {

	void Scene::read(const json::value_t& value) {

		//read prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::getInstance().create<Actor>("Actor");
				actor->read(actorValue);
				//add prototype to factory
				std::string actorName = actor->name;
				Factory::getInstance().RegisterPrototype<Actor>(actorName, std::move(actor));
				
			}
		}

		//read actors
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::getInstance().create<Actor>("Actor");
				actor->read(actorValue);
				addActor(std::move(actor), false);
			}
		}

	}

	bool Scene::load(const std::string& sceneName) {
		//load json
		bonzai::json::document_t document;
		if (!(bonzai::json::load(sceneName, document))) {
			Logger::Error("Failed to load scene: {}", sceneName);
			return false;
		}
		//create scene
		read(document);

		//start actors
		for (auto& actor : actors) {
			actor->start();
		}
		return true;
	}


	void Scene::update(float deltaTime) {
		for (auto& actor : actors) {
			if (actor->active) {
				actor->update(deltaTime);
			}
		}
		//remove destroyed actors
		std::erase_if(actors, [](auto& actor) {
			return (actor->destroyed);
		});



		////check for collisions
		//for (auto& actorA : actors) {
		//	for (auto& actorB : actors) {
		//		if (actorA == actorB || actorA->destroyed || actorB->destroyed) continue; //skip self, just in case the're destroyed
		//		auto colliderA = actorA->getComponent<ColliderComponent>();
		//		auto colliderB = actorB->getComponent<ColliderComponent>();

		//		if (colliderA == nullptr || colliderB == nullptr) continue; //skip if no collider

		//		if (colliderA->checkCollision(*colliderB)) {
		//			actorA->onCollision(actorB.get());
		//			actorB->onCollision(actorA.get());
		//			
		//		}
		//		
		//	}
		//}


	}
	void Scene::draw(class Renderer& renderer) {
		for (auto& actor : actors) {
			if (actor->active) {
				actor->draw(renderer);
			}
		}
	}
	void Scene::addActor(std::unique_ptr<class Actor> actor, bool start)	{
		actor->scene = this; // Set the scene pointer for the actor
		if (start) {
			actor->start(); // Call start method when adding the actor to the scene
		}
		actors.push_back(std::move(actor));

	}

	void Scene::removeAllActors(bool force)	{
		if (force) {
			actors.clear();
		}
		else {
			for (auto iterator = actors.begin(); iterator != actors.end();) {
				if (!(*iterator)->persistent) {
					iterator = actors.erase(iterator);
				}
				else {
					iterator++;
				}
			}
			
		}
	}
	
}