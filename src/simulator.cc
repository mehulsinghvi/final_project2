#include "simulator.h"
using cinder::app::KeyEvent;

namespace finalproject {

PongApp::PongApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
    glm::vec2 corner = glm::vec2 (kMargin * 4, kSize1);
    glm::vec2 size = glm::vec2(kMargin * 6 - kSize1, kWindowSize - kSize1 * 2);
    glm::vec2 paddle_corner = glm::vec2 (kMargin * 4, kSize1);
    glm::vec2 paddle_velocity = glm::vec2 (kMargin * 4, kSize1);
    glm::vec2 paddle_size = glm::vec2 (kMargin * 4, kSize1);
    glm::vec2 paddle_distance = glm::vec2 (kMargin * 4, kSize1);
    Paddle paddle = Paddle(paddle_corner, paddle_velocity, paddle_size, paddle_distance, 10);
    logic_ = CollisionLogic(corner, size, paddle);
    box_ = ci::Rectf(corner, corner + size);
    glm::vec2 ball_entrance = paddle_corner + glm::vec2 (kMargin * 4, kSize1);
    logic_.AddNewBall(ball_entrance, paddle_velocity);
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
    logic_.GetPaddle().DrawPaddles();
}

void PongApp::update() {
  logic_.UpdateState();
}

//https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
void PongApp::keyDown(cinder::app::KeyEvent event) {
    if(event.getCode() == KeyEvent::KEY_UP) {
        logic_.GetPaddle().SlideLeftPaddle(1);
    }
    else if(event.getCode() == KeyEvent::KEY_DOWN) {
        logic_.GetPaddle().SlideLeftPaddle(2);
    }
}

void PongApp::mouseDown(cinder::app::MouseEvent event) {
    if(event.isRight() && event.isShiftDown()) {
        logic_.GetPaddle().SlideRightPaddle(1);
    }
    else if(event.isLeft() && event.isShiftDown()) {
        logic_.GetPaddle().SlideRightPaddle(2);
    }
}


}  // namespace finalproject
