//
// Created by mehul on 08-03-2022.
//

#ifndef FINAL_PROJECT_PONG_BALL_H
#define FINAL_PROJECT_PONG_BALL_H

#include <glm/detail/type_vec2.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace finalproject {

class Pong_Ball {
public:
    /**
     * The constructor that takes in the position vector and the velocity vector
     * and initializes them to create an object - atom
     * @param position is the vector of position in 2-d
     * @param velocity is the velocity vetor
     */
    Pong_Ball(glm::vec2 &position, glm::vec2 &velocity);

    /**
     * This the getter for position vector of an atom
     * @return the position vector
     */
    glm::vec2 getPosition();

    /**
     * This the getter for velocity vector of an atom
     * @return the velocity vector
     */
    glm::vec2 getVelocity();

    /**
     * This is the setter for position of an atom
     * @param position
     */
    void setPosition(glm::vec2 &position);

    /**
     * This is the setter for velocity of an atom
     * @param position
     */
    void setVelocity(glm::vec2 &velocity);

    /**
     * This method updates the velocity of the atom after it collides either with
     * another atom or walls
     * @param second_atom if it collides with an second atom
     * @param type 0 represents collision with another atom, 1 collision with x wall, 2 collision with y wall
     */
    void UpdateAfterCollision(Pong_Ball &second_ball, int type);

private:
    /**
     * This class object is defined by its position and velocity vector declared below
     */
    glm::vec2 position_;
    glm::vec2 velocity_;

};
}


#endif //FINAL_PROJECT_PONG_BALL_H
