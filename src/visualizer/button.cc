#include <cinder/gl/gl.h>

#include <visualizer/button.h>
#include <core/constants.h>

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::string;

Button::Button(const vec2 &position, const vec2 &dimensions, const string &message) :
    position_(position), dimensions_(dimensions), message_(message) {}

bool Button::WasPressed(const ivec2 &mouse_location) const {
  return position_.x <= mouse_location.x &&
      position_.x + dimensions_.x >= mouse_location.x&&
      position_.y <= mouse_location.y &&
      position_.y + dimensions_.y >= mouse_location.y;
}

void Button::SetMessage(const string &new_message) {
  message_ = new_message;
}

void Button::Draw() const {
  // Draw button background
  ci::gl::color(kButtonColor);
  ci::gl::drawSolidRect(ci::Rectf(position_, position_ + dimensions_));

  // Write on Button
  vec2 string_loc = vec2(position_.x + dimensions_.x/2,
                         position_.y + dimensions_.y/2 - kFontSize/2);
  ci::gl::drawStringCentered(message_, string_loc, kButtonTextColor, ci::Font(kFontStyle, kFontSize));
}

const string &Button::GetMessage() const {
  return message_;
}

} // namespace visualizer

} // namespace kaleidoscope