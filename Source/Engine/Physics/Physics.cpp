#include "EnginePCH.h"
#include "Physics.h"
namespace bonzai {
#include "Physics.h"
	float Physics::pixelsPerUnit = 48.0f;
	bool Physics::initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::shutdown() {
		b2DestroyWorld(worldId);
	}

	void Physics::update(float deltaTime) {
		b2World_Step(worldId, 1.0f / 60.0f, 4);
		processCollisionEvents();
	}

	void Physics::processCollisionEvents(){
		b2ContactEvents contactEvents = b2World_GetContactEvents(worldId);

		//begin contact
		for (int i = 0; i < contactEvents.beginCount; i++) {
			b2ContactBeginTouchEvent* contactEvent = contactEvents.beginEvents + i;
			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA= (Actor*) b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) {
				continue;
			}
			Actor* actorB= (Actor*) b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) {
				continue;
			}
			actorA->onCollision(actorB);
			actorB->onCollision(actorA);

		}

		//end contact
		for (int i = 0; i < contactEvents.endCount; i++) {
			b2ContactEndTouchEvent* contactEvent = contactEvents.endEvents + i;
			if (!b2Shape_IsValid(contactEvent->shapeIdA) || !b2Shape_IsValid(contactEvent->shapeIdB)) continue;
			
			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA= (Actor*) b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) {
				continue;
			}
			Actor* actorB= (Actor*) b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) {
				continue;
			}
			actorA->onCollision(actorB);
			actorB->onCollision(actorA);

		}
		
		//sensor contact
		b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId);
		for (int i = 0; i < sensorEvents.beginCount; i++) {
			b2SensorBeginTouchEvent* sensorEvent = sensorEvents.beginEvents + i;
			if (!b2Shape_IsValid(sensorEvent->sensorShapeId) || !b2Shape_IsValid(sensorEvent->visitorShapeId)) continue;
			b2BodyId bodyA = b2Shape_GetBody(sensorEvent->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(sensorEvent->visitorShapeId);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) {
				continue;
			}
			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) {
				continue;
			}
			actorA->onCollision(actorB);
			actorB->onCollision(actorA);

		}
	}
	

}
