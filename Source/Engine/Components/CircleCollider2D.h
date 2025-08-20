#pragma once
#include "Components/ColliderComponent.h"
namespace bonzai {
	 
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{ 0.0f }; // Radius of the circle collider
	public:


		// Inherited via ColliderComponent
		void update(float deltaTime) override;

		bool checkCollision(ColliderComponent& other) override;
		void read(const json::value_t& value) override;

	};
}