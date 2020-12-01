#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#include <visualizer/color_selector.h>
#include <core/constants.h>

namespace kaleidoscope {

namespace visualizer {

ColorSelector::ColorSelector(const glm::vec2 &position,
                             const glm::vec2 &dimensions) {
  int vertical_margins = (int)(dimensions.y/10);
  int horizontal_margins = (int)(dimensions.x/8);
  int x = (int)(position.x);
  int y = (int)(position.y);

  hue_saturation_selector_ = ci::Area(x + horizontal_margins, y + vertical_margins,
                                      x + 7*horizontal_margins,y + 5*vertical_margins);
  value_slider_ = ci::Area(x + horizontal_margins, y + 6*vertical_margins,
                           x + 7*horizontal_margins, y + 7*vertical_margins);
  color_display_ = ci::Area(x + horizontal_margins, y + 8*vertical_margins,
                            x + 7*horizontal_margins, y + 9*vertical_margins);

  color_ = kDefaultDrawingColor;

  std::tuple<float, float, float> hsv = RGBtoHSV(color_.r, color_.g, color_.b);
  hue_ = std::get<0>(hsv);
  saturation_ = std::get<1>(hsv);
  value_ = std::get<2>(hsv);
}

void ColorSelector::Draw() const {
  DrawHueSaturationSelector();
  DrawValueSlider();

  ci::gl::color(color_);
  ci::gl::drawSolidRect(color_display_);
}

const ci::Color& ColorSelector::GetColor() const {
  return color_;
}
bool ColorSelector::WasEdited(const glm::ivec2 &mouse_location) const {
  return hue_saturation_selector_.contains(mouse_location) || value_slider_.contains(mouse_location);
}

void ColorSelector::ChangeColor(const glm::ivec2 &mouse_loc) {
  if (hue_saturation_selector_.contains(mouse_loc)) {
    ChangeHS(mouse_loc);
  } else if (value_slider_.contains(mouse_loc)) {
    ChangeV(mouse_loc);
  }

  std::tuple<float, float, float> rgb = HSVtoRGB(hue_, saturation_, value_);
  color_ = ci::Colorf(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
}

void ColorSelector::DrawValueSlider() const {
  for (float x = 0.0f; x <= value_slider_.getWidth(); x++) {
    float v = x/value_slider_.getWidth();

    std::tuple<float, float, float> rgb = HSVtoRGB(hue_, saturation_, v);
    ci::gl::color(ci::Colorf(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb)));
    ci::gl::drawLine(glm::vec2(value_slider_.getX1()+x, value_slider_.getY1()),
                     glm::vec2(value_slider_.getX1()+x, value_slider_.getY2()));
  }
}

void ColorSelector::DrawHueSaturationSelector() const {
  for (float x = 0.0f; x <= hue_saturation_selector_.getWidth(); x++) {
    float h = x/hue_saturation_selector_.getWidth() * 360;
    for (float y = 0.0f; y <= hue_saturation_selector_.getHeight(); y++) {
      float s = 1 - y/hue_saturation_selector_.getHeight();

      std::tuple<float, float, float> rgb = HSVtoRGB(h, s, value_);
      ci::gl::color(ci::Colorf(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb)));
      ci::gl::drawLine(glm::ivec2(x, y) + hue_saturation_selector_.getUL(),
                       glm::ivec2(x + hue_saturation_selector_.getX1(), hue_saturation_selector_.getY2()));
    }
  }
}

void ColorSelector::ChangeHS(const glm::ivec2 &mouse_location) {
  glm::vec2 relative_loc = mouse_location - hue_saturation_selector_.getUL();
  hue_ = relative_loc.x/hue_saturation_selector_.getWidth() * 360;
  saturation_ = 1 - relative_loc.y/hue_saturation_selector_.getHeight();
}

void ColorSelector::ChangeV(const glm::ivec2 &mouse_location) {
  glm::vec2 relative_loc = mouse_location - value_slider_.getUL();
  value_ = relative_loc.x/value_slider_.getWidth();
}

std::tuple<float, float, float> ColorSelector::RGBtoHSV(float r, float g, float b) const {
  float rp = r/255;
  float gp = g/255;
  float bp = b/255;
  float cmax = std::max(rp, std::max(gp, bp));
  float cmin = std::min(rp, std::min(gp, bp));
  float delta = cmax - cmin;

  float h;
  float s = cmax == 0 ? 0 : delta/cmax;
  float v = cmax;

  if (delta == 0) {
    h = 0;
  } else if (cmax == rp) {
    h = 60.0f * fmod(((gp-bp)/delta), 6.0f);
  } else if (cmax == gp) {
    h = 60.0f * ((bp-rp)/delta + 2.0f);
  } else {
    h = 60.0f * ((rp-gp)/delta + 4.0f);
  }

  return std::tuple<float, float, float>(std::min(360.0f, h), std::min(1.0f, s), std::min(1.0f, v));
}

std::tuple<float, float, float> ColorSelector::HSVtoRGB(float h, float s, float v) const {
  float c = v * s;
  float x = c * (1.0f - abs(fmod(h/60.0f, 2.0f) - 1.0f));
  float m = v - c;

  float r = m;
  float b = m;
  float g = m;

  if (0 <= h && h < 60) {
    r += c;
    g += x;
  } else if (60 <= h && h < 120) {
    r += x;
    g += c;
  } else if (120 <= h && h < 180) {
    g += c;
    b += x;
  } else if (180 <= h && h < 240) {
    g += x;
    b += c;
  } else if (240 <= h && h < 300) {
    r += x;
    b += c;
  } else if (300 <= h && h <= 360) {
    r += c;
    b += x;
  }

  r *= 255;
  g *= 255;
  b *= 255;

  return std::tuple<float, float, float>(std::min(255.0f, r), std::min(255.0f, g), std::min(255.0f, b));
}

} // namespace visualizer

} // namespace kaleidoscope