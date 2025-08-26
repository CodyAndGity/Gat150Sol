#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
namespace bonzai {

	bool Engine::initialize() {
		renderer = std::make_unique<bonzai::Renderer>();
		//initialize renderer and create window
		renderer->initialize();
		renderer->createWindow("Bonzai Engine", 1280, 1024, false);

		input = std::make_unique<bonzai::InputSystem>();
		input->initialize();

		audio = std::make_unique<bonzai::AudioSystem>();
		audio->initialize();

		particles = std::make_unique<bonzai::ParticleSystem>();
		particles->initialize(5000);
		return true;
	}
	void Engine::update() {
		time.tick();
		input->update();
		audio->update();
		particles->update(time.getDeltaTime());
	}
	void Engine::shutdown() {
		resources().clear();
		Factory::getInstance().removeAll();
		EventManager::getInstance().removeAll();
		particles->shutdown();
		audio->shutdown();
		input->shutdown();
		renderer->shutdown();
	}

	void Engine::draw(){
		
	}




}