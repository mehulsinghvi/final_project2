#include "simulator.h"
using cinder::app::KeyEvent;

namespace finalproject {

PongApp::PongApp() {
  add_new_ball_ = 0;
  ball_counter = 0;
  start_ = true;
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  glm::vec2 corner = glm::vec2(kMargin, kMargin * 2 - kSize1);
  glm::vec2 size = glm::vec2(kMargin * 7, kMargin * 4 + kSize1 * 2);
  glm::vec2 paddle_corner = glm::vec2(kMargin + kSize2, kMargin * 2 + kSize1);
  glm::vec2 paddle_velocity = glm::vec2(0, kSize1 * 2);
  glm::vec2 paddle_size = glm::vec2(kSize1, kSize2 * 2);
  glm::vec2 paddle_distance = glm::vec2(kMargin * 6, kMargin * 4);
  glm::vec2 corner_pad = glm::vec2(0, kMargin * 2);
  Paddle paddle = Paddle(corner_pad, paddle_corner, paddle_velocity,
                         paddle_size, paddle_distance, 4);
  logic_ = CollisionLogic(corner, size, paddle);
  box_ = ci::Rectf(corner, corner + size);
  glm::vec2 ball_entrance = paddle_corner + glm::vec2(kMargin * 4, kMargin * 4);
  glm::vec2 ball_velocity = glm::vec2(kSize1, kSize1);
  logic_.AddNewBall(ball_entrance, ball_velocity);
  paddle_ = paddle;
}

void PongApp::draw() {
  if (start_) {
    ci::gl::draw(image3, ci::Rectf(top_left_corner, bottomRightCorner));
    return;
  }
  ci::gl::draw(image, ci::Rectf(top_left_corner, bottomRightCorner));
  if (ball_counter >= 30) {
    ci::gl::draw(image2, ci::Rectf(top_left_corner, bottomRightCorner));
    glm::vec2 titleLoc =
        glm::vec2(box_.x1 + (box_.x2 - box_.x1) / 2, box_.y1 - 100);
    if (logic_.GetScore(CollisionLogic::left) >
        logic_.GetScore(CollisionLogic::right)) {
      ci::gl::drawStringCentered("Left won!", titleLoc, ci::Color("pink"),
                                 arcade_font_2_);
    } else if (logic_.GetScore(CollisionLogic::left) <
               logic_.GetScore(CollisionLogic::right)) {
      ci::gl::drawStringCentered("Right won!", titleLoc, ci::Color("pink"),
                                 arcade_font_2_);
    } else {
      ci::gl::drawStringCentered("No winner!", titleLoc, ci::Color("pink"),
                                 ci::Font("helvetica", 100));
    }
    return;
  }
  glm::vec2 titleLoc3 =
      glm::vec2(box_.x1 + (box_.x2 - box_.x1) / 2, box_.y2 + 50);
  ci::gl::drawStringCentered("restart", titleLoc3, ci::Color("yellow"),
                             arcade_font_2_);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(box_);
  for (Pong_Ball balls : logic_.GetAllBalls()) {
    ci::gl::color(ci::Color("yellow"));
    ci::gl::drawSolidCircle(balls.GetPosition(), 5);
  }
  paddle_.DrawPaddles();
  glm::vec2 titleLoc =
      glm::vec2(box_.x1 + (box_.x2 - box_.x1) / 2, box_.y1 + 50);
  ci::gl::drawStringCentered(
      "Right: " + std::to_string(logic_.GetScore(CollisionLogic::right)),
      titleLoc, ci::Color("red"), arcade_font_);
  glm::vec2 titleLoc2 =
      glm::vec2(box_.x1 + (box_.x2 - box_.x1) / 2, box_.y2 - 50);
  ci::gl::drawStringCentered(
      "Left: " + std::to_string(logic_.GetScore(CollisionLogic::left)),
      titleLoc2, ci::Color("blue"), arcade_font_);
}

void PongApp::update() {
  if (ball_counter >= 30) {
    return;
  }
  logic_.UpdateState();
}

// https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
void PongApp::keyDown(cinder::app::KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_UP) {
    paddle_.SlideLeftPaddle(1);
    logic_.SetPaddle(paddle_);
  } else if (event.getCode() == KeyEvent::KEY_DOWN) {
    paddle_.SlideLeftPaddle(2);
    logic_.SetPaddle(paddle_);
  } else if (event.getCode() == KeyEvent::KEY_CAPSLOCK) {
    if (add_new_ball_ == 1) {
      ball_counter++;
      glm::vec2 paddle_corner = glm::vec2(kMargin + kSize2, kMargin + kSize1);
      glm::vec2 ball_entrance =
          paddle_corner + glm::vec2(kMargin * 4, kMargin * 4);
      int rand1 = rand() % 11 + (-5);
      int rand2 = rand() % 11 + (-5);
      glm::vec2 ball_velocity = glm::vec2(rand1, rand2);
      logic_.AddNewBall(ball_entrance, ball_velocity);
      add_new_ball_ = 0;
    } else {
      add_new_ball_ = 2;
    }
  } else if (event.getCode() == KeyEvent::KEY_SPACE) {
    ball_counter = 0;
    logic_.RestartGame();
  } else if (event.getCode() == KeyEvent::KEY_1) {
    start_ = false;
  }
}

