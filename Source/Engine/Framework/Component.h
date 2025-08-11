#pragma once
#include "Framework/Object.h"
namespace bonzai {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr }; // Pointer to the actor that owns this component
	public:
		Component() = default;
		virtual void update(float deltatime)=0;
	};
}