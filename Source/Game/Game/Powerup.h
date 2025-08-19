#pragma once
#include "../../Engine/Framework/Component.h"

class Powerup:  public bonzai::Component {
	public:
	Powerup() = default;
	

	void update(float deltaTime) override;
	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) ;



private:


};