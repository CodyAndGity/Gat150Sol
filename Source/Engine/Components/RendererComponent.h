#pragma once
#include "Framework/Component.h"

namespace bonzai {
	class RendererComponent : public Component {
	public:
		virtual void draw(class Renderer& renderer) = 0;

	};
}