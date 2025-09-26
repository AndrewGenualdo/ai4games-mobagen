#include "Cat.h"
#include "World.h"
#include <stdexcept>


Point2D dirToPos(int dir, Point2D const &pos) {
  switch (dir) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}

Point2D Cat::Move(World* world) {
  auto pos = world->getCat();
  int rand = Random::Range(0, 5);
  Point2D p = dirToPos(rand, pos);

  if (!world->catCanMoveToPosition(p)) {
    for (int i = 0; i < 5; i++) {
      rand = (rand + 1) % 6;
      p = dirToPos(rand, pos);
      if (world->catCanMoveToPosition(p)) break;
      if (i == 4) return pos;
    }
  }


  return p;

}
