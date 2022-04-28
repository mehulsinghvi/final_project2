#include "simulator.h"
using cinder::app::KeyEvent;

namespace finalproject {

PongApp::PongApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
    glm::vec2 corner = glm::vec2 (kMargin, kMargin);
    glm::vec2 size = glm::vec2(kMargin * 7, kMargin * 7);
    glm::vec2 paddle_corner = glm::vec2 (kMargin + kSize2, kMargin + kSize1);
    glm::vec2 paddle_velocity = glm::vec2 (0, kSize1);
    glm::vec2 paddle_size = glm::vec2 (kSize1, kSize2);
    glm::vec2 paddle_distance = glm::vec2 (kMargin * 6, kMargin * 6);
    Paddle paddle = Paddle(paddle_corner, paddle_corner, paddle_velocity, paddle_size, paddle_distance, 10);
    logic_ = CollisionLogic(corner, size, paddle);
    box_ = ci::Rectf(corner, corner + size);
    glm::vec2 ball_entrance = paddle_corner + glm::vec2 (kMargin * 4, kSize1);
    glm::vec2 ball_velocity = glm::vec2 (kSize1, kSize1);
    logic_.AddNewBall(ball_entrance, ball_velocity);
    paddle_ = paddle;
}
//resolvinf conflict on git
void PongApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(box_);
  for(Pong_Ball balls : logic_.GetAllBalls())  {
      ci::gl::color(ci::Color("yellow"));
      ci::gl::drawSolidCircle(balls.GetPosition(), 10);
  }
    paddle_.DrawPaddles();
  glm::vec2 titleLoc = glm::vec2(box_.x1 + (box_.x2 - box_.x1) / 2, box_.y1 + 50);
  ci::gl::drawStringCentered(std::to_string(logic_.GetScore(1)), titleLoc, ci::Color("red"), ci::Font("helvetica", 30));
}

void PongApp::update() {
    //logic_.SetPaddle(paddle_);
  logic_.UpdateState();
}

//https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
void PongApp::keyDown(cinder::app::KeyEvent event) {
    if(event.getCode() == KeyEvent::KEY_UP) {
        paddle_.SlideLeftPaddle(1);
        logic_.SetPaddle(paddle_);
    }
    else if(event.getCode() == KeyEvent::KEY_DOWN) {
        paddle_.SlideLeftPaddle(2);
        logic_.SetPaddle(paddle_);
    }
    else if(event.getCode() == KeyEvent::KEY_CAPSLOCK) {
        glm::vec2 paddle_corner = glm::vec2 (kMargin + kSize2, kMargin + kSize1);
        glm::vec2 ball_entrance = paddle_corner + glm::vec2 (kMargin * 4, kSize1);
        int rand1 = rand() % 5 - 5;
        int rand2 = rand() % 5 - 5;
        glm::vec2 ball_velocity = glm::vec2 (rand1, rand2);
        logic_.AddNewBall(ball_entrance, ball_velocity);
    }
}

void PongApp::mouseDown(cinder::app::MouseEvent event) {
    if(event.isRight() && event.isShiftDown()) {
        paddle_.SlideRightPaddle(1);
        logic_.SetPaddle(paddle_);
    }
    else if(event.isLeft() && event.isShiftDown()) {
        paddle_.SlideRightPaddle(2);
        logic_.SetPaddle(paddle_);
    }
}


}  // namespace finalproject
