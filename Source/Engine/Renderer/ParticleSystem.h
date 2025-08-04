#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Renderer/Renderer.h"
#include <vector>
namespace bonzai {
	struct Particle {
		bool active{ false };
		float lifespan{ 1 };
		vec2 position{ 0,0 };
		vec2 velocity{ 0,0 };
		vec3 color{ 0,0 ,0};



	};
	class ParticleSystem {
	public:
		ParticleSystem() = default;
		bool initialize(int poolSize=1000);

		void draw(Renderer& renderer);
		void update(float deltaTime);
		void shutdown();

		void addParticle(const struct Particle& particle);

	private:
		Particle* getFreeParticle();
		
		
	private:
		std::vector<struct Particle> particles;
	};
}