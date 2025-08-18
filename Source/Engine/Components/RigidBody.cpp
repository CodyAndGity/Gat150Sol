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
}