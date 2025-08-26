#pragma once
#include "Framework/Component.h"

class Enemy : public bonzai::Component, public bonzai::ICollidable, public bonzai::IObserver {
public:
	float speed{ 200 };
	float shootCooldown{ 3.0f }; // seconds between shots
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void start() override;
	// Inherited via IObserver
	void onNotify(const bonzai::Event& event) override;
	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) override ;

	bonzai::RigidBody* body{ nullptr };

private:
	float shootTimer{ 0.0f }; // time until next shot





};