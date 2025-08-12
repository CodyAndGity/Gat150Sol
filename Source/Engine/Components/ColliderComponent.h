#pragma once
#include "Framework/Component.h"

namespace bonzai {
	class ColliderComponent : public Component {
	public:
		virtual bool checkCollision(ColliderComponent& other)=0;

	};
}