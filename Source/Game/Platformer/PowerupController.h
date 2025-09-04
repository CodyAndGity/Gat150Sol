#pragma once
#include "../../Engine/Framework/Component.h"

class PowerupController : public bonzai::Component, public bonzai::ICollidable {
public:
	PowerupController() = default;
	CLASS_PROTOTYPE(PowerupController)

	void start() override;

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) override;

public:
	bonzai::RigidBody* body{ nullptr };


private:


};