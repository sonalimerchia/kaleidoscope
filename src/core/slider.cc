#include <cinder/gl/gl.h>

#include <core/slider.h>
#include <core/button.h>

namespace kaleidoscope {

using glm::vec2;
using glm::ivec2;
using std::string;

using ci::Rectf;
using ci::Color;
using ci::Font;

const size_t Slider::kSliderTabHeight = 6;

Slider::Slider(const vec2 &position, const vec2 &dimensions, const string &title) :
    total_area_(position, position + dimensions), message_(title),
    slider_area_((int)(position.x + dimensions.x/2.0f - kSliderTabHeight*2),
                 (int)(position.y + kSliderTabHeight + Button::kFontSize),
                 (int)(position.x + dimensions.x/2.0f + kSliderTabHeight*2.0f),
                 (int)(position.y + dimensions.y)){
  degree_ = 0;
}

bool Slider::WasEdited(const ivec2 &mouse_loc) const {
  return slider_area_.contains(mouse_loc);
}

void Slider::Draw() const {
  // Draw title/background of slider
  ci::gl::color(Color("white"));
  ci::gl::drawSolidRect(total_area_);
  ci::gl::drawString(message_, total_area_.getUL(), Color("black"),
                     Font(Button::kFontStyle, Button::kFontSize));

  // Draw line of slider
  ci::gl::color(Color("black"));
  ci::gl::drawLine(vec2(slider_area_.getCenter().x, slider_area_.getY1()),
                   vec2(slider_area_.getCenter().x, slider_area_.getY2()));

  // Draw tab to show current value of slider
  float box_ul_y = slider_area_.getY2() - degree_ * slider_area_.getHeight();
  ci::gl::drawSolidRect(Rectf(vec2(slider_area_.getX1(), box_ul_y - kSliderTabHeight),
                        vec2(slider_area_.getX2(), box_ul_y + kSliderTabHeight)));
}

float Slider::GetDegree() const {
  return degree_;
}

void Slider::Slide(const ivec2 &mouse_loc) {
  float current_tab_loc = (float)(mouse_loc.y - slider_area_.getY1());
  degree_ = 1 - current_tab_loc / slider_area_.getHeight();

  // Ensure degree doesn't go above 1 or below 0
  degree_ = std::min(degree_, 1.0f);
  degree_ = std::max(degree_, 0.0f);
}

} // namespace kaleidoscope