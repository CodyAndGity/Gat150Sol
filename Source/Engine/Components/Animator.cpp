#include "Animator.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/TextureAnimation.h"
#include "Engine.h"
#include "Core/StringHelper.h"
namespace bonzai {
	FACTORY_REGISTER(Animator)
		void Animator::start() {
		// cache off sprite renderer component, using sprite renderer to draw
		spriteRenderer = owner->getComponent<SpriteRenderer>();
		if (!spriteRenderer) {
			Logger::Error("Animator missing sprite renderer.");
		}
		// get texture animations from texture animation names
		for (auto& animation : animations) {
			animation.second.textureAnimation = resources().get<TextureAnimation>(animation.second.textureAnimationName,
				getEngine().getRenderer());
			if (!animation.second.textureAnimation) {
				Logger::Warning("Could not load Animator texture animation {}", animation.second.textureAnimationName);
			}
			else {
				//Logger::Info("Animator animation {}, texture {} loaded", animation.first, animation.second.textureAnimationName);
			}
		}
		// set initial animation, use first map entry
		auto it = animations.begin();
		std::string name = it->first;
		play(name);
	}
	void Animator::update(float dt) {
		if (paused || !currentAnimation.textureAnimation) return;
		// update frame timer
		frameTimer -= dt * speedMultiplier;
		if (frameTimer <= 0) {
			frameTimer = 1.0f / currentAnimation.textureAnimation->getFPS();
			frame++;
			// check if animation is complete, loop or stop on last frame
			if (frame >= currentAnimation.textureAnimation->getTotalFrames()) {
				if (currentAnimation.textureAnimation->isLooping()) {
					frame = 0;
				}
				else {
					frame = currentAnimation.textureAnimation -> getTotalFrames() - 1;
				}
			}
			// set texture rect from animation
			if (spriteRenderer) {
				spriteRenderer->textureRect = currentAnimation.textureAnimation -> getFrameRect(frame);
			}
		}
	}
	void Animator::play(const std::string& name, bool resetFrame) {
		// don't start animation if already current
		if (equalsIgnoreCase(name, currentAnimationName)) return;
		// check animation exists
		auto it = animations.find( toLower(name));
		if (it == animations.end()) {
			Logger::Error("Animation does not exist in animation {}", name);
			return;
		}
		// set the current animation
		currentAnimationName = name;
		currentAnimation = it->second;
		if (resetFrame) frame = 0;
		frameTimer = 1.0f / currentAnimation.textureAnimation->getFPS();
		// set sprite renderer texture
		if (spriteRenderer) {
			spriteRenderer->texture = currentAnimation.textureAnimation->GetTexture();
			spriteRenderer->textureRect = currentAnimation.textureAnimation -> getFrameRect(frame);
		}
	}
	void Animator::read(const json::value_t& value) {
		Object::read(value);
		JSON_READ(value, frame);
		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
			for (auto& animatorValue : JSON_GET(value, animations).GetArray()) {
				std::string name;
				std::string textureAnimationName;
				JSON_READ(animatorValue, name);
				JSON_READ_NAME(animatorValue, "texture_animation", textureAnimationName);
				TextureAnimInfo textureAnimInfo;
				textureAnimInfo.textureAnimationName = textureAnimationName;
				animations[toLower(name)] = textureAnimInfo;
			}
		}
	}
}