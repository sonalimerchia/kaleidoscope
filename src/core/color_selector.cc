#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#include <core/color_selector.h>
#include <core/constants.h>

namespace kaleidoscope {

namespace visualizer {

ColorSelector::ColorSelector(const glm::vec2 &position,
                             const glm::vec2 &dimensions) {
  int vertical_unit = (int)(dimensions.y/10);
  int horizontal_unit = (int)(dimensions.x/8);
  int x = (int)(position.x);
  int y = (int)(position.y);

  // Set the locations for each component of the color selector
  palette_area_ = ci::Area(x + horizontal_unit, y + vertical_unit,
                           x + 7*horizontal_unit, y + 5*vertical_unit);
  slider_area_ = ci::Area(x + horizontal_unit, y + 6*vertical_unit,
                          x + 7*horizontal_unit, y + 7*vertical_unit);
  color_display_ = ci::Area(x + horizontal_unit, y + 8*vertical_unit,
                            x + 7*horizontal_unit, y + 9*vertical_unit);

  // Create the surfaces for each gradient component
  palette_ = ci::Surface(palette_area_.getWidth(), palette_area_.getHeight(), false);
  slider_ = ci::Surface(slider_area_.getWidth(), 1, false);

  // Initialize default color
  color_ = kDefaultDrawingColor;
  glm::vec3 hsv = color_.get(ci::ColorModel::CM_HSV);
  hue_ = hsv.x;
  saturation_ = hsv.y;
  value_ = hsv.z;

  // Generate initial palettes
  RefreshPalette();
  RefreshSlider();
}

void ColorSelector::Draw() {
  // Draw Gradient Components
  DrawHueSaturationPalette();
  DrawValueSlider();

  // Draw Color Display
  ci::gl::color(color_);
  ci::gl::drawSolidRect(color_display_);
}

const ci::ColorA& ColorSelector::GetColor() const {
  return color_;
}
bool ColorSelector::WasEdited(const glm::ivec2 &mouse_location) const {
  return palette_area_.contains(mouse_location) || slider_area_.contains(mouse_location);
}

void ColorSelector::ChangeColor(const glm::ivec2 &mouse_loc) {
  // Adjust Hue/Saturation and change Value Display accordingly
  if (palette_area_.contains(mouse_loc)) {
    ChangeHueNSaturation(mouse_loc);
    RefreshSlider();

    // Adjust Value and change Hue/Saturation Display accordingly
  } else if (slider_area_.contains(mouse_loc)) {
    ChangeValue(mouse_loc);
    RefreshPalette();
  }

  color_ = ci::Colorf(ci::ColorModel::CM_HSV, hue_, saturation_, value_);
}

void ColorSelector::DrawValueSlider() const {
  // Draw slider
  ci::gl::color(ci::Color("white"));
  ci::gl::draw(ci::gl::Texture2d::create(slider_), slider_area_);

  // Draw line on slider to show current color
  ci::gl::color(ci::Colorf(ci::ColorModel::CM_HSV, 1-hue_, 1-saturation_, 1-value_));
  ci::gl::drawLine(glm::vec2(slider_area_.getX1() + value_ * slider_area_.getWidth(), slider_area_.getY1()),
                   glm::vec2(slider_area_.getX1() + value_ * slider_area_.getWidth(), slider_area_.getY2()));
}

void ColorSelector::DrawHueSaturationPalette() const {
  // Draw palette area
  ci::gl::color(ci::Color("white"));
  ci::gl::draw(ci::gl::Texture2d::create(palette_), palette_area_);

  // Draw circle on slider to show current color
  ci::gl::color(ci::Colorf(ci::ColorModel::CM_HSV, 1-hue_, 1-saturation_, 1-value_));
  ci::gl::drawStrokedCircle(glm::ivec2(hue_*palette_area_.getWidth(),
                            (1-saturation_)*palette_area_.getHeight()) + palette_area_.getUL(),
                            2);
}

void ColorSelector::ChangeHueNSaturation(const glm::ivec2 &mouse_location) {
  // Get location on Hue/Saturation Palette
  glm::vec2 relative_loc = mouse_location - palette_area_.getUL();

  // Adjust hue and saturation accordingly
  hue_ = relative_loc.x/palette_area_.getWidth();
  saturation_ = 1 - relative_loc.y/palette_area_.getHeight();
}

void ColorSelector::ChangeValue(const glm::ivec2 &mouse_location) {
  // Get location on Value Slider
  glm::vec2 relative_loc = mouse_location - slider_area_.getUL();

  // Adjust value accordingly
  value_ = relative_loc.x/slider_area_.getWidth();
}

void ColorSelector::RefreshPalette() {
  // Go through each pixel
  for (float x = 0.0f; x <= palette_area_.getWidth(); x++) {
    float hue = x/palette_area_.getWidth();
    for (float y = 0.0f; y <= palette_area_.getHeight(); y++) {
      float saturation = 1 - y/palette_area_.getHeight();

      // Make the pixel's value component matches the current color's HSV
      ci::ColorAf color(ci::ColorModel::CM_HSV, hue, saturation, value_);
      palette_.setPixel(glm::ivec2(x, y), color);
    }
  }
}

void ColorSelector::RefreshSlider() {
  // Go through each pixel
  for (float x = 0.0f; x <= slider_area_.getWidth(); x++) {
    float value = x/slider_area_.getWidth();

    // Make the pixel's hue/saturation components match the current color's HSV
    ci::Color8u color(ci::ColorModel::CM_HSV, hue_, saturation_, value);
    slider_.setPixel(glm::ivec2(x, 0), color);
  }
}

} // namespace visualizer

} // namespace kaleidoscope