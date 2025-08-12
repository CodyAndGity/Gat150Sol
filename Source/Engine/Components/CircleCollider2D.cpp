#include "EnginePCH.h"
#include "CircleCollider2D.h"
namespace bonzai {
    void CircleCollider2D::update(float deltatime) {
        //
    }

    bool CircleCollider2D::checkCollision(ColliderComponent& other) {
        float distance = (owner->transform.position - other.owner->transform.position).length();

		//check circle to circle collision
		auto cirleCollider = dynamic_cast<CircleCollider2D*>(&other);
        if (cirleCollider) {
		    float radii = radius + cirleCollider->radius;
            if( distance <= radii) {
                // Collision detected
                return true;
			}
        }
        //if (distance <= (actorA->getRadius() + actorB->getRadius())) {

        return false;
    }
}
