#include "Components/MeshRenderer.h"

namespace bonzai {

	void MeshRenderer::update(float deltaTime) {

	}
	void MeshRenderer::draw(class Renderer& renderer) {
		auto mesh = resources().get<Mesh>(meshName);
		if (mesh) {
			mesh->draw(renderer, owner->transform);
		}
	}

}