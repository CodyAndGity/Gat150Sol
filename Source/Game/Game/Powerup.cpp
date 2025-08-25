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
	
	if (other->name == "Player") {
		owner->scene->getGame()->addScore(250);

		bonzai::Actor* playerActor = owner->scene->getActorByName<bonzai::Actor>("Player");
		auto player = playerActor->getComponent<Player>();

		if (bonzai::toLower(owner->name) == "star") {
			player->starPowerActive = true;
			
			
			auto playerBody = player->owner->getComponent<bonzai::RigidBody>();
			if (playerBody) {
				playerBody->damping -= 0.0005f;
			}
			
			
			auto sprite = player->owner->getComponent<bonzai::SpriteRenderer>();
			sprite->setColor({ 1, 1, 0 });
		}else if (bonzai::toLower(owner->name) == "health") {
			player->health = player->health + 3;
			
			auto sprite = player->owner->getComponent<bonzai::SpriteRenderer>();
			sprite->setColor({ 0, 1, 0 });
			player->healthPowerActive = true;

		}else if (bonzai::toLower(owner->name) == "tripleshot") {
			player->tripleShotPowerActive = true;

		}else if (bonzai::toLower(owner->name) == "laser") {
			player->laserPowerActive = true;

		}
		owner->destroyed = true;
		
	}
}