void PongApp::mouseWheel(cinder::app::MouseEvent event) {
  if (event.getWheelIncrement() > 0 && event.isShiftDown()) {
    paddle_.SlideRightPaddle(1);
    logic_.SetPaddle(paddle_);
  } else if (event.getWheelIncrement() < 0 && event.isShiftDown()) {
    paddle_.SlideRightPaddle(2);
    logic_.SetPaddle(paddle_);
  }
}

// https://libcinder.org/docs/classcinder_1_1_font.html
// https://libcinder.org/docs/classcinder_1_1_data_source.html
void PongApp::setup() {
  // this was copied from miguel fernandez's campuswire answer (next 3 lines)
  auto tempImg = loadImage(ci::app::loadAsset("img.png"));
  image = ci::gl::Texture2d::create(tempImg);
  this->top_left_corner = ci::vec2(0, 0);
  this->bottomRightCorner = ci::vec2(top_left_corner.x + kWindowSize,
                                     top_left_corner.y + kWindowSize);
  auto tempImg2 = loadImage(ci::app::loadAsset("img_1.png"));
  image2 = ci::gl::Texture2d::create(tempImg2);
  auto tempImg3 = loadImage(ci::app::loadAsset("img_2.png"));
  image3 = ci::gl::Texture2d::create(tempImg3);
  arcade_font_ =
      ci::Font(ci::DataSourcePath::create(std::experimental::filesystem::path(
                   ci::app::getAssetPath("ARCADE_N.TTF"))),
               12);
  arcade_font_2_ =
      ci::Font(ci::DataSourcePath::create(std::experimental::filesystem::path(
                   ci::app::getAssetPath("ARCADE_N.TTF"))),
               25);
}

void PongApp::mouseDown(cinder::app::MouseEvent event) {
  if (add_new_ball_ == 2 && event.isLeft()) {
    ball_counter++;
    glm::vec2 paddle_corner = glm::vec2(kMargin + kSize2, kMargin + kSize1);
    glm::vec2 ball_entrance =
        paddle_corner + glm::vec2(kMargin * 4, kMargin * 4);
    int rand1 = rand() % 11 + (-5);
    int rand2 = rand() % 11 + (-5);
    glm::vec2 ball_velocity = glm::vec2(rand1, rand2);
    logic_.AddNewBall(ball_entrance, ball_velocity);
    add_new_ball_ = 0;
  } else if (add_new_ball_ == false) {
    add_new_ball_ = 1;
  } else if (event.isRight()) {
    if (event.getX() > kMargin * 2 && event.getX() < kMargin * 6) {
      if (event.getY() > kMargin * 4 && event.getY() < kMargin * 8) {
        ball_counter = 0;
        logic_.RestartGame();
      }
    }
  }
}

}  // namespace finalproject
