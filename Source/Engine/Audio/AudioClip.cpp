#include "EnginePCH.h"
#include "AudioClip.h"
#include "Audio/AudioSystem.h"
namespace bonzai{
    AudioClip::~AudioClip()   {
        if (sound) {
            sound->release();
        }
    }
    bool bonzai::AudioClip::load(const std::string& filename, AudioSystem& audioSystem) {

        FMOD_RESULT result = audioSystem.system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
        if (!AudioSystem::checkFMODResult(result)) return false;

        return false;
    }
}
