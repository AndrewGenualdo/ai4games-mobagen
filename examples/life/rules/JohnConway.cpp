#include "JohnConway.h"

#include <iostream>
#include <bits/ostream.tcc>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  for (int y = 0; y < world.SideSize(); y++) {
    for (int x = 0; x < world.SideSize(); x++) {

      const int neighbors = CountNeighbors(world, Point2D(x, y));
      const bool wasAlive = world.Get(Point2D(x, y));
      const bool alive = wasAlive ? (neighbors == 2 || neighbors == 3) : neighbors == 3;
      world.SetNext(Point2D(x, y), alive);
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (x == 0 && y == 0) continue;
      count += world.Get(Point2D(point.x + x, point.y + y)) ? 1 : 0;
    }
  }
  return count;
}
