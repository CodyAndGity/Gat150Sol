#include "ParticleSystem.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Renderer/Renderer.h"
#include "../Engine.h"
namespace bonzai{

    

    bool ParticleSystem::initialize(int poolSize){
		particles.resize(poolSize); // Preallocate space for 1000 particles
        return false;
    }
    void ParticleSystem::draw( Renderer& renderer){
        for (auto& particle : particles) {
            if (particle.active) {
				renderer.setColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.drawPoint(particle.position.x, particle.position.y);
            }
        }
	}
    void ParticleSystem::update(float deltaTime){
        for (auto& particle : particles) {
            if (particle.active) {
				particle.lifespan -= deltaTime;
				particle.active = particle.lifespan > 0;
				particle.position += particle.velocity * deltaTime;
                particle.position.x = bonzai::math::wrap(particle.position.x, 0.0f, (float)bonzai::getEngine().getRenderer().getWidth());
                particle.position.y = bonzai::math::wrap(particle.position.y, 0.0f, (float)bonzai::getEngine().getRenderer().getHeight());

            }
        }
        
    }
    void ParticleSystem::shutdown(){
		particles.clear();

	}

    void ParticleSystem::addParticle(const Particle& particle)  {
        Particle* p = getFreeParticle();
        if (p) {
            *p = particle;
            p->active = true;
		}

    }

    Particle* ParticleSystem::getFreeParticle()  {
        for(auto& particle : particles) {
            if (!particle.active) {
                return &particle;
            }
		}
        return nullptr;
    }


}