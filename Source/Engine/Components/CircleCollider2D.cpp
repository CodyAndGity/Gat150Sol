#include "EnginePCH.h"
#include "CircleCollider2D.h"
namespace bonzai {
    FACTORY_REGISTER(CircleCollider2D)

    void CircleCollider2D::update(float deltaTime) {
        //
    }

    bool CircleCollider2D::checkCollision(ColliderComponent& other) {
        float distance = (owner->transform.position - other.owner->transform.position).length();

		//check circle to circle collision
		auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
        if (circleCollider) {
		    float radii = radius + circleCollider->radius;
            if( distance <= radii) {
                // Collision detected
                return true;
			}
        }
        //if (distance <= (actorA->getRadius() + actorB->getRadius())) {

        return false;
    }
    void CircleCollider2D::read(const json::value_t& value)    {
        Object::read(value);
        JSON_READ(value, radius);
		
    }
    

}
