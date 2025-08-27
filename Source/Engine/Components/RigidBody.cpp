#include "RigidBody.h"
#include "Components/SpriteRenderer.h"
#include "Engine.h"
namespace bonzai {
	FACTORY_REGISTER(RigidBody)

	RigidBody::RigidBody(const RigidBody& other){
		bodyDef = other.bodyDef;
		size = other.size;
		if (other.physicsBody) {
			physicsBody = std::make_unique<PhysicsBody>(*other.physicsBody);
		}
	}

	void RigidBody::start()	{
		bodyDef.actor = owner;
		if (size.x == 0 && size.y == 0) {
			auto spriteRenderer = owner->getComponent<SpriteRenderer>();
			if (spriteRenderer) {
				size = spriteRenderer->texture->getSize();
			}
		}
		physicsBody = std::make_unique<PhysicsBody>(owner->transform,size,bodyDef,getEngine().getPhysics());
	}
	void RigidBody::update(float deltaTime){
		owner->transform.position = physicsBody->getPosition();
		owner->transform.rotation = math::radToDeg(physicsBody->getAngle());
		//if (velocity.x != velocity.x) {
		//	return;
		//}
		//owner->transform.position += velocity * deltaTime;
		//velocity *= (1.0f / (1.0f + damping)); // Dampen the velocity to simulate friction
	}
	void RigidBody::applyForce(const vec2& force) {
		physicsBody->applyForce(force);
	}
	void RigidBody::applyTorque(const float radians) {
		physicsBody->applyTorque(radians);

	}
	void RigidBody::setVelocity(const vec2& velocity) {
		physicsBody->setVelocity(velocity);

	}


	void RigidBody::read(const json::value_t& value){
		Object::read(value);

		JSON_READ(value, size);
		//JSON_READ(value, scale);


		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);
		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);
		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);
		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", bodyDef.friction);
		JSON_READ_NAME(value, "restitution", bodyDef.restitution);
		JSON_READ_NAME(value, "density", bodyDef.density);
		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {
			
			if (equalsIgnoreCase(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;
			else if (equalsIgnoreCase(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (equalsIgnoreCase(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}
}