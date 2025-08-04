#pragma once
//copy over enemy but make it projectile

#include "Framework/Actor.h"
#include "Math/Vector3.h"
class Projectile : public bonzai::Actor {
public:
	int pierce{ 1 };
	float speed{ 200 };
	bool hasParticles{ true };
	bonzai::vec3 particleColor{ 0,0,0 };
	Projectile() = default;
	Projectile(const bonzai::Transform& transform, std::shared_ptr<class bonzai::Model> model) :
		bonzai::Actor{ transform, model }
	{}

	void update(float deltaTime) override;

	// Inherited via Actor
	void onCollision(Actor* other) override;


private:




};