#include "Components/MeshRenderer.h"

namespace bonzai {
	FACTORY_REGISTER(MeshRenderer)

	void MeshRenderer::update(float deltaTime) {

	}
	void MeshRenderer::draw(class Renderer& renderer) {
		auto mesh = resources().get<Mesh>(meshName);
		if (mesh) {
			mesh->draw(renderer, owner->transform);
		}
	}
	void MeshRenderer::read(const json::value_t& value) {
		Object::read(value);
		JSON_READ(value, meshName);

	}

}