#pragma once
#include "Components/ColliderComponent.h"
namespace bonzai {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{ 0.0f }; // Radius of the circle collider
	public:


		// Inherited via ColliderComponent
		void update(float deltatime) override;

		bool checkCollision(ColliderComponent& other) override;

	};
}