#pragma once
#include "../../Engine/Framework/Actor.h"

class Powerup:  public bonzai::Actor{
	public:
	Powerup() = default;
	Powerup(const bonzai::Transform& transform) :
		bonzai::Actor{ transform }
	{}

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(Actor* other) override;



private:


};