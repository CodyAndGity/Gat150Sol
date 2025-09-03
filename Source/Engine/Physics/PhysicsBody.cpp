#include "PhysicsBody.h"
#include "Physics.h"
namespace bonzai {
	PhysicsBody::PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const Physics& physics){
		b2BodyDef bodyDef = b2DefaultBodyDef();

		// set body definition
		bodyDef.type = (def.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = to_b2(Physics::pixelToWorld(transform.position));
		bodyDef.rotation = b2MakeRot(math::degToRad(transform.rotation));
		bodyDef.motionLocks.angularZ = def.constrainAngle;
		bodyDef.gravityScale = def.gravityScale;
		bodyDef.linearDamping = def.linearDamping;
		bodyDef.angularDamping = def.angularDamping;
		bodyDef.userData = def.actor;

		// create body
		bodyId = b2CreateBody(physics.worldId, &bodyDef);

		// set shape definition
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.material.friction = def.friction;
		shapeDef.material.restitution = def.restitution;
		shapeDef.density = def.density;
		shapeDef.isSensor = def.isSensor;

		if (def.isSensor)shapeDef.enableSensorEvents = true;
		else shapeDef.enableContactEvents = true;
		// create shape
		b2Vec2 hsize = to_b2(Physics::pixelToWorld(size * transform.scale * 0.5f));
		switch (def.shape)
		{
		case Shape::Box:
		{
			b2Polygon box = b2MakeBox(hsize.x, hsize.y);
			b2CreatePolygonShape(bodyId, &shapeDef, &box);
		}
		break;
		case Shape::Capsule:
		{
			b2Capsule capsule{ b2Vec2{ 0, hsize.y - hsize.x }, b2Vec2{ 0, -(hsize.y - hsize.x) }, hsize.x };
			b2CreateCapsuleShape(bodyId, &shapeDef, &capsule);
		}
		break;
		case Shape::Circle:
		{
			b2Circle circle{ b2Vec2{ 0, 0 }, hsize.x };
			b2CreateCircleShape(bodyId, &shapeDef, &circle);
		}
		break;
		default:
			break;
		}
	}
	PhysicsBody::~PhysicsBody(){

		b2DestroyBody(bodyId);
	}
	vec2 PhysicsBody::getPosition(){
		return Physics::worldToPixel(to_vec2(b2Body_GetPosition(bodyId)));
	}
	float PhysicsBody::getAngle(){
		return b2Rot_GetAngle(b2Body_GetRotation(bodyId));
	}
	void PhysicsBody::applyForce(const vec2& force){
		b2Body_ApplyForceToCenter(bodyId,to_b2(Physics::pixelToWorld( force)), true);
	}
	void PhysicsBody::applyTorque(const float radians){
		b2Body_ApplyTorque(bodyId, radians, true);

	}
	void PhysicsBody::setVelocity(const vec2& velocity)	{
		b2Body_SetLinearVelocity(bodyId, to_b2(Physics::pixelToWorld(velocity)));
	}
	vec2 PhysicsBody::getVelocity(){
		return Physics::worldToPixel(to_vec2(b2Body_GetLinearVelocity(bodyId)));
	}
}