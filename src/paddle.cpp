//
// Created by mehul on 18-04-2022.
//

#include "paddle.h"
#include "collision_logic.h"
#include <cinder/gl/wrapper.h>
#include <cinder/gl/draw.h>

namespace finalproject {

Paddle::Paddle(glm::vec2 &position, glm::vec2 &velocity, glm::vec2 &size, glm::vec2 &distance) {
    position_ = position;
    velocity_ = velocity;
    size_ = size;
    distance_ = distance;
    position2_ = position + distance;
    velocity2_ = velocity;
}

void Paddle::DrewPaddles() {
    ci::Rectf box = ci::Rectf(position_, position_ + size_);
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidRect(box);
    ci::gl::color(ci::Color("yellow"));
    ci::gl::drawStrokedRect(box);

    ci::Rectf box2 = ci::Rectf(position_ + distance_, position_ + size_ + distance_);
    ci::gl::color(ci::Color("red"));
    ci::gl::drawSolidRect(box2);
    ci::gl::color(ci::Color("green"));
    ci::gl::drawStrokedRect(box2);
}

glm::vec2 Paddle::GetPosition() {
    return position_;
}

glm::vec2 Paddle::GetVelocity() {
    return velocity_;
}

void Paddle::SetPosition(glm::vec2 &position) {
    position_ = position;
}

void Paddle::SetVelocity(glm::vec2 &velocity) {
    velocity_ = velocity;
}

bool Paddle::CheckCollisionWithPaddle(finalproject::Pong_Ball &ball) const {
    glm::vec2 future_pos = ball.getPosition();
    future_pos += ball.getVelocity();
    if (abs(future_pos.x - position_.x) <= KRadius && abs(future_pos.y - position_.y) <= KRadius) {
        ball.UpdateAfterCollision(ball, 1);
    }
    if (abs(future_pos.x - position2_.x) <= KRadius && abs(future_pos.y - position2_.y) <= KRadius) {
        ball.UpdateAfterCollision(ball, 1);
    }
    return false;
}

void Paddle::SlideLeftPaddle(int type) {
    if(type == 1) {
        position_ += velocity_;
    }
    else {
        position_ -= velocity_;
    }
}

void Paddle::SlideRightPaddle(int type) {
    if(type == 1) {
        position2_ += velocity2_;
    }
    else {
        position2_ -= velocity2_;
    }
}


}
