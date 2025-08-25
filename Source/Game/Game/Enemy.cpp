#include "../GamePCH.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"

#include "Projectile.h"
#include "Components/SpriteRenderer.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Core/Random.h"
#include "Framework/Actor.h"
FACTORY_REGISTER(Enemy)


/// <summary>
/// Updates the enemy's state, moving it towards the player and handling screen wrapping.
/// </summary>
/// <param name="deltaTime">The time elapsed since the last update, used to ensure frame-rate independent movement.</param>
void Enemy::update(float deltaTime){
    bool playerSeen{ false };

	bonzai::Actor* player = owner->scene->getActorByName<bonzai::Actor>("Player");

    
    
    if (player) {
      bonzai::vec2 direction{0,0 };
		direction = player->transform.position - owner->transform.position; // Calculate direction towards the player
        
		//if the player is close to the edge, use the screen wrap to get to the player faster
        //left edge x
        if (bonzai::math::fabs(direction.x) > bonzai::math::fabs(player->transform.position.x + bonzai::getEngine().getRenderer().getWidth() - owner->transform.position.x)) {
           
            direction.x = player->transform.position.x + bonzai::getEngine().getRenderer().getWidth() - owner->transform.position.x;
        } else if (bonzai::math::fabs(direction.x) > bonzai::math::fabs(player->transform.position.x - bonzai::getEngine().getRenderer().getWidth() - owner->transform.position.x)) {
            //right edge x    
            direction.x = player->transform.position.x - bonzai::getEngine().getRenderer().getWidth() - owner->transform.position.x;
        }

        //bottom edge y
        if (bonzai::math::fabs(direction.y) > bonzai::math::fabs(player->transform.position.y + bonzai::getEngine().getRenderer().getHeight() - owner->transform.position.y)) {
            direction.y = player->transform.position.y + bonzai::getEngine().getRenderer().getHeight() - owner->transform.position.y;
        }else if (bonzai::math::fabs(direction.y) > bonzai::math::fabs(player->transform.position.y - bonzai::getEngine().getRenderer().getHeight() - owner->transform.position.y)) {
            //top edge y
            direction.y = player->transform.position.y - bonzai::getEngine().getRenderer().getHeight() - owner->transform.position.y;
        }
		direction = direction.normalized(); // Normalize the direction vector
        bonzai::vec2 forward = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(owner->transform.rotation));
        float angle = bonzai::math::radToDeg( bonzai::vec2::angleBetween (forward,direction));


        playerSeen = (angle < 30);
        if (playerSeen) {
            angle = (bonzai::vec2::signedAngleBetween(forward, direction));
            angle = bonzai::math::sign(angle);

            owner->transform.rotation += bonzai::math::radToDeg(angle * deltaTime * 10);
            bonzai::vec2 velocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(owner->transform.rotation)) * speed;
            
            auto body= owner->getComponent<bonzai::RigidBody>();
            if(body) {
                body->velocity +=velocity* deltaTime;
			}

        }else{
            angle = bonzai::random::getReal(0.1f);
            owner->transform.rotation += bonzai::math::radToDeg(angle * deltaTime * 10);
            bonzai::vec2 velocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(owner->transform.rotation)) * speed*0.1f;
            auto body = owner->getComponent<bonzai::RigidBody>();
            if (body) {
                body->velocity += velocity * deltaTime;
            }

        }
    }
    
    

    owner->transform.position.x = bonzai::math::wrap(owner->transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
    owner->transform.position.y = bonzai::math::wrap(owner->transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());
    shootTimer -= deltaTime;
    if ( shootTimer <= 0 && playerSeen) {
        shootTimer = shootCooldown; // Reset the shoot timer
    
        bonzai::Transform transform{ owner->transform.position,owner->transform.rotation, 2 };//size

        auto projectile = bonzai::Instantiate("Rocket", transform);
        projectile->getComponent<bonzai::SpriteRenderer>()->setColor({ 1.0f,1.0f,1.0f });
		projectile->getComponent<bonzai::SpriteRenderer>()->textureName = "Textures/enemy_projectile.png";
        projectile->getComponent<Projectile>()->particleColor = owner->getComponent<bonzai::SpriteRenderer>()->getColor();
		projectile->tag = "enemy"; 
		projectile->name = "Rocket"; 

        projectile->getComponent<Projectile>()->speed = 300;
        projectile->getComponent<bonzai::CircleCollider2D>()->radius = 10.0f; // Set the radius of the collider


        projectile->lifespan = 2.0f; // seconds
        owner->scene->addActor(std::move(projectile));
    }
    
}

void Enemy::onCollision(bonzai::Actor* other){
    if (owner->tag !=other->tag) {
        this->owner->destroyed = true;
        owner->scene->getGame()->addScore(100);
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
