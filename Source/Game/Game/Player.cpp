#include "../GamePCH.h"
#include "Player.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Projectile.h"
#include "Core/StringHelper.h"
#include "SpaceGame.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"

FACTORY_REGISTER(Player)


void Player::start() {
     body = owner->getComponent<bonzai::RigidBody>();

}
void Player::update(float deltaTime){
    
    if (starPowerActive) {
        
        powerupTimer += deltaTime;
        //I know it's bad, but it make the player look cool without seizure vibes
        starColorIndex++;
        if (starColorIndex % 512 == 128) {
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                 sprite->setColor({ starColors[starColorIndex % 3] });
            }
        }
        else if (starColorIndex % 512 == 1) {
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[starColorIndex % 3] });
            }

        }
        else if (starColorIndex % 512 == 258) {
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[starColorIndex % 3] });
            }

        }

        if (powerupTimer > 8) {
            starPowerActive = false;
            powerupTimer = 0;
            
            auto body = owner->getComponent<bonzai::RigidBody>();
            if (body) {
                body->damping += 0.0005f;
            }
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }
            


        }
    }
    else if (tripleShotPowerActive) {
        powerupTimer += deltaTime;
        auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            sprite->setColor({ 0,1,1 });
        }
        

        

        if (powerupTimer > 10) {
            tripleShotPowerActive = false;
            powerupTimer = 0;
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }
            


        }
    }else if (laserPowerActive) {
        powerupTimer += deltaTime;
        
        auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            sprite->setColor( { 1,0,1 } );
        }

        if (powerupTimer > 11) {
            laserPowerActive = false;
            powerupTimer = 0;
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }
        }
    }
    else if (healthPowerActive) {
        powerupTimer += deltaTime;
        
        auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            sprite->setColor({ 0,1,0 });
        }
        if (powerupTimer > 10) {
            healthPowerActive = false;
            powerupTimer = 0;
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }

        }
    }
	bool slowDown = false;
    float rotate = 0;
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) {
        rotate = -1;
    }
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) {
        rotate = 1;
    }
    body->applyTorque(rotate* rotateSpeed);
    

    float thrust = 0;
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
    }
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_S)) {
		slowDown = true;
    }
    bonzai::vec2 direction{ 1,0 };
	bonzai::vec2 velocity = direction.rotate(bonzai::math::degToRad(owner->transform.rotation)) *thrust * speed;
    
    if (body) {
        body->applyForce(velocity);//velocity += velocity * deltaTime;
    }

    owner->transform.position.x=bonzai::math::wrap(owner->transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
    owner->transform.position.y = bonzai::math::wrap(owner->transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());
    if (slowDown) {
        
        if (body) {
            //body->damping += 0.0025f;
        }
        
    }
    
    
    if (slowDown) {
        
        if (body) {
            //body->damping -= 0.0025f;
        }
        
    }
    
	shootTimer -= deltaTime;
	//Laser shot
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && laserPowerActive && shootTimer <= 0) {
        shootTimer = shootCooldown/5; // Reset the shoot timer
		shoot( 0.0f, "laser_shot");
    

    }else{
		//Normal shot
        if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && shootTimer <= 0) {
            shootTimer = shootCooldown; // Reset the shoot timer
            
            
			//2 extra shots for triple shot powerup
           
            shoot();
            if (tripleShotPowerActive) {
                shoot( -30.0f);
			    shoot( 30.0f);
            }

        }
    }
    
    
}



void Player::shoot( float angle, std::string type){
    float size = 2.0f;
    if (type == "laser_shot") {
        size = 36.0f;
    }
    bonzai::Transform transform{ owner->transform.position,owner->transform.rotation + angle, size };

    auto projectile = bonzai::Instantiate(type, transform);
    if (type == "rocket") {
        projectile->getComponent<Projectile>()->particleColor = owner->getComponent<bonzai::SpriteRenderer>()->getColor(); 
    }
        
    if (type == "rocket") {
        // try to keep up with the players speed
        projectile->getComponent<Projectile>()->speed = projectile->getComponent<bonzai::RigidBody>()->velocity.length() + 50.0f;

    }
    owner->scene->addActor(std::move(projectile));
    

        
}


void Player::onCollision(bonzai::Actor* other){
    
    if (bonzai::toLower(other->tag) == "enemy" and !starPowerActive) {
        if (healthPowerActive) {
            if(bonzai::random::getReal(0.0f,1.0f)<0.5f){
                health--;
			}
        }
        else {
            health--;
        }
    }
    if(health<=0){
        this->owner->destroyed = true;
        EVENT_NOTIFY(player_dead);
        for (int i = 0; i < 500; i++) {
            bonzai::Particle particle;
            particle.position = owner->transform.position;
            particle.velocity = bonzai::random::onUnitCircle() * bonzai::random::getReal(100.0f, 500.0f);
            auto sprite = owner->getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                particle.color  = sprite->getColor();

            }
           
            particle.lifespan = 1.0f;
            bonzai::getEngine().getParticlesSystem().addParticle(particle);


        }
    }
}

void Player::read(const bonzai::json::value_t& value){
	Object::read(value);
	JSON_READ(value, speed);
	JSON_READ(value, rotateSpeed);
	JSON_READ(value, shootCooldown);
	JSON_READ(value, starPowerActive);
	JSON_READ(value, tripleShotPowerActive);
	JSON_READ(value, laserPowerActive);
	JSON_READ(value, healthPowerActive);
	JSON_READ(value, health);
	//JSON_READ(value, starColors);
}

