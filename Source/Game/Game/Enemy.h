#pragma once
#include "Framework/Component.h"

class Enemy : public bonzai::Component {
public:
	float speed{ 200 };
	float shootCooldown{ 0.0f }; // seconds between shots
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)


	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) ;



private:
	float shootTimer{ 0.0f }; // time until next shot



};