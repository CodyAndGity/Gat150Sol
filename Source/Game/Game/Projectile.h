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
	Projectile(const bonzai::Transform& transform, bonzai::res_t<bonzai::Texture> texture) :
		bonzai::Actor{ transform, texture }
	{}

	void update(float deltaTime) override;

	// Inherited via Actor
	void onCollision(Actor* other) override;


private:




};