#include "Powerup.h"
#include "Player.h"
#include "Engine.h"
#include "Core/StringHelper.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"


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
			player->damping = player->damping-0.001f;
			player->model->setColor({ 1,1,0 });

		}else if (bonzai::toLower(name) == "health") {
			player->health = player->health + 3;
			player->model->setColor({ 0,1,0 });

		}else if (bonzai::toLower(name) == "tripleshot") {
			player->tripleShotPowerActive = true;

		}else if (bonzai::toLower(name) == "laser") {
			player->laserPowerActive = true;

		}
		destroyed = true;
		
	}
}
