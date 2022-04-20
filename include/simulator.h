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

  void draw() override;
  void update() override;
  void keyDown(cinder::app::KeyEvent event) override;
  void mouseDown(cinder::app::MouseEvent event) override;

  const int kWindowSize = 875;
  const int kMargin = 100;
  const int kSize1 = 500;
  const int kSize2 = 300;

 private:
  CollisionLogic logic_;
  ci::Rectf box_;
};

}  // namespace finalproject
