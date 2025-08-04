#pragma once
#include "../Core/StringHelper.h"
#include <vector>
#include <memory>
#include <list>
#include <string>
namespace bonzai {
	class Actor;
	class Game;

	class Scene {
	public:
		Scene(Game* game) : game{ game }{}

		void update(float deltaTime);
		void draw(class Renderer& renderer);

		void addActor(std::unique_ptr< Actor> actor);
		void removeAllActors();
		template<typename T = Actor>
		 T* getActorByName(const std::string& name);

		 template<typename T=Actor>
		 std::vector<T*> getActorByTag(const std::string& tag);
		  Game* getGame() const { return game; }
	private:
		 Game* game{ nullptr };
		std::list<std::unique_ptr<  Actor>> actors;


	};
	/// <summary>
	/// Retrieves an actor from the scene by name and casts it to the specified type.
	/// </summary>
	/// <typeparam name="T">The type to which the found actor should be cast.</typeparam>
	/// <param name="name">The name of the actor to search for (case-insensitive).</param>
	/// <returns>A pointer to the actor of type T if found and the cast succeeds; otherwise, nullptr.</returns>
	template<typename T>
	inline T* Scene::getActorByName(const std::string& name){
		for(auto& actor : actors) {
			if (toLower(actor->name) == toLower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if(object) {
					return object;
				}
			}
		}
		return nullptr;
	}

	/// <summary>
	/// Retrieves all actors in the scene with a tag matching the specified string and casts them to the specified type.
	/// </summary>
	/// <typeparam name="T">The type to which matching actors will be dynamically cast.</typeparam>
	/// <param name="tag">The tag to match against each actor's tag (case-insensitive).</param>
	/// <returns>A vector of pointers to actors of type T whose tag matches the specified tag.</returns>
	template<typename T>
	inline std::vector<T*> Scene::getActorByTag(const std::string& tag)	{
		std::vector<T*> results;
		for(auto& actor : actors) {
			if (bonzai::toLower(actor->tag) == bonzai::toLower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if(object) {
					results.push_back(object);
				}
			}
		}
		return results;
	}
}