#include <core/slider.h>
#include "cinder/gl/gl.h"

namespace kaleidoscope {

Slider::Slider(const glm::vec2 &location,
                             const glm::vec2 &dimensions,
                             const std::string &title) :
                             position_(location), dimensions_(dimensions), message_(title) {
  degree_ = 0;
}

bool Slider::WasEdited(const glm::ivec2 &mouse_loc) const {
  return position_.x + dimensions_.x/2 - 5 <= mouse_loc.x &&
         mouse_loc.x <= position_.x + dimensions_.x/2 + 5 &&
         position_.y + 25 <= mouse_loc.y &&
         mouse_loc.y <= position_.y + dimensions_.y;
}

void Slider::Draw() const {
  ci::gl::drawString(message_, position_,
                             ci::Color("white"),ci::Font("arial", 20));
  float bar_length = dimensions_.y-25;
  ci::gl::color(ci::Color("black"));
  ci::gl::drawLine(position_ + glm::vec2(dimensions_.x/2, 25),
                   position_ + glm::vec2(dimensions_.x/2, dimensions_.y));
  glm::vec2 box_loc = position_ + glm::vec2(dimensions_.x/2 - 5, dimensions_.y - (degree_*bar_length) -2);
  ci::gl::drawSolidRect(ci::Rectf(box_loc, box_loc + glm::vec2(10, 4)));
}

float Slider::GetDegree() {
  return degree_;
}

void Slider::Slide(const glm::ivec2 &mouse_loc) {
  float total = dimensions_.y - 25;
  float current_loc = mouse_loc.y - position_.y - 25;
  degree_ = 1 - current_loc/total;
}

}