#pragma once
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Core/time.h"
#include "Core/Singleton.h"
#include "Resources/ResourceManager.h"
#include "Physics/Physics.h"
#include <memory>
namespace bonzai {
	
	class Engine :public Singleton<Engine>{
	public:
		bool initialize();
		void update();
		void shutdown();
		void draw();

		Renderer& getRenderer() { return *renderer; }
		AudioSystem& getAudio() { return *audio; }
		InputSystem& getInput() { return *input; }
		ParticleSystem& getParticlesSystem() { return *particles; }
		Time& getTime() { return time; }
		Physics& getPhysics() { return *physics; }
	private:
		friend class Singleton<Engine>;
		Engine() = default;
	private:
		bonzai::Time time;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<AudioSystem> audio;
		std::unique_ptr<InputSystem> input;
		std::unique_ptr<ParticleSystem> particles;
		std::unique_ptr<Physics> physics;

	};
	inline Engine& getEngine(){
		return Engine::getInstance();
	}
};