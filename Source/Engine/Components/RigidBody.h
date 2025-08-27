#pragma once
#include "Framework/Component.h"


namespace bonzai {
	class RigidBody : public Component {
	public:
		PhysicsBody::PhysicsBodyDef bodyDef;
		vec2 size{ 0,0 };
		vec2 velocity{ 0,0 };
		float damping{ 0.0f }; 
	public:
		RigidBody() = default;
		RigidBody(const RigidBody& other);
		void start() override;

		CLASS_PROTOTYPE(RigidBody)
		void update(float deltaTime) override;
		void read(const json::value_t& value) override;

		void applyForce(const vec2& force);
		void applyTorque(const float radians);

		void setVelocity(const vec2& velocity);
	private:
		std::unique_ptr<PhysicsBody> physicsBody;
	};
}