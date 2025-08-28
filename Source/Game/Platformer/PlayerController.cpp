#include "../GamePCH.h"
#include "PlayerController.h"
void PlayerController::start() {
	body = owner->getComponent<bonzai::RigidBody>();

}
void PlayerController::update(float deltaTime) {
	float dir = 0;
	if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) {
		dir = -1;
		std::cout << "hi" << std::endl;
	}
	if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) {
		dir = 1;
	}
	if (dir != 0) {
		body->applyForce(bonzai::vec2{ 1,0 }*dir * 1000);
	}
	if (bonzai::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		body->applyForce(bonzai::vec2{ 0,-1 } * 1000000);

	}

}
void PlayerController::onCollision(class bonzai::Actor* other) {

}
void PlayerController::read(const bonzai::json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, shootCooldown);
	JSON_READ(value, jump);

}
