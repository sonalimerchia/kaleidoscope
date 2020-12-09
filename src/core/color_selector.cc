#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#include <core/color_selector.h>
#include <visualizer/sketchpad.h>

namespace kaleidoscope {

namespace visualizer {

using ci::Color;
using ci::ColorAf;
using ci::Colorf;
using ci::Color8u;
using ci::ColorModel;

using ci::gl::Texture2d;
using ci::Surface;

using ci::gl::color;
using ci::gl::draw;
using ci::gl::drawLine;
using ci::gl::drawStrokedCircle;
using ci::gl::drawSolidRect;

using glm::ivec2;
using glm::vec2;

ColorSelector::ColorSelector(const ivec2 &position, const ivec2 &dimensions) :
  palette_area_(position.x + dimensions.x/8, position.y + dimensions.y/10,
                position.x + 7*dimensions.x/8, position.y + 5*dimensions.y/10),
  slider_area_(position.x + dimensions.x/8, position.y + 6*dimensions.y/10,
               position.x + 7*dimensions.x/8, position.y + 7*dimensions.y/10),
  color_display_area_(position.x + dimensions.x/8, position.y + 8*dimensions.y/10,
                      position.x + 7*dimensions.x/8, position.y + 9*dimensions.y/10) {

  // Create the surfaces for each gradient component
  palette_ = Surface(palette_area_.getWidth(), palette_area_.getHeight(), false);
  slider_ = Surface(slider_area_.getWidth(), 1, false);

  // Initialize default color
  color_ = Sketchpad::kDefaultDrawingColor;
  glm::vec3 hsv = color_.get(ColorModel::CM_HSV);
  hue_ = hsv.x;
  saturation_ = hsv.y;
  value_ = hsv.z;

  // Generate initial palettes
  RefreshPalette();
  RefreshSlider();
}

void ColorSelector::Draw() const {
  // Draw Gradient Components
  DrawHueSaturationPalette();
  DrawValueSlider();

  // Draw Color Display
  color(color_);
  drawSolidRect(color_display_area_);
}

const ColorA& ColorSelector::GetColor() const {
  return color_;
}
bool ColorSelector::WasEdited(const ivec2 &mouse_location) const {
  return palette_area_.contains(mouse_location) || slider_area_.contains(mouse_location);
}

void ColorSelector::ChangeColor(const ivec2 &mouse_location) {
  // Adjust Hue/Saturation and change Value Display accordingly
  if (palette_area_.contains(mouse_location)) {
    ChangeHueNSaturation(mouse_location);
    RefreshSlider();

    // Adjust Value and change Hue/Saturation Display accordingly
  } else if (slider_area_.contains(mouse_location)) {
    ChangeValue(mouse_location);
    RefreshPalette();
  }

  color_ = Colorf(ColorModel::CM_HSV, hue_, saturation_, value_);
}

void ColorSelector::DrawValueSlider() const {
  // Draw slider
  color(Color("white"));
  draw(Texture2d::create(slider_), slider_area_);

  // Draw line on slider to show current color
  color(Colorf(ColorModel::CM_HSV, 1-hue_, 1-saturation_, 1-value_));
  drawLine(vec2(slider_area_.getX1() + value_ * slider_area_.getWidth(), slider_area_.getY1()),
                   vec2(slider_area_.getX1() + value_ * slider_area_.getWidth(), slider_area_.getY2()));
}

void ColorSelector::DrawHueSaturationPalette() const {
  // Draw palette area
  color(Color("white"));
  draw(Texture2d::create(palette_), palette_area_);

  // Draw circle on slider to show current color
  color(Colorf(ColorModel::CM_HSV, 1-hue_, 1-saturation_, 1-value_));
  ivec2 relative_color_loc(hue_*palette_area_.getWidth(),
                                 (1-saturation_)*palette_area_.getHeight());
  drawStrokedCircle(relative_color_loc + palette_area_.getUL(),2);
}

void ColorSelector::ChangeHueNSaturation(const ivec2 &mouse_location) {
  // Get location on Hue/Saturation Palette
  vec2 relative_loc = mouse_location - palette_area_.getUL();

  // Adjust hue and saturation accordingly
  hue_ = relative_loc.x/palette_area_.getWidth();
  saturation_ = 1 - relative_loc.y/palette_area_.getHeight();
}

void ColorSelector::ChangeValue(const ivec2 &mouse_location) {
  // Get location on Value Slider
  vec2 relative_loc = mouse_location - slider_area_.getUL();

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
      ColorAf color(ColorModel::CM_HSV, hue, saturation, value_);
      palette_.setPixel(ivec2(x, y), color);
    }
  }
}

void ColorSelector::RefreshSlider() {
  // Go through each pixel
  for (float x = 0.0f; x <= slider_area_.getWidth(); x++) {
    float value = x/slider_area_.getWidth();

    // Make the pixel's hue/saturation components match the current color's HSV
    Color8u color(ColorModel::CM_HSV, hue_, saturation_, value);
    slider_.setPixel(ivec2(x, 0), color);
  }
}

} // namespace visualizer

} // namespace kaleidoscope