#pragma once


#include "Framework/Component.h"
#include "Math/Vector3.h"

class Projectile : public bonzai::Component {
public:
	int pierce{ 1 };
	float speed{ 200 };
	bool hasParticles{ true };
	bonzai::vec3 particleColor{ 0,0,0 };
	Projectile() = default;
	CLASS_PROTOTYPE(Projectile)


	void update(float deltaTime) override;

	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) ;


private:




};