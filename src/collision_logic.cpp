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

CollisionLogic::CollisionLogic(glm::vec2 corner, glm::vec2 size, Paddle paddle)
        : corner_(corner), box_size_(size) {
    paddle_ = paddle;
    left_score_ = 0;
    right_score_ = 0;
}

void CollisionLogic::UpdateState() {
//    glm::vec2 curr_position = paddle_.GetPosition();
//    paddle_.SetPosition(curr_position);
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
        glm::vec2 curr_pos = curr_ball.GetPosition();
        glm::vec2 curr_vel = curr_ball.GetVelocity();
        curr_pos += curr_vel;
        curr_ball.SetPosition(curr_pos);
        curr_ball.SetVelocity(curr_vel);
        all_balls.at(i) = curr_ball;
    }
}

void CollisionLogic::BallCollisionsUpdate(Pong_Ball &ball, Pong_Ball &second) const {
    if (2 * radius >= glm::distance(ball.GetPosition(), second.GetPosition())) {
        if (!IsStickyCollision(ball, second, 1, ball.GetPosition())) {
            ball.UpdateAfterCollision(second, 0);
            second.UpdateAfterCollision(ball, 0); //update
        }
    }
}

bool CollisionLogic::IsStickyCollision(Pong_Ball &ball1, Pong_Ball &ball2, int type, glm::vec2 wall_vec) {
    float dotProduct;
    if (type == 1) {
        dotProduct = glm::dot(ball1.GetVelocity() - ball2.GetVelocity(),
                              ball1.GetPosition() - ball2.GetPosition());
    }
    if (type == 2) {
        dotProduct = glm::dot(ball1.GetVelocity(), ball1.GetPosition() - wall_vec);
    }
    if (dotProduct < 0) {
        return false;
    } else {
        return true;
    }
}

void CollisionLogic::WallCollisionsUpdate(Pong_Ball &ball) {
    glm::vec2 future_pos = ball.GetPosition();
    future_pos += ball.GetVelocity();
    // This if conditional checks collision with first x wall
    if (abs(future_pos.x - corner_.x) <= radius) {
        if (!CollisionLogic::IsStickyCollision(ball, ball, 2,
                                               glm::vec2(corner_.x, future_pos.y))) {
//            auto it = find(all_balls.begin(), all_balls.end(), ball);
//            int idx = 0;
//            if(it != all_balls.end()) {
//                idx = it - all_balls.begin();
//            }
//            if(all_balls.empty() == false) {
//                all_balls.erase(all_balls.begin());
//            }
            glm::vec2 pos = corner_ + glm::vec2(box_size_.x/2, box_size_.y/2);
            ball.SetPosition(pos);
            glm::vec2 vel = glm::vec2(0, 5);
            ball.SetVelocity(vel);
            right_score_ = right_score_ + 1;
        }
    }
    // This if conditional checks collision with second x wall
    if (abs(future_pos.x - corner_.x - box_size_.x) <= radius) {
        if (!CollisionLogic::IsStickyCollision(
                ball, ball, 2, glm::vec2(corner_.x + box_size_.x, future_pos.y))) {
            glm::vec2 pos = corner_ + glm::vec2(box_size_.x/2, box_size_.y/2);
            ball.SetPosition(pos);
            glm::vec2 vel = glm::vec2(0, 5);
            ball.SetVelocity(vel);
            left_score_ = left_score_ + 1;
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
//    if(paddle_.CheckCollisionWithPaddle(ball)) {
//        ball.UpdateAfterCollision(ball, 1);
//    }
    paddle_.CheckCollisionWithPaddle(ball);
}

void CollisionLogic::AddNewBall(glm::vec2 position, glm::vec2 velocity) {
    Pong_Ball idealAtom(position, velocity);
    all_balls.push_back(idealAtom);
}

std::vector<Pong_Ball> CollisionLogic::GetAllBalls() const {
    return all_balls;
}

Paddle CollisionLogic::GetPaddle() const {
    return paddle_;
}

void CollisionLogic::SetPaddle(Paddle paddle) {
    paddle_ = paddle;
}

size_t CollisionLogic::GetScore(int type) {
    if(type == 1) {
        return left_score_;
    }
    else {
        return right_score_;
    }
}

    CollisionLogic::CollisionLogic() = default;
}