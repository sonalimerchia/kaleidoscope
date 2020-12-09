#include <cinder/gl/gl.h>

#include <core/button.h>

namespace kaleidoscope {

using glm::vec2;
using glm::ivec2;
using std::string;

using ci::Color;
using ci::Font;

const float Button::kFontSize = 30;
const string Button::kFontStyle = "arial";

Button::Button(const vec2 &position, const vec2 &dimensions, const string &message) :
    area_(position, position + dimensions), message_(message) {}

bool Button::WasPressed(const ivec2 &mouse_location) const {
  return area_.contains(mouse_location);
}

void Button::SetMessage(const string &new_message) {
  message_ = new_message;
}

void Button::Draw() const {
  // Draw button background
  ci::gl::color(Color("black"));
  ci::gl::drawSolidRect(area_);

  // Write on Button
  vec2 string_loc = area_.getCenter() - vec2(0, kFontSize/2);
  ci::gl::drawStringCentered(message_, string_loc, Color("white"),
                             Font(kFontStyle, kFontSize));
}

const string &Button::GetMessage() const {
  return message_;
}

} // namespace kaleidoscope