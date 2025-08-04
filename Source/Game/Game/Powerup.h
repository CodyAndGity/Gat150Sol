#pragma once
#include "../../Engine/Framework/Actor.h"

class Powerup:  public bonzai::Actor{
	public:
	Powerup() = default;
	Powerup(const bonzai::Transform& transform, std::shared_ptr<class bonzai::Model> model) :
		bonzai::Actor{ transform, model }
	{}

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(Actor* other) override;



private:


};