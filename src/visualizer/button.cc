#include <visualizer/button.h>
#include "cinder/gl/gl.h"

namespace kaleidoscope {

namespace visualizer {

Button::Button(const glm::vec2 &position, const glm::vec2 &dimensions,
               const std::string &message) :
    position_(position), dimensions_(dimensions), message_(message) {}

bool Button::WasPressed(const glm::ivec2 &mouse_location) const {
  return position_.x <= mouse_location.x &&
      position_.x + dimensions_.x >= mouse_location.x&&
      position_.y <= mouse_location.y &&
      position_.y + dimensions_.y >= mouse_location.y;
}

void Button::SetMessage(const std::string &new_message) {
  message_ = new_message;
}

void Button::Draw() const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(ci::Rectf(position_, position_ + dimensions_));
  glm::vec2 string_loc = glm::vec2(position_.x + 0.5 * dimensions_.x,
                                   position_.y + 0.5 * dimensions_.y - 10);
  ci::gl::drawStringCentered(message_, string_loc,
                             ci::Color("white"), ci::Font("arial", 20));
}

const std::string &Button::GetMessage() const {
  return message_;
}

} // namespace visualizer

} // namespace kaleidoscope