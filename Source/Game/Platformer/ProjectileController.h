#pragma once
#include "Components/RigidBody.h"
#include "Framework/Component.h"
#include "Math/Vector3.h"
#include "Physics/ICollidable.h"
class ProjectileController : public bonzai::Component, public bonzai::ICollidable {
public:
	int pierce{ 1 };
	float speed{ 000 };
	bool hasParticles{ true };
	bonzai::vec3 particleColor{ 0,0,0 };
	ProjectileController() = default;
	CLASS_PROTOTYPE(ProjectileController)

	bonzai::RigidBody* body{ nullptr };

	void update(float deltaTime) override;

	// Inherited via Actor
	void onCollision(class bonzai::Actor* other) override;
	void read(const bonzai::json::value_t& value);
	void start() override;


private:




};