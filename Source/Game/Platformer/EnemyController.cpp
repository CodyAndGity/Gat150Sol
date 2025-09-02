#include "../GamePCH.h"
#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::start() {
	body = owner->getComponent<bonzai::RigidBody>();

}
void EnemyController::update(float deltaTime) {
	float dir = 0;
	bonzai::Actor* player = owner->scene->getActorByName<bonzai::Actor>("PlatformPlayer");
	//move to player
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) {
			dir = -1;
		}
		else {
			dir = 1;
		}
	}
	
	if (dir != 0) {
		body->applyForce(bonzai::vec2{ 1,0 }*dir * speed);
	}
	

}
void EnemyController::onCollision(class bonzai::Actor* other) {
	if (owner->tag != other->tag && other->tag != "Powerup") {
		this->owner->destroyed = true;
		EVENT_NOTIFY_DATA(add_points, 100);

		for (int i = 0; i < 100; i++) {
			bonzai::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = bonzai::random::onUnitCircle() * bonzai::random::getReal(100.0f, 200.0f);

			auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
			if (sprite) {
				particle.color = sprite->getColor();

			}
			particle.lifespan = 0.80f;
			bonzai::getEngine().getParticlesSystem().addParticle(particle);


		}
	}
}
void EnemyController::read(const bonzai::json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, shootCooldown);
	JSON_READ(value, jump);

}
