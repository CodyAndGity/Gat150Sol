#include "AudioSystem.h"
#include <fmod_errors.h>
#include <iostream>
#include <string>
#include "../Core/StringHelper.h"
namespace bonzai {

	/// <summary>
	/// Adds a sound to the audio system using the specified filename and an optional name.
	/// </summary>
	/// <param name="filename">The path to the sound file to be added.</param>
	/// <param name="name">An optional name to identify the sound. If not provided or empty, the filename is used as the key.</param>
	/// <returns>True if the sound was successfully added; false if a sound with the same name already exists or if sound creation fails.</returns>
	bool AudioSystem::addSound(const std::string& filename, const  std::string name ) {
		std::string key = (name.empty()) ? filename : name;
		//convert to lowercase
		key = bonzai::toLower(key);
		//check if key already exists in map
		if (sounds.find(key) != sounds.end()) {
			std::cerr << "Sound with name '" << key << "' already exists!" << std::endl;
			return false;
		}
		FMOD::Sound* sound = nullptr;

		//create sounds from key
		FMOD_RESULT result= system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!checkFMODResult(result)) return false;
		sounds[key] = sound;

		////insert sounds into map
		return true;
	}
	bool AudioSystem::playSound(const std::string name){
		std::string key = name;

		//convert to lowercase
		key = bonzai::toLower(key);

		//check if sound with name exists in map
		if(sounds.find(key) ==sounds.end()){
			std::cerr << "Sound with name '" << key << "' not found!" << std::endl;
			return false;
		}
		FMOD_RESULT result = system->playSound(sounds[key], 0, false, nullptr);
		if (!checkFMODResult(result)) return false;

		return true;
	}
	/// <summary>
	/// Checks if an FMOD operation was successful and logs an error message if it was not.
	/// </summary>
	/// <param name="result">The FMOD_RESULT value returned by an FMOD function call.</param>
	/// <returns>True if the result indicates success (FMOD_OK); false otherwise, after logging the error.</returns>
	bool AudioSystem::checkFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		return true;
	}

	/// <summary>
	/// Initializes the audio system using FMOD.
	/// </summary>
	/// <returns>True if the audio system was successfully initialized; false otherwise.</returns>
	bool AudioSystem::initialize() {
		FMOD_RESULT result=FMOD::System_Create(&system); 
		if (!checkFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!checkFMODResult(result)) return false;

		return true;

	}

	void AudioSystem::shutdown() {
		checkFMODResult(system->release());
	}

	void AudioSystem::update() {
		checkFMODResult(system->update());

	}

}