#pragma once
#include <box2d/box2d.h>
#include <memory>
namespace bonzai {
	inline b2Vec2 to_b2(const vec2& v) {
		return b2Vec2({v.x, v.y	});
	}
	inline vec2 to_vec2(const b2Vec2& v) {
		return vec2({ v.x, v.y });
	}
	class Physics {
	public:
		Physics() = default;
		bool initialize();
		void shutdown();
		void update(float deltaTime);

		static vec2 worldToPixel(const vec2& world) {
			return world * pixelsPerUnit;
		}
		static vec2 pixelToWorld(const vec2& pixel) {
			return pixel / pixelsPerUnit;
		}
		static void setPixelsPerUnit(float ppu) {
			pixelsPerUnit = ppu;
		}
		static float pixelsPerUnit;
	private:
		friend class PhysicsBody;

		b2WorldId worldId;
	};
}



