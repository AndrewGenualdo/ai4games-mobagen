#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }
  // FORMULA: 1 / x
  //separatingForce = Vector2f::normalized(separatingForce);
  for (Boid* i : neighborhood) {
    if (i == boid) { continue; }
    float dist = Vector2f::Distance(i->getPosition(), boid->getPosition());
    if (dist == 0) continue;
    if (dist < desiredMinimalDistance) {
      separatingForce += (boid->getPosition() - i->getPosition()) / dist;
    }
  }

  return separatingForce * weight;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
