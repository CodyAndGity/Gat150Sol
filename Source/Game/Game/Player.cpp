#include "../GamePCH.h"
#include "Player.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Projectile.h"

#include "SpaceGame.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"

FACTORY_REGISTER(Player)

void Player::update(float deltaTime){
    // bonzai::getEngine().getAudio().playSound(*bonzai::resources().get<bonzai::AudioClip>("bass.wav", bonzai::getEngine().getAudio()).get());
    auto sound = bonzai::resources().get<bonzai::AudioClip>("bass.wav", bonzai::getEngine().getAudio()).get();
    if (sound) {
        bonzai::getEngine().getAudio().playSound(*sound);
    }
    if (starPowerActive) {
        
        powerupTimer += deltaTime;
        //I know it's bad, but it make the player look cool without seizure vibes
        starColorIndex++;
        if (starColorIndex % 512 == 128) {
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                 sprite->setColor({ starColors[starColorIndex % 3] });
            }
        }
        else if (starColorIndex % 512 == 1) {
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[starColorIndex % 3] });
            }

        }
        else if (starColorIndex % 512 == 258) {
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[starColorIndex % 3] });
            }

        }

        if (powerupTimer > 8) {
            starPowerActive = false;
            powerupTimer = 0;
            
            auto body = getComponent<bonzai::RigidBody>();
            if (body) {
                body->damping += 0.001f;
            }
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }
            


        }
    }
    else if (tripleShotPowerActive) {
        powerupTimer += deltaTime;
        auto sprite = getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            sprite->setColor({ 0,1,1 });
        }
        

        

        if (powerupTimer > 10) {
            tripleShotPowerActive = false;
            powerupTimer = 0;
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }
            


        }
    }else if (laserPowerActive) {
        powerupTimer += deltaTime;
        
        auto sprite = getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            sprite->setColor( { 1,0,1 } );
        }

        if (powerupTimer > 11) {
            laserPowerActive = false;
            powerupTimer = 0;
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                sprite->setColor({ starColors[0] });
            }
        }
    }
    else if (healthPowerActive) {
        powerupTimer += deltaTime;
        
        auto sprite = getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            sprite->setColor({ 0,1,0 });
        }
        if (powerupTimer > 10) {
            healthPowerActive = false;
            powerupTimer = 0;
            auto sprite = getComponent<bonzai::SpriteRenderer>();
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
    transform.rotation += (rotate *rotateSpeed)* deltaTime;

    float thrust = 0;
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
    }
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_S)) {
		slowDown = true;
    }
    bonzai::vec2 direction{ 1,0 };
	bonzai::vec2 velocity = direction.rotate(bonzai::math::degToRad( transform.rotation)) *thrust * speed;
    auto body = getComponent<bonzai::RigidBody>();
    if (body) {
        body->velocity += velocity * deltaTime;
    }

    transform.position.x=bonzai::math::wrap(transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
	transform.position.y = bonzai::math::wrap(transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());
    if (slowDown) {
        auto body = getComponent<bonzai::RigidBody>();
        if (body) {
            body->damping += 0.0025f;
        }
        
    }
    Actor::update(deltaTime);
    if (slowDown) {
        auto body = getComponent<bonzai::RigidBody>();
        if (body) {
            body->damping -= 0.0025f;
        }
        
    }
	shootTimer -= deltaTime;
	//Laser shot
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && laserPowerActive && shootTimer <= 0) {
        shootTimer = shootCooldown/5; // Reset the shoot timer

        
        bonzai::Transform transform{ this->transform.position,this->transform.rotation, 36 };//size
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform);
        
        
        projectile->hasParticles=false; // seconds
        projectile->lifespan = 3.0f; // seconds
        projectile->pierce=5; 
        projectile->speed = 0;
        auto sprite = getComponent<bonzai::SpriteRenderer>();
        if (sprite) {
            projectile->particleColor = sprite->getColor();

        }
       
        projectile->name = "laser"; // Set the name of the player actor
        projectile->tag = "Player"; // Set the name of the player actor
        //components
        auto spriteRenderer = std::make_unique<bonzai::SpriteRenderer>();
        spriteRenderer->textureName = "Textures/laser_shot.png";
        projectile->addComponent(std::move(spriteRenderer));
        
        auto collider = std::make_unique<bonzai::CircleCollider2D>();
        collider->radius = 100.0f; // Set the radius of the collider
        projectile->addComponent(std::move(collider));

        scene->addActor(std::move(projectile));


    }else{
		//Normal shot
        if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && shootTimer <= 0) {
            shootTimer = shootCooldown; // Reset the shoot timer
            
            
			//2 extra shots for triple shot powerup
            if (tripleShotPowerActive) {
                
                
                {
                    bonzai::Transform transform{ this->transform.position,this->transform.rotation - 30.0f, 2 };//size
                    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform);

                    auto spriteRenderer = std::make_unique<bonzai::SpriteRenderer>();
                    spriteRenderer->textureName = "Textures/Projectile.png";
                    spriteRenderer->setColor({ 1.0f,1.0f,1.0f });

                    //projectile->damping = 0.00f;
                    //projectile->speed = this->velocity.length() + 50.0f; // Set speed to a higher value for faster movement
                    projectile->lifespan = 4.0f; // seconds
                    auto sprite = getComponent<bonzai::SpriteRenderer>();
                    if (sprite) {
                        projectile->particleColor = sprite->getColor();

                    }
                    
                    projectile->name = "projectile"; // Set the name of the player actor
                    projectile->tag = "Player"; // Set the name of the player actor
                    projectile->addComponent(std::move(spriteRenderer));

                    auto rigidBody = std::make_unique<bonzai::RigidBody>();
                    rigidBody->damping = 0.0000f;
                    auto body = getComponent<bonzai::RigidBody>();
                    if (body) {
                        projectile->speed = body->velocity.length() + 50.0f; // Set speed to a higher value for faster movement
                        
                    }

                    projectile->addComponent(std::move(rigidBody));

                    auto collider = std::make_unique<bonzai::CircleCollider2D>();
                    collider->radius = 10.0f; // Set the radius of the collider
                    projectile->addComponent(std::move(collider));

                    scene->addActor(std::move(projectile));
                }
                
                bonzai::Transform transform = { this->transform.position,this->transform.rotation + 30.0f, 2 };//size
                std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform);
                
                auto spriteRenderer = std::make_unique<bonzai::SpriteRenderer>();
                spriteRenderer->textureName = "Textures/Projectile.png";
                spriteRenderer->setColor({ 1.0f,1.0f,1.0f });

               
                projectile->lifespan = 4.0f; // seconds
                auto sprite = getComponent<bonzai::SpriteRenderer>();
                if (sprite) {
                    projectile->particleColor = sprite->getColor();

                }
                projectile->name = "projectile"; // Set the name of the player actor
                projectile->tag = "Player"; // Set the name of the player actor
                projectile->addComponent(std::move(spriteRenderer));

                auto rigidBody = std::make_unique<bonzai::RigidBody>();
                rigidBody->damping = 0.0000f;
                auto body = getComponent<bonzai::RigidBody>();
                if (body) {
                    projectile->speed = body->velocity.length() + 50.0f; // Set speed to a higher value for faster movement

                }
                auto collider = std::make_unique<bonzai::CircleCollider2D>();
                collider->radius = 10.0f; // Set the radius of the collider
                projectile->addComponent(std::move(collider));

                projectile->addComponent(std::move(rigidBody));

                scene->addActor(std::move(projectile));

            }


            bonzai::Transform transform{ this->transform.position,this->transform.rotation, 2 };//size
            std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform);

            auto spriteRenderer = std::make_unique<bonzai::SpriteRenderer>();
            spriteRenderer->textureName = "Textures/Projectile.png";
           

            
            
            projectile->lifespan = 4.0f; // seconds
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                projectile->particleColor = sprite->getColor();

            }
            projectile->name = "projectile"; // Set the name of the player actor
            projectile->tag = "Player"; // Set the name of the player actor
            projectile->addComponent(std::move(spriteRenderer));

            auto rigidBody = std::make_unique<bonzai::RigidBody>();
            rigidBody->damping = 0.0000f;
            auto body = getComponent<bonzai::RigidBody>();
            if (body) {
                projectile->speed = body->velocity.length() + 50.0f; // Set speed to a higher value for faster movement

            }

            projectile->addComponent(std::move(rigidBody));

            auto collider = std::make_unique<bonzai::CircleCollider2D>();
            collider->radius = 10.0f; // Set the radius of the collider
            projectile->addComponent(std::move(collider));

            scene->addActor(std::move(projectile));
        }
    }
    

}

void Player::onCollision(Actor* other){
    
    if (other->tag == "Enemy" and !starPowerActive) {
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
        this->destroyed = true;
		dynamic_cast<SpaceGame*>(scene->getGame())->onDeath();
        for (int i = 0; i < 500; i++) {
            bonzai::Particle particle;
            particle.position = transform.position;
            particle.velocity = bonzai::random::onUnitCircle() * bonzai::random::getReal(100.0f, 500.0f);
            auto sprite = getComponent<bonzai::SpriteRenderer>();
            if (sprite) {
                particle.color  = sprite->getColor();

            }
           
            particle.lifespan = 1.0f;
            bonzai::getEngine().getParticlesSystem().addParticle(particle);


        }
    }
}
