//
// Created by mehul on 08-03-2022.
//

#ifndef IDEAL_GAS_COLLISION_LOGIC_H
#define IDEAL_GAS_COLLISION_LOGIC_H

#include <vector>
#include "pong_ball.h"

namespace finalproject {
    class CollisionLogic {
    public:
        /**
         * This is the constructor for this class and takes in the corner vector required to draw rectangle
         * and also takes the length and breadth of rectangle in vec2 form
         * @param corner is the vec required to draw rectangle
         * @param size of the rectangle
         */
        CollisionLogic(glm::vec2 corner, glm::vec2 size);

        /**
         * Default empty constructor
         */
        CollisionLogic();

        /**
         * This function updates the atom state of all atoms in the vector after
         * taking into account their collisions etc
         */
        void UpdateState();

        /**
         * This function simply adds another new atom to the vector list
         * @param position of the atom being added
         * @param velocity of the atom being added
         */
        void AddNewAtom(glm::vec2 position, glm::vec2 velocity);

        /**
         * This is the getter for the vector list with all the atoms
         * @return the vector of all the atoms
         */
        std::vector<Pong_Ball> GetAllBalls() const;

    private:
        // this is the vector container keeping track of all the atoms in the box at any moment
        std::vector<Pong_Ball> all_balls;
        // this is the corner of the rectangle needed for drawing rectangle and finding out wall positions
        glm::vec2 corner_;
        // keeping track of box size for wall collisions
        glm::vec2 box_size_;
        // the radius of all atoms - this is not constant because week 2 will require atoms be of different length
        float radius = 10;

        /**
         * This helper functions return false if the collision is actually happening and helps avoid infinite
         * back and forth between two atoms (due to small velocity vecs) - aka sticky collisions
         * In other words, tests whether two atoms are moving towards each other for collision
         * @param atom1
         * @param atom2
         * @param type is to figure out if the collision is between two atoms or with a wall
         * @param wall_vec is the position vector of wall boundary
         * @return true is collision is sticky, false otherwise
         */
        static bool IsStickyCollision(Pong_Ball& ball1, Pong_Ball& ball2, int type, glm::vec2 wall_vec);

        /**
         * This function handles collisions with the wall and updates the velocity of the given atom
         * @param atom to handles collision for
         */
        void WallCollisionsUpdate(Pong_Ball& ball) const;

        /**
         * This function handles collisions between two atoms and updates the velocity of both atoms
         * @param atom to handles collision for
         * @param second is the second atom involved in collision
         */
        void BallCollisionsUpdate(Pong_Ball& ball, Pong_Ball& second) const;

        void PaddleCollisionUpdate(Pong_Ball& ball) const;
    };
}


#endif //IDEAL_GAS_COLLISION_LOGIC_H
