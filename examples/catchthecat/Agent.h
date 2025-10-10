#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <queue>
#include <stdexcept>
#include <unordered_map>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);

  static Point2D dirToPos(int dir, Point2D const &pos);
  static std::vector<Point2D> neighbors(const Point2D& p);

  //found at:
  //https://www.redblobgames.com/grids/hexagons/#distances-cube
  static float heuristic(const Point2D& a, const Point2D& b) {
    return (std::abs(a.x - b.x) + std::abs(a.x + a.y - b.x - b.y) + std::abs(a.y - b.y)) / 2.0;
  }
};

#endif  // AGENT_H
