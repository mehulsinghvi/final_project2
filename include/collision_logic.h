//
// Created by mehul on 08-03-2022.
//

#ifndef FINAL_PROJECT_COLLISION_LOGIC_H
#define FINAL_PROJECT_COLLISION_LOGIC_H

#include <vector>
#include "pong_ball.h"
#include "paddle.h"

namespace finalproject {
    class CollisionLogic {
    public:
        /**
         * This is the constructor for this class and takes in the corner vector required to draw rectangle
         * and also takes the length and breadth of rectangle in vec2 form
         * @param corner is the vec required to draw rectangle
         * @param size of the rectangle
         */
        CollisionLogic(glm::vec2 corner, glm::vec2 size, Paddle paddle);

        /**
         * Default empty constructor
         */
        CollisionLogic();

        /**
         * This function updates the state of all elements on the board, including balls and slider paddles
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
        Paddle GetPaddle() const;
        void SetPaddle(Paddle paddle);

        size_t GetScore(int type);

//        const glm::vec2 KMargin = glm::vec2(20,0);
//        const glm::vec2 KVelocity = glm::vec2(10,0);
//        const glm::vec2 KSize = glm::vec2(3,10);
//        const glm::vec2 KDistance = glm::vec2(500,0);

    private:
        std::vector<Pong_Ball> all_balls;
        // this is the corner of the rectangle needed for drawing rectangle and finding out wall positions
        glm::vec2 corner_;
        // keeping track of box size for wall collisions
        glm::vec2 box_size_;
        // the radius of all balls
        float radius = 10;

        Paddle paddle_;

        size_t left_score_;
        size_t right_score_;

        /**
         * This helper functions return false if the collision is actually happening and helps avoid infinite
         * back and forth between two balls (due to small velocity vecs) - aka sticky collisions
         * @param ball1
         * @param ball2
         * @param type is to figure out if the collision is between two balls or with a wall/paddle
         * @param wall_vec is the position vector of wall boundary
         * @return true is collision is sticky, false otherwise
         */
        static bool IsStickyCollision(Pong_Ball& ball1, Pong_Ball& ball2, int type, glm::vec2 wall_vec);

        /**
         * This function handles collisions with the wall and updates the velocity
         * @param atom to handles collision for
         */
        void WallCollisionsUpdate(Pong_Ball& ball);

        /**
         * This function handles collisions between two balls and updates the velocity of both atoms
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
}


#endif //FINAL_PROJECT_COLLISION_LOGIC_H
