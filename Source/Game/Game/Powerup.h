#pragma once
#include "../../Engine/Framework/Component.h"

class Powerup:  public bonzai::Component, public bonzai::ICollidable {
	public:
	Powerup() = default;
	CLASS_PROTOTYPE(Powerup)


	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) override ;



private:


};