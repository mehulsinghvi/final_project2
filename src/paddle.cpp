//
// Created by mehul on 18-04-2022.
//

#include "paddle.h"
#include "collision_logic.h"
#include <cinder/gl/wrapper.h>
#include <cinder/gl/draw.h>

namespace finalproject {

    Paddle::Paddle(glm::vec2 corner, glm::vec2 &position, glm::vec2 &velocity, glm::vec2 &size, glm::vec2 &distance, float radius) {
        position_ = position;
        velocity_ = velocity;
        size_ = size;
        distance_ = distance;
        position2_ = position + glm::vec2(distance.x - size.x, 0);
        velocity2_ = velocity;
        radius_ = radius;
        corner_ = corner;
    }

    void Paddle::DrawPaddles() {
        ci::Rectf box = ci::Rectf(position_, position_ + size_);
        ci::gl::color(ci::Color("blue"));
        ci::gl::drawSolidRect(box);
        ci::gl::color(ci::Color("yellow"));
        ci::gl::drawStrokedRect(box);

        ci::Rectf box2 = ci::Rectf(position2_, position2_ + size_);
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
//    glm::vec2 future_pos = ball.GetPosition();
//    future_pos += ball.GetVelocity();
        bool collided = false;
        glm::vec2 future_pos = ball.GetPosition();
        if (abs(future_pos.x - position_.x - size_.x) <= radius_ && (future_pos.y - position_.y - size_.y) <= radius_ && (future_pos.y - position_.y) >= radius_) { //problem here
            ball.UpdateAfterCollision(ball, 1);
            collided = true;
        }
        if (abs(future_pos.x - position2_.x) <= radius_ && (future_pos.y - position2_.y - size_.y) <= radius_ && (future_pos.y - position2_.y) >= radius_) {
            ball.UpdateAfterCollision(ball, 1);
            collided = true;
        }
        if(collided) {
            return true;
        }
        return false;
    }

    void Paddle::SlideLeftPaddle(int type) {
        if(type == 1 && position_.y >= corner_.y /*&& position_.y + size_.y > corner_.y + distance_.y*/) {
            position_ -= velocity_;
        }
        if(type == 2 && position_.y + size_.y <= corner_.y + distance_.y) {
            position_ += velocity_;
        }
    }

    void Paddle::SlideRightPaddle(int type) {
        if(type == 1 && position2_.y + size_.y <= corner_.y + distance_.y) {
            position2_ += velocity_;
        }
        if(type == 2 && position2_.y >= corner_.y ) {
            position2_ -= velocity_;
        }
    }

    Paddle::Paddle() {}
}
