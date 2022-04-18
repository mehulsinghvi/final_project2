#include "simulator.h"

namespace finalproject {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  container_ = GasContainer(glm::vec2(kMargin, kMargin),glm::vec2 (kSize1, kSize2));
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace finalproject
