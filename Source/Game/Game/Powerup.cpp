#include "../GamePCH.h"
#include "Powerup.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Components/SpriteRenderer.h"

FACTORY_REGISTER(Powerup)

void Powerup::update(float deltaTime){
	

}

void Powerup::onCollision(bonzai::Actor* other){
	auto test = other->name;
	if (other->name == "Player") {
		owner->scene->getGame()->addScore(250);

		Player* player =dynamic_cast<Player*> (other);
		if (bonzai::toLower(name) == "star") {
			player->starPowerActive = true;

			
			auto playerBody = player->owner->getComponent<bonzai::RigidBody>();
			if (playerBody) {
				playerBody->damping -= 0.001f;
			}
			
			
			auto sprite = player->owner->getComponent<bonzai::SpriteRenderer>();
			sprite->setColor({ 1, 1, 0 });
		}else if (bonzai::toLower(name) == "health") {
			player->health = player->health + 3;
			
			auto sprite = player->owner->getComponent<bonzai::SpriteRenderer>();
			sprite->setColor({ 0, 1, 0 });
			player->healthPowerActive = true;

		}else if (bonzai::toLower(name) == "tripleshot") {
			player->tripleShotPowerActive = true;

		}else if (bonzai::toLower(name) == "laser") {
			player->laserPowerActive = true;

		}
		owner->destroyed = true;
		
	}
}
