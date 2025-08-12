#pragma once
#include "Framework/Object.h"
#include "Framework/Component.h"
#include "Math/Transform.h"
#include "../Renderer/Model.h"
#include "Renderer/Texture.h"
#include <string>
#include <memory>
#include <vector>
namespace bonzai {
	class Actor :public Object{
	public:
		
		std::string tag;
		Transform transform;
		std::shared_ptr<Model> model;
		

		
		bool destroyed{ false };
		float lifespan{ 0.0f }; 
		class Scene* scene{ nullptr }; // Pointer to the scene this actor belongs to
		std::vector<std::unique_ptr<Component>> components;

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}

		virtual void update(float deltaTime);
		virtual void draw(class Renderer& renderer);
		Transform& getTransform() { return transform; }

		virtual void onCollision(Actor* other)=0;
		
		void addComponent(std::unique_ptr<Component> component);
		
		template<typename T>
		T* getComponent();

		template<typename T>
		std::vector<T*> getComponents();

	protected:


	};
	template<typename T>
	inline T* Actor::getComponent()	{
		for (auto& component : components) {
			auto result =dynamic_cast<T*>(component.get());
			if(result) {
				return result;
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Actor::getComponents()	{
		std::vector<T*> results;
		for (auto& component : components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}