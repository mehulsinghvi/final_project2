//
// Created by mehul on 08-03-2022.
//
#include "collision_logic.h"
#include "paddle.h"
#include <algorithm>
#include <glm/geometric.hpp>
#include <iostream>

namespace finalproject {

//Please look at the header file for documentation

CollisionLogic::CollisionLogic(glm::vec2 corner, glm::vec2 size)
        : corner_(corner), box_size_(size) {}

void CollisionLogic::UpdateState() {
    //std::sort(all_balls.begin(), all_balls.end());
    for (size_t i = 0; i < all_balls.size(); i++) {
        Pong_Ball curr_ball = all_balls.at(i);
        if (i + 1 < all_balls.size()) {
            for (size_t j = i + 1; j < all_balls.size(); j++) {
                Pong_Ball curr_ball2 = all_balls.at(j);
                BallCollisionsUpdate(curr_ball, curr_ball2);
                all_balls.at(j) = curr_ball2;
            }
        }
        PaddleCollisionUpdate(curr_ball);
        WallCollisionsUpdate(curr_ball);
        glm::vec2 curr_pos = curr_ball.getPosition();
        glm::vec2 curr_vel = curr_ball.getVelocity();
        curr_pos += curr_vel;
        curr_ball.setPosition(curr_pos);
        curr_ball.setVelocity(curr_vel);
        all_balls.at(i) = curr_ball;
    }
}

void CollisionLogic::BallCollisionsUpdate(Pong_Ball &ball, Pong_Ball &second) const {
    if (2 * radius >= glm::distance(ball.getPosition(), second.getPosition())) {
        if (!IsStickyCollision(ball, second, 1, ball.getPosition())) {
            ball.UpdateAfterCollision(second, 0);
            second.UpdateAfterCollision(ball, 0); //update
        }
    }
}

bool CollisionLogic::IsStickyCollision(Pong_Ball &ball1, Pong_Ball &ball2, int type, glm::vec2 wall_vec) {
    float dotProduct;
    if (type == 1) {
        dotProduct = glm::dot(ball1.getVelocity() - ball2.getVelocity(),
                              ball1.getPosition() - ball2.getPosition());
    }
    if (type == 2) {
        dotProduct = glm::dot(ball1.getVelocity(), ball1.getPosition() - wall_vec);
    }
    if (dotProduct < 0) {
        return false;
    } else {
        return true;
    }
}

void CollisionLogic::WallCollisionsUpdate(Pong_Ball &ball) const {
    glm::vec2 future_pos = ball.getPosition();
    future_pos += ball.getVelocity();
    // This if conditional checks collision with first x wall
    if (abs(future_pos.x - corner_.x) <= radius) {
        if (!CollisionLogic::IsStickyCollision(ball, ball, 2,
                                               glm::vec2(corner_.x, future_pos.y))) {
            ball.UpdateAfterCollision(ball, 1); // update score for right
        }
    }
    // This if conditional checks collision with second x wall
    if (abs(future_pos.x - corner_.x - box_size_.x) <= radius) {
        if (!CollisionLogic::IsStickyCollision(
                ball, ball, 2, glm::vec2(corner_.x + box_size_.x, future_pos.y))) {
            ball.UpdateAfterCollision(ball, 1); // update score for left
        }
    }
    // This if conditional checks collision with first y wall
    if (abs(future_pos.y - corner_.y) <= radius) {
        if (!CollisionLogic::IsStickyCollision(ball, ball, 2,
                                               glm::vec2(future_pos.x, corner_.y))) {
            ball.UpdateAfterCollision(ball, 2);
        }
    }
    // This if conditional checks collision with second y wall
    if (abs(future_pos.y - corner_.y - box_size_.y) <= radius) {
        if (!CollisionLogic::IsStickyCollision(
                ball, ball, 2, glm::vec2(future_pos.x, corner_.y + box_size_.y))) {
            ball.UpdateAfterCollision(ball, 2);
        }
    }
}

void CollisionLogic::PaddleCollisionUpdate(Pong_Ball &ball) const {
//    if(Paddle::CheckCollisionWithPaddle(ball) == true) {
//
//    }
}

void CollisionLogic::AddNewBall(glm::vec2 position, glm::vec2 velocity) {
    Pong_Ball idealAtom(position, velocity);
    all_balls.push_back(idealAtom);
}

std::vector<Pong_Ball> CollisionLogic::GetAllBalls() const {
    return all_balls;
}

    CollisionLogic::CollisionLogic() = default;
}