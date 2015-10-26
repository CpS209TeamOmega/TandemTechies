#include "entity.h"

int Entity::SIZE = 32;

bool Entity::isCollidingWith(Entity &otherEntity) {
    return rect.intersects(otherEntity.getRect());
}
