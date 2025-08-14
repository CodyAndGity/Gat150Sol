#pragma once
#include "Framework/Component.h"
namespace bonzai {
	class AudioSource : public Component {
	public:
		std::string audioClipName;
	public:


		// Inherited via Component
		void update(float deltaTime) override;

		void play();

	};
}