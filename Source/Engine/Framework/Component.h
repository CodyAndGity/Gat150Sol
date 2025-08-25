#pragma once
#include "Framework/Object.h"
namespace bonzai {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr }; // Pointer to the actor that owns this component
	public:
		Component() = default;
		virtual void start() {}
		virtual void destroy() {}

		virtual void update(float deltaTime)=0;
	};
}