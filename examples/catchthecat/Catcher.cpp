#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  /*for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }*/
  int dir = 0;
  constexpr int SOUTH = 0;
  constexpr int EAST = 1;
  constexpr int NORTH = 2;
  constexpr int WEST = 3;
  int southOff = 0;
  int eastOff = 0;
  int northOff = 0;
  int westOff = 0;
  Point2D dims = Point2D(world->getWorldSideSize(), world->getWorldSideSize());
  Point2D p = Point2D(-side, -side);
  Point2D cat = world->getCat() + Point2D(side, side);
  Point2D catReal = world->getCat();
  #define filled(x) world->getContent(x) || x == cat
  /*if (filled(p)) {
    p = Point2D(side, -side);
  }
  if (filled(p))*/
  if (!filled(Point2D(-side, -side))) return Point2D(-side, -side);
  if (!filled(Point2D(side, -side))) return Point2D(side, -side);
  if (!filled(Point2D(side, side))) return Point2D(side, side);
  if (!filled(Point2D(-side, side))) return Point2D(-side, side);



  if (cat.y > cat.x && cat.y < dims.y - cat.x) { //left triangle
    std::cout << "left";
    bool top = true;
    p.x = -side;
    p.y = catReal.y - 1;
    while (filled(p)) {
      if (top) p.y += 2;
      else {
        p.y -= 2;
        p.x++;
      }
      top = !top;
    }
  } else if (cat.y < cat.x && cat.y > dims.y - cat.x) { //right triangle
    std::cout << "right";
    bool top = true;
    p.x = side;
    p.y = catReal.y - 1;
    while (filled(p)) {
      if (top) p.y += 2;
      else {
        p.y -= 2;
        p.x--;
      }
      top = !top;
    }
  } else if (cat.y < side) {//top triangle
    std::cout << "top";
    bool left = true;
    p.x = catReal.x - 1;
    p.y = -side;
    while (filled(p)) {
      if (left) p.x += 2;
      else {
        p.y++;
        p.x -= 2;
      }
      left = !left;
    }
  } else { //bottom triangle
    std::cout << "bottom";
    bool left = true;
    p.x = catReal.x - 1;
    p.y = side;
    while (filled(p)) {
      if (left) p.x += 2;
      else {
        p.y--;
        p.x -= 2;
      }
      left = !left;
    }
  }
  std::cout << ": " << p.x << " " << p.y << std::endl;
  /*int dir = 0;
  constexpr int SOUTH = 0;
  int southOff = 0;
  constexpr int EAST = 1;
  int eastOff = 0;
  constexpr int NORTH = 2;
  int northOff = 0;
  constexpr int WEST = 3;
  int westOff = 0;
  while (world->getContent(p) || world->getCat() == p) {
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
  }*/
  return p;
}