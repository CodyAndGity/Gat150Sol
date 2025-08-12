#include "Powerup.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Components/SpriteRenderer.h"

void Powerup::update(float deltaTime){
	transform.position.x = bonzai::math::wrap(transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
	transform.position.y = bonzai::math::wrap(transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());

	Actor::update(deltaTime);

}

void Powerup::onCollision(Actor* other){
	if (other->name == "Player") {
		scene->getGame()->addScore(250);

		Player* player =dynamic_cast<Player*> (other);
		if (bonzai::toLower(name) == "star") {
			player->starPowerActive = true;

			
			auto playerBody = player->getComponent<bonzai::RigidBody>();
			if (playerBody) {
				playerBody->damping -= 0.001f;
			}
			dynamic_cast<bonzai::SpriteRenderer*>(player->components[0].get())->setColor( { 1,1,0 });

		}else if (bonzai::toLower(name) == "health") {
			player->health = player->health + 3;
			dynamic_cast<bonzai::SpriteRenderer*>(player->components[0].get())->setColor({ 0,1,0 });

			player->healthPowerActive = true;

		}else if (bonzai::toLower(name) == "tripleshot") {
			player->tripleShotPowerActive = true;

		}else if (bonzai::toLower(name) == "laser") {
			player->laserPowerActive = true;

		}
		destroyed = true;
		
	}
}
