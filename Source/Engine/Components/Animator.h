#pragma once
#include<map>
#include "Framework/Component.h"
#include "Renderer/TextureAnimation.h"
namespace bonzai {
	class Animator : public Component {
	public:
		struct TextureAnimInfo {
			std::string textureAnimationName;
			res_t<TextureAnimation> textureAnimation;
		};
		int frame = 0;
		float speedMultiplier{ 1 };
	public:
		CLASS_PROTOTYPE(Animator)
			void start() override;
		void update(float dt) override;
		void play(const std::string& name, bool resetFrame = true);
		void pause(bool pause) { paused = pause; }
		bool isPaused() const { return paused; }
		const std::string& getCurrentAnimationName() const { return currentAnimationName; }
		void read(const json::value_t& value) override;
	private:
		float frameTimer = 0;
		bool paused = false;
		std::string currentAnimationName;
		TextureAnimInfo currentAnimation;
		std::map<std::string, TextureAnimInfo> animations;
		class SpriteRenderer* spriteRenderer{ nullptr };
	};
}
