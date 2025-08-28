#include "../GamePCH.h"
#include "EnemyController.h"
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
		body->applyForce(bonzai::vec2{ 1,0 }*dir * 1000);
	}
	

}
void EnemyController::onCollision(class bonzai::Actor* other) {

}
void EnemyController::read(const bonzai::json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, shootCooldown);
	JSON_READ(value, jump);

}
