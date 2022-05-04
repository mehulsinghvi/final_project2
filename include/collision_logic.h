//
// Created by mehul on 08-03-2022.
//

#ifndef FINAL_PROJECT_COLLISION_LOGIC_H
#define FINAL_PROJECT_COLLISION_LOGIC_H

#include <vector>

#include "cinder/audio/Voice.h"
#include "paddle.h"
#include "pong_ball.h"

namespace finalproject {
class CollisionLogic {
 public:
  /**
   * This is the constructor for this class and takes in the corner vector
   * required to draw rectangle and also takes the length and breadth of
   * rectangle in vec2 form
   * @param corner is the vec required to draw rectangle
   * @param size of the rectangle
   */
  CollisionLogic(glm::vec2 corner, glm::vec2 size, Paddle paddle);

  /**
   * Default empty constructor
   */
  CollisionLogic();

  /**
   * This function updates the state of all elements on the board, including
   * balls and slider paddles
   */
  void UpdateState();

  /**
   * This function simply adds another new ball to the vector list
   * @param position of the atom being added
   * @param velocity of the atom being added
   */
  void AddNewBall(glm::vec2 position, glm::vec2 velocity);

  /**
   * This is the getter for the vector list with all the balls
   * @return the vector of all the balls
   */
  std::vector<Pong_Ball> GetAllBalls() const;

  /**
   * This is getter for the paddle
   * @return paddle
   */
  Paddle GetPaddle() const;

  /**
   * This sets the paddle when you want to replace the paddles
   */
  void SetPaddle(Paddle paddle);

  /**
   * Getters for scores for both players
   * @param type is to indicate which player
   * @return score of player
   */
  enum player { left, right };
  size_t GetScore(player type);

  /**
   * resets the game to start from the beginning
   */
  void RestartGame();

 private:
  std::vector<Pong_Ball> all_balls;
  // this is the corner of the rectangle needed for drawing rectangle and
  // finding out wall positions
  glm::vec2 corner_;
  // keeping track of box size for wall collisions
  glm::vec2 box_size_;
  // the radius of all balls
  float radius = 10;
  // keeps track of paddle, scores and sounds for collisions
  Paddle paddle_;
  size_t left_score_;
  size_t right_score_;
  cinder::audio::VoiceRef sound_wall_;
  cinder::audio::VoiceRef sound_pad_;

  /**
   * This helper functions return false if the collision is actually happening
   * and helps avoid infinite back and forth between two balls (due to small
   * velocity vecs) - aka sticky collisions
   * @param ball1
   * @param ball2
   * @param type is to figure out if the collision is between two balls or with
   * a wall/paddle
   * @param wall_vec is the position vector of wall boundary
   * @return true is collision is sticky, false otherwise
   */
  static bool IsStickyCollision(Pong_Ball& ball1, Pong_Ball& ball2, int type,
                                glm::vec2 wall_vec);

  /**
   * This function handles collisions with the wall and updates the velocity
   * @param atom to handles collision for
   */
  void WallCollisionsUpdate(Pong_Ball& ball);

  /**
   * This function handles collisions between two balls and updates the velocity
   * of both atoms
   * @param atom to handles collision for
   * @param second is the second atom involved in collision
   */
  void BallCollisionsUpdate(Pong_Ball& ball, Pong_Ball& second) const;

  /**
   * This function handles collisions between balls and paddles
   * @param ball
   */
  void PaddleCollisionUpdate(Pong_Ball& ball) const;
};
}  // namespace finalproject
#endif  // FINAL_PROJECT_COLLISION_LOGIC_H
