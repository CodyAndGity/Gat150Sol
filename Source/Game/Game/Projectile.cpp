#include "Projectile.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Core/Random.h"

void Projectile::update(float deltaTime) {


    


    
    bonzai::vec2 velocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(transform.rotation)) * speed;
	this->velocity += velocity.normalized() ;

    transform.position.x = bonzai::math::wrap(transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
    transform.position.y = bonzai::math::wrap(transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());
    
    Actor::update(deltaTime);
    if (hasParticles) {
        float angle = transform.rotation + bonzai::random::getReal(-30.0f, 30.0f);
        bonzai::vec2 particleVelocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(angle));
        particleVelocity *= bonzai::random::getReal(80.0f, 150.0f) * -1;
        bonzai::Particle particle;
        particle.position = transform.position;
        particle.velocity = particleVelocity;
        particle.color = particleColor;
        particle.lifespan = bonzai::random::getReal(0.3f, 0.6f);
        bonzai::getEngine().getParticlesSystem().addParticle(particle);
    }
}

void Projectile::onCollision(Actor* other){
    if (other->tag !=tag && other->tag!="Powerup") {
        pierce--;
        
	}
    if (pierce <= 0) {
        this->destroyed = true;
    }
}
