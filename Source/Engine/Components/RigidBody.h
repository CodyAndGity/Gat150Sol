#pragma once
#include "Framework/Component.h"


namespace bonzai {
	class RigidBody : public Component {
	public:
		vec2 velocity{ 0,0 };
		float damping{ 0.0f }; 
	public:
		void update(float deltaTime) override;
		void read(const json::value_t& value) override;

	};
}