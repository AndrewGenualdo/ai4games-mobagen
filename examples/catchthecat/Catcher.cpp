#include "Catcher.h"
#include "World.h"

#include <algorithm>

//found at:
//https://www.redblobgames.com/grids/hexagons/#distances-cube
float hexDistance(const Point2D& a, const Point2D& b) {
  return (std::abs(a.x - b.x) + std::abs(a.x + a.y - b.x - b.y) + std::abs(a.y - b.y)) / 2.0;
}

void sortByDistance(std::vector<Point2D>& points, const Point2D& cat) {
  std::sort(points.begin(), points.end(),
      [&cat](const Point2D& a, const Point2D& b) {
          return hexDistance(a, cat) < hexDistance(b, cat);
      });
}

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  Point2D cat = world->getCat();
#define valid(p) p.x >= -side && p.x <= side && p.y >= -side && p.y <= side
#define filled(p) world->getContent(p) || p == cat
#define check(x, y) if (valid(Point2D(x, y)) && !filled(Point2D(x, y))) return Point2D(x, y)

  if (cat.x <= -side + 1) {
    check(-side, cat.y);
    check(-side, cat.y + 1);
    check(-side, cat.y - 1);
  }
  if (cat.x >= side - 1) {
    check(side, cat.y);
    check(side, cat.y + 1);
    check(side, cat.y - 1);
  }
  if (cat.y <= -side + 1) {
    check(cat.x, -side);
    check(cat.x + 1, -side);
  }
  if (cat.y >= side - 1) {
    check(cat.x, side);
    check(cat.x + 1, side);
  }

  check(-side + 1, -side);
  check(side - 1, -side);
  check(-side + 1, side);
  check(side - 1, side);

  std::vector<Point2D> walls;
  for(int y = -side; y <= side; y += 2) walls.push_back(Point2D(-side, y));
  for(int y = -side; y <= side; y += 2) walls.push_back(Point2D(side, y));
  for(int x = -side + 2; x <= side - 2; x += 2) walls.push_back(Point2D(x, -side));
  for(int x = -side + 2; x <= side - 2; x += 2) walls.push_back(Point2D(x, side));



  sortByDistance(walls, cat);

  for(int i = 0; i < walls.size(); i++) {
    check(walls[i].x, walls[i].y);
  }

  int rand = Random::Range(0, 5);
  for(int i = 0; i < 6; i++) {
    check(dirToPos(i + rand, cat).x, dirToPos(i + rand, cat).y);
  }
  return cat;
  /*for(int y = -side; y <= side; y+= 2) check(-side, y);
  for(int y = -side; y <= side; y+= 2) check(side, y);
  for(int x = -side; x <= )*/
  /*Point2D dims = Point2D(world->getWorldSideSize(), world->getWorldSideSize());
  Point2D p = Point2D(-side, -side);

  Point2D catReal = world->getCat();




  check(-side, side);
  check(side, -side);
  check(side, side);
  check(-side, side);
  check(side, -side + 1);



  if (cat.y > cat.x && cat.y < dims.y - cat.x) { //left triangle

    p.x = -side;
    p.y = catReal.y;
    if (catReal.x <= -side + 1 &&  !filled(p)) return p;
    p.y = catReal.y - 1;
    bool top = true;
    bool fill = false;
    while (filled(p) && valid(p)) {
      if (top) p.y += 2;
      else {
        p.y -= 2;
        p.x++;
      }
      top = !top;
      if(p.x - 1 > catReal.x) {
        fill = true;
        break;
      }
    }
    if(fill) {
      p.x = catReal.x + 1;
      p.y = catReal.y;
      while(filled(p)) {
        p.x--;
      }
    }
    return p;
    //if (!valid(p)) p.x = side;
  } else if (cat.y < cat.x && cat.y > dims.y - cat.x) { //right triangle

    p.x = side;
    p.y = catReal.y;
    if (catReal.x >= side - 1 && !filled(p)) return p;
    p.y = catReal.y + 1;
    bool top = false;
    bool fill = false;
    while (filled(p) && valid(p)) {
      if (top) p.y += 2;
      else {
        p.y -= 2;
        p.x--;
      }
      top = !top;
      if(p.x + 1 < catReal.x) {
        fill = true;
        break;
      }
    }
    if(fill) {
      p.x = catReal.x - 1;
      p.y = catReal.y;
      while(filled(p)) {
        p.x++;
      }
    }
    return p;
    //if (!valid(p)) p.x = -side;
  } else if (cat.y < side) {//top triangle

    p.y = -side;
    p.x = catReal.x;
    if (catReal.y <= -side + 1 && !filled(p)) return p;
    p.x = catReal.x - 1;
    bool left = true;
    bool fill = false;
    while (filled(p) && valid(p)) {
      if (left) p.x += 2;
      else {
        p.y++;
        p.x -= 2;
      }
      left = !left;
      if(p.y - 1 > catReal.y) {
        fill = true;
        break;
      }
    }
    if(fill) {
      p.x = catReal.x;
      p.y = catReal.y + 1;
      while(filled(p)) {
        p.y--;
      }
    }
    return p;
    //if (!valid(p)) p.y = side;
  } else { //bottom triangle

    p.y = side;
    p.x = catReal.x;
    if (catReal.y >= side - 1 && !filled(p)) return p;
    p.x = catReal.x - 1;
    bool left = true;
    bool fill = false;
    while (filled(p) && valid(p)) {
      if (left) p.x += 2;
      else {
        p.y--;
        p.x -= 2;
      }
      left = !left;
      if(p.y + 1 < catReal.y) {
        fill = true;
        break;
      }
    }
    if(fill) {
      p.x = catReal.x;
      p.y = catReal.y - 1;
      while(filled(p)) {
        p.y++;
      }
    }
    return p;
  }
  return p;*/
}