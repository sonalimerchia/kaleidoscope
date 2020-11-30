#include <cinder/gl/gl.h>

#include <visualizer/slider.h>
#include <core/constants.h>

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::string;

Slider::Slider(const vec2 &position, const vec2 &dimensions, const string &title) :
    position_(position), dimensions_(dimensions), message_(title) {
  degree_ = 0;
}

bool Slider::WasEdited(const ivec2 &mouse_loc) const {
  return position_.x + dimensions_.x/2 - kSliderTabHeight*2 <= mouse_loc.x &&
      mouse_loc.x <= position_.x + dimensions_.x/2 + kSliderTabHeight*2 &&
      position_.y + kSliderTabHeight + kFontSize <= mouse_loc.y &&
      mouse_loc.y <= position_.y + dimensions_.y;
}

void Slider::Draw() const {
  // Draw title/background of slider
  ci::gl::color(kButtonTextColor);
  ci::gl::drawSolidRect(ci::Rectf(position_, position_ + dimensions_));
  ci::gl::drawString(message_, position_, kButtonColor, ci::Font(kFontStyle, kFontSize));

  // Draw line of slider
  float bar_length = dimensions_.y - kFontSize;
  ci::gl::color(kButtonColor);
  ci::gl::drawLine(position_ + vec2(dimensions_.x/2, kFontSize + kSliderTabHeight),
                   position_ + vec2(dimensions_.x/2, dimensions_.y));

  // Draw tab of slider
  vec2 box_loc(dimensions_.x/2 - kSliderTabHeight*2,
               dimensions_.y - (degree_ * bar_length) - kSliderTabHeight);
  box_loc += position_;
  ci::gl::drawSolidRect(ci::Rectf(box_loc, box_loc + vec2(4*kSliderTabHeight, 2*kSliderTabHeight)));
}

float Slider::GetDegree() {
  return degree_;
}

void Slider::Slide(const glm::ivec2 &mouse_loc) {
  float total_height_of_slider = dimensions_.y - kFontSize - kSliderTabHeight;
  float current_loc_on_slider = mouse_loc.y - position_.y - kFontSize - kSliderTabHeight;
  degree_ = 1 - current_loc_on_slider / total_height_of_slider;
}

} // namespace visualizer

} // namespace kaleidoscope