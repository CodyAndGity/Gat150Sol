#pragma once
#include <fmod.hpp>
#include <string>
#include <map>
namespace bonzai {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool initialize();
		void shutdown();
		void update();

		bool addSound(const std::string& filename, const  std::string name = "");
		bool playSound(const std::string name );
		bool playSound(class AudioClip& );
	private:
		static bool checkFMODResult(FMOD_RESULT result);
	private:
		std::map<std::string, FMOD::Sound*> sounds;
		FMOD::System* system{ nullptr };
		friend class AudioClip;


	};



};