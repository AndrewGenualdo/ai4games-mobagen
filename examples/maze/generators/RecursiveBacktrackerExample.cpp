#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

  //backtrack = pop something from stack
  if (stack.empty()) {
    Point2D start = randomStartPoint(w);
    if (start != Point2D(INT_MAX, INT_MAX)) {
      stack.push_back(start);
      visited[start.y][start.x] = true;
      w->SetNodeColor(start, Color32(0, 255, 0, 255));
      return true;
    }
    return false;
  }
  std::vector<Point2D> visitables = getVisitables(w, stack.back());
  if (visitables.size() == 0) {
    w->SetNodeColor(stack.back(), Color32(0, 0, 0, 255));
    stack.pop_back();
    return true;
  }
  Point2D newPoint = visitables.size() == 1 ? visitables.back() : visitables[rand() % visitables.size()];
  Point2D diff = newPoint - stack.back();
  stack.push_back(newPoint);
  visited[newPoint.y][newPoint.x] = true;
  w->SetNodeColor(newPoint, Color32(0, 0, 255, 255));
  if (diff == Point2D(0, 1)) w->SetNorth(newPoint, false);
  else if (diff == Point2D(0, -1)) w->SetSouth(newPoint, false);
  else if (diff == Point2D(-1, 0)) w->SetEast(newPoint, false);
  else if (diff == Point2D(1, 0)) w->SetWest(newPoint, false);

  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  if (p.y + 1 <=  sideOver2 && !visited[p.y+1][p.x]) visitables.push_back(Point2D(p.x, p.y+1));
  if (p.x + 1 <=  sideOver2 && !visited[p.y][p.x+1]) visitables.push_back(Point2D(p.x+1, p.y));
  if (p.y - 1 >= -sideOver2 && !visited[p.y-1][p.x]) visitables.push_back(Point2D(p.x, p.y-1));
  if (p.x - 1 >= -sideOver2 && !visited[p.y][p.x-1]) visitables.push_back(Point2D(p.x-1, p.y));


  return visitables;
}
