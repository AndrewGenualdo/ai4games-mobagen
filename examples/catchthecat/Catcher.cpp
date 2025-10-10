#include "Catcher.h"
#include "World.h"



struct Node {
  Point2D point;
  double priority;

  bool operator>(const Node& other) const {
    return priority > other.priority;
  }
};

std::vector<Point2D> AStar(World* world, const Point2D& start, std::vector<Point2D> walls) {
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
  frontier.push({start, 0.0});

  std::unordered_map<Point2D, Point2D> cameFrom;
  std::unordered_map<Point2D, float> costSoFar;

  cameFrom[start] = Point2D::INFINITE;
  costSoFar[start] = 0.0f;

  Point2D goal = Point2D::INFINITE;

  while(!frontier.empty()) {
    Point2D current = frontier.top().point;
    frontier.pop();

    /*if(std::find(walls.begin(), walls.end(), current) != walls.end()) {
      goal = current;
      break;
    }*/
    bool brek = false;
    int wallCounter = 0;
    for(int i = 0; i < walls.size(); i++) {
      if(world->getContent(walls[i])) {
        wallCounter++;
        continue;
      }
      if(walls[i].x == current.x && walls[i].y == current.y) {
        goal = current;
        brek = true;
        break;
      }
    }
    if(brek || wallCounter == walls.size()) break;

    for(auto& next : Agent::neighbors(current)) {

      if(world->getContent(next)) continue; // skip if its a wall

      const float newCost = costSoFar[current] + 1;
      if (!costSoFar.contains(next) || newCost < costSoFar[next]) {
        costSoFar[next] = newCost;
        const float priority = newCost + Agent::heuristic(goal, next);
        frontier.push({next, priority});
        cameFrom[next] = current;
      }
    }
  }

  std::vector<Point2D> path;
  if(goal != Point2D::INFINITE) {
    for(Point2D current = goal; current != Point2D::INFINITE && current != start; current = cameFrom.at(current)) {
      path.push_back(current);
    }
  }
  return path;
}

Point2D Catcher::Move(World* world) {
  const auto side = world->getWorldSideSize() / 2;
  Point2D cat = world->getCat();
#define valid(p) p.x >= -side && p.x <= side && p.y >= -side && p.y <= side
#define filled(p) world->getContent(p) || p == cat
#define check(x, y) if (valid(Point2D(x, y)) && !filled(Point2D(x, y))) return Point2D(x, y)

  //METHOD 3
  /*if (cat.y <= -side + 1) { //top
    check(cat.x, -side);
    check(cat.x + 1, -side);
  }
  if (cat.y >= side - 1) { //bottom
    check(cat.x, side);
    check(cat.x + 1, side);
  }

  std::vector<Point2D> walls;
  for(int x = -side / 2; x <= side / 2; x += 2) walls.push_back(Point2D(x, -side));
  for(int x = -side / 2; x <= side / 2; x += 2) walls.push_back(Point2D(x, side));
  int dx = -side;
  int dy = 0;
  for(int i = 0; i < side / 2; i++) {
    walls.push_back(Point2D(dx, -dy));
    walls.push_back(Point2D(-dx, -dy));
    if(dy != 0) {
      walls.push_back(Point2D(dx, dy));
      walls.push_back(Point2D(-dx, dy));
    }
    dx++;
    dy += 2;
  }

  std::vector<Point2D> holes;
  for(int x = -side / 2 + 1; x <= side / 2 - 1; x += 2) holes.push_back(Point2D(x, -side));
  for(int x = -side / 2 + 1; x <= side / 2 - 1; x += 2) holes.push_back(Point2D(x, side));
  dx = -side;
  dy = 1;
  for(int i = 0; i < side / 2; i++) {
    holes.push_back(Point2D(dx, -dy));
    holes.push_back(Point2D(-dx - 1, -dy));
    holes.push_back(Point2D(dx, dy));
    holes.push_back(Point2D(-dx - 1, dy));
    dx++;
    dy += 2;
  }

  sortByDistance(walls, cat);

  sortByDistance(holes, cat);

  const std::vector<Point2D> catNeighbors = neighbors(cat);
  for(int i = 0; i < holes.size(); i++) {
    for(int j = 0; j < catNeighbors.size(); j++) {
      if(holes[i].x == catNeighbors[j].x && holes[i].y == catNeighbors[j].y) check(holes[i].x, holes[i].y);
    }
  }

  for(int i = 0; i < walls.size(); i++) {
    check(walls[i].x, walls[i].y);
  }



  const int rand = Random::Range(0, 5);
  for(int i = 0; i < 6; i++) {
    check(dirToPos(i + rand, cat).x, dirToPos(i + rand, cat).y);
  }*/

  //METHOD 2

  if (cat.x <= -side + 1) { //left
    check(-side, cat.y);
    if(cat.y != side - 1) check(-side, cat.y + 1);
    if(cat.y != -side + 1) check(-side, cat.y - 1);
  }
  if (cat.x >= side - 1) { //right
    check(side, cat.y);
    check(side, cat.y + 1);
    check(side, cat.y - 1);
  }
  if (cat.y <= -side + 1) { //top
    check(cat.x, -side);
    check(cat.x + 1, -side);
  }
  if (cat.y >= side - 1) { //bottom
    check(cat.x, side);
    check(cat.x + 1, side);
  }

  //check(-side + 1, -side);
  //check(side - 1, -side);
  //check(-side + 1, side);
  //check(side - 1, side);

  std::vector<Point2D> walls;
  for(int y = -side + 1; y <= side; y += 2) walls.push_back(Point2D(-side, y));
  for(int y = -side; y <= side; y += 2) walls.push_back(Point2D(side, y));
  for(int x = -side + 1; x <= side - 1; x += 2) walls.push_back(Point2D(x, -side));
  for(int x = -side + 1; x <= side - 1; x += 2) walls.push_back(Point2D(x, side));



  // sortByDistance(walls, cat);
  const std::vector<Point2D> closestWall = AStar(world, cat, walls);
  if(!closestWall.empty()) check(closestWall.front().x, closestWall.front().y);

  const int rand = Random::Range(0, 5);
  for(int i = 0; i < 6; i++) {
    check(dirToPos(i + rand, cat).x, dirToPos(i + rand, cat).y);
  }
  return cat;




  //METHOD 1
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
  return cat;
}