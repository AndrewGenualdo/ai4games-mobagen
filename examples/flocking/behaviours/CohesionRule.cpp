#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  for (Boid* i : neighborhood) {
    cohesionForce += i->getPosition();
  }

  return neighborhood.size() == 0 ? Vector2f::zero() : ((cohesionForce / neighborhood.size()) - boid->getPosition()).normalized() * weight;
}