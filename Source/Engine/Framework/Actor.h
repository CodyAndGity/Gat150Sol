#pragma once
#include "Framework/Object.h"
#include "Framework/Component.h"
#include "Math/Transform.h"
#include "../Renderer/Model.h"
#include "Renderer/Texture.h"
#include <string>
#include <memory>
namespace bonzai {
	class Actor :public Object{
	public:
		
		std::string tag;
		Transform transform;
		std::shared_ptr<Model> model;
		

		vec2 velocity{ 0,0 };
		float damping{ 0.0f };
		bool destroyed{ false };
		float lifespan{ 0.0f }; 
		class Scene* scene{ nullptr }; // Pointer to the scene this actor belongs to

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}

		virtual void update(float deltaTime);
		virtual void draw(class Renderer& renderer);
		Transform& getTransform() { return transform; }

		virtual void onCollision(Actor* other)=0;
		float getRadius();
		void addComponent(std::unique_ptr<Component> component);

	protected:
		std::vector<std::unique_ptr<Component>> components;


	};
}