#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f force = Vector2f::zero();  // zero

  // todo: add here your code code here do make the boid follow the bounded box rule
  // hint: use this->world->engine->window->size() and desiredDistance

    //if (desiredDistance)
    // if (Vector2f::Distance())

  if (float const distToTop = Vector2f::Distance(boid->getPosition(), Vector2f(boid->getPosition().x, static_cast<float>(this->world->engine->window->size().y)));
    distToTop < static_cast<float>(desiredDistance)) { force += Vector2f(0, -distToTop / static_cast<float>(desiredDistance) * weight); }
  if (float const distToBottom = Vector2f::Distance(boid->getPosition(), Vector2f(boid->getPosition().x, 0));
    distToBottom < static_cast<float>(desiredDistance)) { force += Vector2f(0, distToBottom / static_cast<float>(desiredDistance) * weight); }
  if (float const distToLeft = Vector2f::Distance(boid->getPosition(), Vector2f(0, boid->getPosition().y));
    distToLeft < static_cast<float>(desiredDistance)) { force += Vector2f(distToLeft / static_cast<float>(desiredDistance) * weight, 0); }
  if (float const distToRight = Vector2f::Distance(boid->getPosition(), Vector2f(static_cast<float>(this->world->engine->window->size().x), boid->getPosition().y));
    distToRight < static_cast<float>(desiredDistance)) { force += Vector2f(-distToRight / static_cast<float>(desiredDistance) * weight, 0); }



  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}