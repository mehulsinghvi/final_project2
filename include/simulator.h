#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "collision_logic.h"

namespace finalproject {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class PongApp : public ci::app::App {
 public:
  PongApp();

  // overrides all the cinder display functions and input keys
  void setup() override;
  void draw() override;
  void update() override;
  void keyDown(cinder::app::KeyEvent event) override;
  void mouseWheel(cinder::app::MouseEvent event) override;
  void mouseDown(cinder::app::MouseEvent event) override;

  const int kWindowSize = 875;
  const int kMargin = 100;
  const int kSize1 = 10;
  const int kSize2 = 50;

 private:
  CollisionLogic logic_;
  Paddle paddle_;
  ci::Rectf box_;
  size_t ball_counter;
  size_t add_new_ball_;

  //this was inspired by miguel fernandez's campuswire answer
  ci::vec2 top_left_corner;
  ci::vec2 bottomRightCorner;
  ci::gl::Texture2dRef image;
  ci::gl::Texture2dRef image2;
  ci::gl::Texture2dRef image3;
  bool start_;
  ci::Font arcade_font_;
  ci::Font arcade_font_2_;
};
}  // namespace finalproject