#include "Cat.h"
#include "World.h"






struct Node {
  Point2D point;
  double priority;

  bool operator>(const Node& other) const {
    return priority > other.priority;
  }
};


static bool isOnEdge(const Point2D&p, const int side) {
  return p.x == -side || p.x == side || p.y == -side || p.y == side;
}

std::vector<Point2D> AStar(World* world, const Point2D& start) {
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

    if(isOnEdge(current, world->getWorldSideSize() / 2)) {
      goal = current;
      break;
    }

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

Point2D Cat::Move(World* world) {
  auto cat = world->getCat();

  std::vector<Point2D> path = AStar(world, cat);

  if(path.empty()) { //random walk if it can't move
    int rand = Random::Range(0, 5);
    Point2D p = dirToPos(rand, cat);

    if (!world->catCanMoveToPosition(p)) {
      for (int i = 0; i < 6; i++) {
        p = dirToPos(lastDir, cat);
        if (!world->catCanMoveToPosition(p)) {
          lastDir++;
          lastDir %= 6;
          p = dirToPos(lastDir, cat);
        } else {
          break;
        }

      }
      /*for (int i = 0; i < 5; i++) {
        rand = (rand + 1) % 6;
        p = dirToPos(rand, cat);
        if (world->catCanMoveToPosition(p)) break;
        if (i == 4) return cat;
      }*/
    }
    return p;
  }

  return path.back();





}
