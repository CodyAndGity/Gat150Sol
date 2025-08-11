#pragma once
#include "Framework/Actor.h"

class Enemy : public bonzai::Actor {
public:
	float speed{ 200 };
	float shootCooldown{ 0.0f }; // seconds between shots
	Enemy() = default;
	Enemy(const bonzai::Transform& transform) :
		bonzai::Actor{ transform }
	{}

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(Actor* other) override;



private:
	float shootTimer{ 0.0f }; // time until next shot



};