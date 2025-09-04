#include "../GamePCH.h"
#include "PowerupController.h"

#include "PlayerController.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Components/SpriteRenderer.h"

FACTORY_REGISTER(PowerupController)

void PowerupController::start() {
	body = owner->getComponent<bonzai::RigidBody>();

}

void PowerupController::onCollision(bonzai::Actor* other) {

	if (other->name == "PlatformPlayer") {
		owner->scene->getGame()->addScore(250);

		bonzai::Actor* playerActor = owner->scene->getActorByName<bonzai::Actor>("PlatformPlayer");
		auto player = playerActor->getComponent<PlayerController>();

		if (bonzai::toLower(owner->name) == "star") {
			player->starPowerActive = true;


			auto playerBody = player->owner->getComponent<bonzai::RigidBody>();
			if (playerBody) {
				playerBody->damping -= 0.0005f;
			}


			auto sprite = player->owner->getComponent<bonzai::SpriteRenderer>();
			sprite->setColor({ 1, 1, 0 });
		}
		else if (bonzai::toLower(owner->name) == "health") {
			player->health = player->health + 3;

			auto sprite = player->owner->getComponent<bonzai::SpriteRenderer>();
			sprite->setColor({ 0, 1, 0 });
			player->healthPowerActive = true;

		}
		else if (bonzai::toLower(owner->name) == "tripleshot") {
			player->tripleShotPowerActive = true;

		}
		else if (bonzai::toLower(owner->name) == "laser") {
			player->laserPowerActive = true;

		}
		owner->destroyed = true;

	}
}
void PowerupController::update(float deltaTime) {
	float dir = 0;
	bonzai::Actor* player = owner->scene->getActorByName<bonzai::Actor>("PlatformPlayer");
	//move to player
	if (player) {
		bonzai::vec2 direction = player->transform.position - owner->transform.position;
		body->applyForce(direction.normalized() * 4);
	}
}

