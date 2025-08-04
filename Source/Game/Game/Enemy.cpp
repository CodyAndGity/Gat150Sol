#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Framework/Game.h"
#include "Projectile.h"
#include "Renderer/Model.h"
#include "GameData.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"

/// <summary>
/// Updates the enemy's state, moving it towards the player and handling screen wrapping.
/// </summary>
/// <param name="deltaTime">The time elapsed since the last update, used to ensure frame-rate independent movement.</param>
void Enemy::update(float deltaTime){
    bool playerSeen{ false };

	Player* player = scene->getActorByName<Player>("Player");

    
    if (player) {
      bonzai::vec2 direction{0,0 };
		direction = player->transform.position - transform.position; // Calculate direction towards the player
        
		//if the player is close to the edge, use the screen wrap to get to the player faster
        //left edge x
        if (bonzai::math::fabs(direction.x) > bonzai::math::fabs(player->transform.position.x + bonzai::getEngine().getRenderer().getWidth() - transform.position.x)) {
           
            direction.x = player->transform.position.x + bonzai::getEngine().getRenderer().getWidth() - transform.position.x;
        } else if (bonzai::math::fabs(direction.x) > bonzai::math::fabs(player->transform.position.x - bonzai::getEngine().getRenderer().getWidth() - transform.position.x)) {
            //right edge x    
            direction.x = player->transform.position.x - bonzai::getEngine().getRenderer().getWidth() - transform.position.x;
        }

        //bottom edge y
        if (bonzai::math::fabs(direction.y) > bonzai::math::fabs(player->transform.position.y + bonzai::getEngine().getRenderer().getHeight() - transform.position.y)) {
            direction.y = player->transform.position.y + bonzai::getEngine().getRenderer().getHeight() - transform.position.y;
        }else if (bonzai::math::fabs(direction.y) > bonzai::math::fabs(player->transform.position.y - bonzai::getEngine().getRenderer().getHeight() - transform.position.y)) {
            //top edge y
            direction.y = player->transform.position.y - bonzai::getEngine().getRenderer().getHeight() - transform.position.y;
        }
		direction = direction.normalized(); // Normalize the direction vector
        bonzai::vec2 forward = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(transform.rotation));
        float angle = bonzai::math::radToDeg( bonzai::vec2::angleBetween (forward,direction));


        playerSeen = (angle < 30);
        if (playerSeen) {
            angle = (bonzai::vec2::signedAngleBetween(forward, direction));
            angle = bonzai::math::sign(angle);

            transform.rotation += bonzai::math::radToDeg(angle * deltaTime * 10);
            bonzai::vec2 velocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(transform.rotation)) * speed;
            this->velocity += velocity * deltaTime;
        }else{
            angle = bonzai::random::getReal(0.1f);
            transform.rotation += bonzai::math::radToDeg(angle * deltaTime * 10);
            bonzai::vec2 velocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(transform.rotation)) * speed*0.1f;
            this->velocity += velocity * deltaTime;

        }
    }
    
    

    transform.position.x = bonzai::math::wrap(transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
    transform.position.y = bonzai::math::wrap(transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());
    
    shootTimer -= deltaTime;
    if ( shootTimer <= 0 && playerSeen) {
        shootTimer = shootCooldown; // Reset the shoot timer

        std::shared_ptr<bonzai::Model> model = std::make_shared <bonzai::Model>(GameData::projectilePoints, bonzai::vec3{ 1.0f,0.0f,0.0f });
        bonzai::Transform transform{ this->transform.position,this->transform.rotation, 2 };//size
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, model);
        projectile->damping = 0.003f;
        projectile->speed = this->speed + bonzai::random::getReal(100.0f)+200;
        projectile->lifespan = 2.0f; // seconds
        projectile->particleColor = model->getColor();
        projectile->name = "projectile"; // Set the name of the player actor
        projectile->tag = "Enemy"; // Set the name of the player actor

        scene->addActor(std::move(projectile));

    }
    Actor::update(deltaTime);
}

void Enemy::onCollision(Actor* other){
    if (tag !=other->tag) {
        this->destroyed = true;
		scene->getGame()->addScore(100);
        for (int i = 0; i < 100; i++) {
            bonzai::Particle particle;
            particle.position = transform.position;
			particle.velocity = bonzai::random::onUnitCircle() * bonzai::random::getReal(100.0f, 200.0f);
            particle.color = model->getColor();
            particle.lifespan = 0.80f;
            bonzai::getEngine().getParticlesSystem().addParticle(particle);
            
                
        }
    }
}
