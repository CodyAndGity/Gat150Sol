#pragma once
#include "../../Engine/Framework/Component.h"

class Powerup:  public bonzai::Component {
	public:
	Powerup() = default;
	/*Powerup(const bonzai::Transform& transform) :
		bonzai::Actor{ transform }
	{}*/

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class Actor* other) ;



private:


};