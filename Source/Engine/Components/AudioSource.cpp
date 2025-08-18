#include "EnginePCH.h"
#include "AudioSource.h"
#include "Audio/AudioClip.h"
#include "Engine.h"

namespace bonzai {
	FACTORY_REGISTER(AudioSource)

	void AudioSource::update(float deltaTime) {
		//

	}
	void AudioSource::play(){
		auto audioClip = resources().get<AudioClip>(audioClipName, bonzai::getEngine().getAudio());
		if (audioClip) {
			bonzai::getEngine().getAudio().playSound(*audioClip);
		}
	}
}