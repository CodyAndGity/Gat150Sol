#pragma once


#include "Framework/Component.h"
#include "Math/Vector3.h"

class Projectile : public bonzai::Component, public bonzai::ICollidable {
public:
	int pierce{ 1 };
	float speed{ 000 };
	bool hasParticles{ true };
	bonzai::vec3 particleColor{ 0,0,0 };
	Projectile() = default;
	CLASS_PROTOTYPE(Projectile)

	bonzai::RigidBody* body{ nullptr };

	void update(float deltaTime) override;

	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) override ;
	void read(const bonzai::json::value_t& value);
	void start() override;


private:




};