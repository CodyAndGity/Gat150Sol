#include "../GamePCH.h"
#include "PlayerController.h"
#include "ProjectileController.h"
FACTORY_REGISTER(PlayerController)

void PlayerController::start() {
	body = owner->getComponent<bonzai::RigidBody>();
	owner->getComponent<bonzai::SpriteRenderer>()->setColor({ 0.5f,0.5f,1.0f });

}
void PlayerController::update(float deltaTime) {
	float dir = 0;
	if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) {
		dir = -1;
		playerLeft = true;

	}
	if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) {
		dir = 1;
		playerLeft = false;
	}
	if (dir != 0) {
		body->applyForce(bonzai::vec2{ 1,0 }*dir * speed);
	}
	if (bonzai::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		body->applyForce(bonzai::vec2{ 0,-1 } * jump);

	}
	auto spriteRenderer = owner->getComponent<bonzai::SpriteRenderer>();
	if (spriteRenderer) {
		if (body->velocity.x != 0) {
			spriteRenderer->flipH = (body->velocity.x < 0);//playerLeft;
		}
	}
	if (bonzai::getEngine().getInput().getMouseButtonPressed(bonzai::InputSystem::MouseButton::LEFT)) {
		shoot(playerLeft *180.0f);

	}
	if (bonzai::getEngine().getInput().getMouseButtonPressed(bonzai::InputSystem::MouseButton::RIGHT)) {
		bonzai::Transform transform{ {10,500},0, 1 };

		auto bat =bonzai::Instantiate("bat", transform);
		//bat->getComponent<bonzai::SpriteRenderer>()->setColor({ 0,0,0 });

		owner->scene->addActor(std::move(bat));

	}

}
void PlayerController::shoot(float angle, std::string type) {
	float size = 2.0f;
	if (type == "laser_shot") {
		size = 36.0f;
	}
	bonzai::Transform transform{ owner->transform.position,owner->transform.rotation + angle, size };

	auto projectile = bonzai::Instantiate(type, transform);
	if (type == "PlatformerRocket") {
		auto cache= owner->getComponent<bonzai::SpriteRenderer>()->getColor();
		projectile->getComponent<ProjectileController>()->particleColor = cache;
	}

	if (type == "PlatformerRocket") {
		// try to keep up with the players speed
		//projectile->getComponent<ProjectileController>()->speed = projectile->getComponent<bonzai::RigidBody>()->velocity.length() + 50.0f;

	}
	owner->scene->addActor(std::move(projectile));



}

void PlayerController::onCollision(class bonzai::Actor* other) {
	if (other->tag == "Enemy") {
		owner->getComponent<bonzai::SpriteRenderer>()->setColor({ 1111,0,0 });
	}
	else {
		owner->getComponent<bonzai::SpriteRenderer>()->setColor({ 1,1,1 });

	}
}
void PlayerController::read(const bonzai::json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, shootCooldown);
	JSON_READ(value, jump);

}
