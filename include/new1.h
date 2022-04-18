#pragma once

#include "cinder/gl/gl.h"
#include "collision_logic.h"

using glm::vec2;

namespace finalproject {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * This is the constructor and takes in corner vector and size vector needed
   * to draw a rectangle
   */
  GasContainer(const glm::vec2& corner, const vec2& size);

  /**
   * This is the default empty constructor
   */
  GasContainer();

    /**
     * Displays the container walls and the current positions of the particles.
     */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:
  CollisionLogic logic_ ; // this is to use all the logic functions
  ci::Rectf box; // this is to draw rectangle
};

}  // namespace finalproject
