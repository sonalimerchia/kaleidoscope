#include <glm/glm.hpp>
#include "cinder/gl/gl.h"

#ifndef KALEIDOSCOPE_INCLUDE_VISUALIZER_COLOR_SELECTOR_H_
#define KALEIDOSCOPE_INCLUDE_VISUALIZER_COLOR_SELECTOR_H_

namespace kaleidoscope {

namespace visualizer {

class ColorSelector {
 public:
  ColorSelector(const glm::vec2 &position, const glm::vec2 &dimensions);
  void Draw() const;
  const ci::Color& GetColor() const;
  bool WasEdited(const glm::ivec2 &mouse_loc) const;
  void ChangeColor(const glm::ivec2 &mouse_loc);

 private:
  ci::Area hue_saturation_selector_;
  ci::Area value_slider_;
  ci::Area color_display_;

  ci::Color color_;

  float hue_;
  float saturation_;
  float value_;

  void DrawValueSlider() const;
  void DrawHueSaturationSelector() const;

  void ChangeHS(const glm::ivec2 &mouse_location);
  void ChangeV(const glm::ivec2 &mouse_location);

  std::tuple<float, float, float> RGBtoHSV(float r, float g, float b) const;
  std::tuple<float, float, float> HSVtoRGB(float h, float s, float v) const;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_VISUALIZER_COLOR_SELECTOR_H_
