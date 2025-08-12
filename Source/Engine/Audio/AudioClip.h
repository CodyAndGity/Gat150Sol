#pragma once
#include "Resources/Resource.h"
namespace bonzai  {
	class AudioClip:public Resource {
	public:
		AudioClip() = default;
		~AudioClip();
		bool load(const std::string& filename, class AudioSystem& audioSystem);


	private:
		FMOD::Sound* sound{ nullptr };
		friend class AudioSystem;


	};
}