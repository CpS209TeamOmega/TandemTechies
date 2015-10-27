#include "level.h"
#include "entity.h"

int Entity::SIZE = 64;

bool Entity::isCollidingWith(Entity &otherEntity) {
    return rect.intersects(otherEntity.getRect());
}
