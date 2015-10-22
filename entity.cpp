#include "entity.h"

Entity::Entity()
{

}

bool Entity::isCollidingWith(Entity &otherEntity) {
    return rect.intersects(otherEntity.getRect());
}
