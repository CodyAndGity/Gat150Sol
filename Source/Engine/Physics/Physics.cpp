#include "EnginePCH.h"
#include "Physics.h"
namespace bonzai {
#include "Physics.h"

	bool Physics::initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
		worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::shutdown() {
		b2DestroyWorld(worldId);
	}

	void Physics::update(float deltaTime) {
		b2World_Step(worldId, 1.0f / 60.0f, 4);
	}
	

}
