#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  /*for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }*/
  Point2D p = Point2D(-side, -side);
  int dir = 0;
  constexpr int SOUTH = 0;
  int southOff = 0;
  constexpr int EAST = 1;
  int eastOff = 0;
  constexpr int NORTH = 2;
  int northOff = 0;
  constexpr int WEST = 3;
  int westOff = 0;
  while (world->getContent(p) || world->getCat() == p) {
    /*p.y ++;
    if (p.y > side) {
      p.y = -side;
      p.x = -p.x;
      if (p.x < 0) p.x++;
    }*/
    switch (dir) {
      case SOUTH: {
        //southOff == 0 ? p.y += 2 : p.y++;
        p.y += 2;
        if (p.y >= side - southOff) {
          dir = (dir + 1) % 4;
          p.x++;
          if (world->getContent(p)) {
            //p.y--;
            southOff++;
          }
        }
        break;
      }
      case EAST: {
        //eastOff == 0 ? p.x += 2 : p.x++;
        p.x += 2;
        if (p.x >= side - eastOff) {
          dir = (dir + 1) % 4;
          p.x-=2;
        if (world->getContent(p)) {

          eastOff++;
        }
        }
        break;
      }
      case NORTH: {
        //northOff == 0 ? p.y -= 2 : p.y--;
        p.y -= 2;
        if (p.y <= -side + northOff + 1) {
          dir = (dir + 1) % 4;
          if (world->getContent(p)) {
            //p.y++;
            northOff++;
          }
        }
        break;
      }
      case WEST: {
        //westOff == 0 ? p.x -= 2 : p.x--;
        p.x -= 2;
        if (p.x <= -side + westOff + 1) {
          dir = (dir + 1) % 4;
          p.y++;
          if (world->getContent(p)) {
            p.x++;
            westOff++;
          }
        }
        break;
      }
    }
  }
  return p;
}