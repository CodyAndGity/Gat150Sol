#pragma once
#include "Framework/Component.h"
namespace bonzai {
	class AudioSource : public Component {
	public:
		std::string audioClipName;
	public:
		CLASS_PROTOTYPE(AudioSource)


		// Inherited via Component
		void update(float deltaTime) override;

		void play();

	};
}