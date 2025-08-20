#include "RigidBody.h"

namespace bonzai {
	FACTORY_REGISTER(RigidBody)

	void RigidBody::update(float deltaTime){
		if (velocity.x != velocity.x) {
			return;
		}

		owner->transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + damping)); // Dampen the velocity to simulate friction
	}
	void RigidBody::read(const json::value_t& value){
		Object::read(value);
		JSON_READ(value, damping);
		JSON_READ(value, velocity);
	}
}