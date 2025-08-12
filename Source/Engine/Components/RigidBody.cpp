#include "RigidBody.h"

namespace bonzai {
	void RigidBody::update(float deltaTime){
		if (velocity.x != velocity.x) {
			return;
		}

		owner->transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + damping)); // Dampen the velocity to simulate friction
	}
}