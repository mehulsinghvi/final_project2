#include "new1.h"
#include "collision_logic.h"

namespace finalproject {

using glm::vec2;

GasContainer::GasContainer() = default;
GasContainer::GasContainer(const vec2& corner, const vec2& size) {
    logic_ = CollisionLogic(corner, size);
    box = ci::Rectf(corner, corner + size);
    for(int i = 0 ; i < 25; i++) {
        float randNum = rand()%((int) glm::min(size.x, size.y) + 1) + corner.x;
        logic_.AddNewBall(vec2(randNum, randNum), vec2(0.7, -0.9));
    }

}

void GasContainer::Display() const {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRect(box);
    for(Pong_Ball log : logic_.GetAllBalls())  {
        ci::gl::color(ci::Color("orange"));
        ci::gl::drawSolidCircle(log.getPosition(), 10);
    }
}

void GasContainer::AdvanceOneFrame() {
  logic_.UpdateState();
}

}  // namespace finalproject