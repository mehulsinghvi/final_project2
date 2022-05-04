//
// Created by mehul on 08-03-2022.
//

#include "pong_ball.h"

#include <glm/geometric.hpp>
namespace finalproject {

Pong_Ball::Pong_Ball(glm::vec2 &position, glm::vec2 &velocity)
    : position_(position), velocity_(velocity) {
}

glm::vec2 Pong_Ball::GetPosition() {
  return position_;
}

glm::vec2 Pong_Ball::GetVelocity() {
  return velocity_;
}

void Pong_Ball::SetPosition(glm::vec2 &position) {
  position_ = position;
}

void Pong_Ball::SetVelocity(glm::vec2 &velocity) {
  velocity_ = velocity;
}

void Pong_Ball::UpdateAfterCollision(Pong_Ball &second_ball, int type) {
  if (type == 0) {  // collision with another atom
    glm::vec2 second_velocity = second_ball.velocity_;
    glm::vec2 second_pos = second_ball.position_;
    glm::vec2 velocity_difference = velocity_ - second_velocity;
    glm::vec2 position_difference = position_ - second_pos;
    float numerator = glm::dot(velocity_difference, position_difference);
    float denominator = pow(glm::length(position_difference), 2);
    velocity_ = velocity_ - ((numerator / denominator) * position_difference);
  } else if (type == 1) {  // collision with side walls - x
    velocity_.x *= -1;
  } else if (type == 2) {  // collision with top walls - y
    velocity_.y *= -1;
  }
}
}  // namespace finalproject
