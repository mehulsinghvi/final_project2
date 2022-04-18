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
    Paddle(glm::vec2 &position, glm::vec2 &velocity, glm::vec2 &size, glm::vec2 &distance);

    void DrewPaddles();

    glm::vec2 GetPosition();

    /**
     * This the getter for velocity vector of an atom
     * @return the velocity vector
     */
    glm::vec2 GetVelocity();

    /**
     * This is the setter for position of an atom
     * @param position
     */
    void SetPosition(glm::vec2 &position);

    /**
     * This is the setter for velocity of an atom
     * @param position
     */
    void SetVelocity(glm::vec2 &velocity);

    void SlideRightPaddle(int type);
    void SlideLeftPaddle(int type);

    bool CheckCollisionWithPaddle(Pong_Ball &ball) const;

    const float KRadius = 10;

private:
    glm::vec2 position_;
    glm::vec2 velocity_;
    glm::vec2 size_;
    glm::vec2 distance_;

    glm::vec2 position2_;
    glm::vec2 velocity2_;
};
}



#endif //FINAL_PROJECT_PADDLE_H
