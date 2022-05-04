//
// Created by mehul on 18-04-2022.
//

#ifndef FINAL_PROJECT_PADDLE_H
#define FINAL_PROJECT_PADDLE_H

#include <glm/detail/type_vec2.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "pong_ball.h"

namespace finalproject {

class Paddle {
 public:
  Paddle(glm::vec2 corner, glm::vec2 &position, glm::vec2 &velocity,
         glm::vec2 &size, glm::vec2 &distance, float radius);

  Paddle();

  /**
   * Draws the paddles on both sides on a "slider"
   */
  void DrawPaddles();

  glm::vec2 GetPosition();

  /**
   * This the getter for velocity vector of a ball
   * @return the velocity vector
   */
  glm::vec2 GetVelocity();

  /**
   * This is the setter for position of a ball
   * @param position
   */
  void SetPosition(glm::vec2 &position);

  /**
   * This is the setter for velocity of a ball
   * @param position
   */
  void SetVelocity(glm::vec2 &velocity);

  /**
   * Sliders -vertical to be controlled by the keys for both the players
   * @param type
   */
  void SlideRightPaddle(int type);
  void SlideLeftPaddle(int type);

  /**
   * Checks collisions with paddle on a slider and returns true for yes
   * @param ball
   * @return
   */
  bool CheckCollisionWithPaddle(Pong_Ball &ball) const;

 private:
  // position and velocity of vectors of both paddles
  glm::vec2 position_;
  glm::vec2 velocity_;
  glm::vec2 size_;
  glm::vec2 distance_;
  float radius_;
  glm::vec2 position2_;
  glm::vec2 velocity2_;
  glm::vec2 corner_;
};
}  // namespace finalproject

#endif  // FINAL_PROJECT_PADDLE_H
