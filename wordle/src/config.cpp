#include "config.h"

int equalCoordinates(const Coordinate *c1, const Coordinate *c2){
    return c1->x == c2->x && c1->y == c2->y ? 1 : 0;
}