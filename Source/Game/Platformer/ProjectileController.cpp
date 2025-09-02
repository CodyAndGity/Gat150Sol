#include "../GamePCH.h"
#include "ProjectileController.h"
FACTORY_REGISTER(ProjectileController)


void ProjectileController::update(float deltaTime) {





    bonzai::vec2 velocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(owner->transform.rotation)) * speed;

    if (body) {
        body->setVelocity(velocity);
    }


    //owner->transform.position.x = bonzai::math::wrap(owner->transform.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
    //owner->transform.position.y = bonzai::math::wrap(owner->transform.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());


    if (hasParticles) {
        float angle = owner->transform.rotation + bonzai::random::getReal(-30.0f, 30.0f);
        bonzai::vec2 particleVelocity = bonzai::vec2{ 1,0 }.rotate(bonzai::math::degToRad(angle));
        particleVelocity *= bonzai::random::getReal(80.0f, 150.0f) * -1;
        bonzai::Particle particle;
        particle.position = owner->transform.position;
        particle.velocity = particleVelocity;
        particle.color = particleColor;
        particle.lifespan = bonzai::random::getReal(0.3f, 0.6f);
        bonzai::getEngine().getParticlesSystem().addParticle(particle);
    }

}

void ProjectileController::onCollision(bonzai::Actor* other) {
    if (other->tag != owner->tag && other->tag != "Powerup") {
        pierce--;

    }
    if (pierce <= 0) {
        this->owner->destroyed = true;
    }
}

void ProjectileController::read(const bonzai::json::value_t& value) {
    Object::read(value);
    JSON_READ(value, speed);
    JSON_READ(value, pierce);
    JSON_READ(value, hasParticles);
    JSON_READ(value, particleColor);
}

void ProjectileController::start() {
    body = owner->getComponent<bonzai::RigidBody>();

}


