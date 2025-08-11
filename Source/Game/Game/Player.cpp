#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "GameData.h"
#include "Framework/Scene.h"
#include "Projectile.h"
#include "Renderer/Model.h"
#include "SpaceGame.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
void Player::update(float deltaTime){
    /*bonzai::Particle particle;
    particle.position = transform.position;
    particle.velocity = { bonzai::random::getReal(-600.0f, 600.0f),bonzai::random::getReal(-600.0f, 600.0f) };
	particle.color = { 1,1,0 };
    particle.lifespan = 0.20f;
	bonzai::getEngine().getParticlesSystem().addParticle(particle);*/
    if (starPowerActive) {
        
        powerupTimer += deltaTime;
        //I know it's bad, but it make the player look cool without seizure vibes
        starColorIndex++;
        if (starColorIndex % 512 == 128) {
            texture->color = { starColors[starColorIndex % 3] };

        }
        else if (starColorIndex % 512 == 1) {
            texture->color = { starColors[starColorIndex % 3] };

        }
        else if (starColorIndex % 512 == 258) {
            texture->color = { starColors[starColorIndex % 3] };


        }

        if (powerupTimer > 8) {
            starPowerActive = false;
            powerupTimer = 0;
            damping += 0.001f;
            texture->color = { starColors[0] };

        }
    }
    else if (tripleShotPowerActive) {
        powerupTimer += deltaTime;
        texture->color = { 0,1,1 };

        

        if (powerupTimer > 10) {
            tripleShotPowerActive = false;
            powerupTimer = 0;
            texture->color = { starColors[0] };

        }
    }else if (laserPowerActive) {
        powerupTimer += deltaTime;
        texture->color = { 1,0,1 };
       

        if (powerupTimer > 11) {
            laserPowerActive = false;
            powerupTimer = 0;
            texture->color = {starColors[0] };
        }
    }
    else if (healthPowerActive) {
        powerupTimer += deltaTime;
        texture->color = { 0,1,0 };
        if (powerupTimer > 10) {
            healthPowerActive = false;
            powerupTimer = 0;
            texture->color = { starColors[0] };
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
    this->velocity += velocity * deltaTime;

    transform.position.x=bonzai::math::wrap(transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
	transform.position.y = bonzai::math::wrap(transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());
    if (slowDown) {
        this->damping += 0.0005f;
    }
    Actor::update(deltaTime);
    if (slowDown) {
        this->damping -= 0.0005f;
    }
	shootTimer -= deltaTime;
	//Laser shot
    if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && laserPowerActive && shootTimer <= 0) {
        shootTimer = shootCooldown/5; // Reset the shoot timer

        
        bonzai::Transform transform{ this->transform.position,this->transform.rotation, 36 };//size
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, bonzai::resources().get<bonzai::Texture>("Textures/laser_shot.png", bonzai::getEngine().getRenderer()));

        
        projectile->hasParticles=false; // seconds
        projectile->lifespan = 3.0f; // seconds
        projectile->pierce=5; 
        projectile->speed = 0;;
        projectile->particleColor = this->texture->color;
        projectile->name = "laser"; // Set the name of the player actor
        projectile->tag = "Player"; // Set the name of the player actor

        scene->addActor(std::move(projectile));


    }else{
		//Normal shot
        if (bonzai::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && shootTimer <= 0) {
            shootTimer = shootCooldown; // Reset the shoot timer
            
            bonzai::res_t texture = bonzai::resources().get<bonzai::Texture>("Textures/Projectile.png", bonzai::getEngine().getRenderer());
            texture->color = bonzai::vec3{ 1.0f,1.0f,1.0f };
			//2 extra shots for triple shot powerup
            if (tripleShotPowerActive) {
                
                

                bonzai::Transform transform{ this->transform.position,this->transform.rotation - 30.0f, 2 };//size
                std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, texture);

                projectile->damping = 0.00f;
                projectile->speed = this->velocity.length() + 50.0f; // Set speed to a higher value for faster movement
                projectile->lifespan = 4.0f; // seconds
                projectile->particleColor = this->texture->color;
                projectile->name = "projectile"; // Set the name of the player actor
                projectile->tag = "Player"; // Set the name of the player actor
                scene->addActor(std::move(projectile));

                
                transform = { this->transform.position,this->transform.rotation + 30.0f, 2 };//size
                projectile = std::make_unique<Projectile>(transform, bonzai::resources().get<bonzai::Texture>("Textures/projectile.png", bonzai::getEngine().getRenderer()));
                projectile->damping = 0.00f;
                projectile->speed = this->velocity.length() + 50.0f; // Set speed to a higher value for faster movement
                projectile->lifespan = 4.0f; // seconds
                projectile->particleColor = this->texture->color;
                projectile->name = "projectile"; // Set the name of the player actor
                projectile->tag = "Player"; // Set the name of the player actor
                scene->addActor(std::move(projectile));

            }

           // std::shared_ptr<bonzai::Model> model = std::make_shared <bonzai::Model>(GameData::projectilePoints, bonzai::vec3{ 1.0f,1.0f,1.0f });
            bonzai::Transform transform{ this->transform.position,this->transform.rotation, 2 };//size
            std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, texture);


            projectile->damping = 0.00f;
            projectile->speed = this->velocity.length() + 50.0f; // Set speed to a higher value for faster movement
            projectile->lifespan = 4.0f; // seconds
            projectile->particleColor = this->texture->color;
            projectile->name = "projectile"; // Set the name of the player actor
            projectile->tag = "Player"; // Set the name of the player actor

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
            particle.color = this->texture->color;
            particle.lifespan = 1.0f;
            bonzai::getEngine().getParticlesSystem().addParticle(particle);


        }
    }
}
