#pragma once
#include "Framework/Actor.h"

class Enemy : public bonzai::Actor {
public:
	float speed{ 200 };
	float shootCooldown{ 0.0f }; // seconds between shots
	Enemy() = default;
	Enemy(const bonzai::Transform& transform, std::shared_ptr<class bonzai::Model> model) :
		bonzai::Actor{ transform, model }
	{}

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(Actor* other) override;



private:
	float shootTimer{ 0.0f }; // time until next shot



};