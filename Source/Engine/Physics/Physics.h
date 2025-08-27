#pragma once
#include <box2d/box2d.h>
#include <memory>
namespace bonzai {
	class Physics {
		inline b2Vec2 to_b2(const vec2& v) {
			return b2Vec2({v.x, v.y	});
		}
		inline vec2 to_vec2(const b2Vec2& v) {
			return vec2({ v.x, v.y });
		}
	public:
		Physics() = default;
		bool initialize();
		void shutdown();
		void update(float deltaTime);
		//vec2 worldToPixel(const vec);
	private:
		b2WorldId worldId;
	};
}



