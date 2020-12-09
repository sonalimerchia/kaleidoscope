#include <glm/glm.hpp>

#include "core/stroke_maker.h"
#include "core/command_type.h"

#include "core/button.h"
#include "core/slider.h"
#include "core/color_selector.h"

#ifndef KALEIDOSCOPE_INCLUDE_TOOLBAR_H_
#define KALEIDOSCOPE_INCLUDE_TOOLBAR_H_

namespace kaleidoscope {

namespace visualizer {

using glm::ivec2;

class Toolbar {

 public:
  /**
   * Construct a toolbar
   */
  Toolbar();

/**
   * Checks to see if the given point is contained within the toolbar
   * @param mouse_location the location being tested to see if it falls within the toolbar
   * @return true if the point is within the toolbar; false otherwise
   */
  bool ContainsPoint(const ivec2 &mouse_location) const;

  /**
   * Reacts as if the mouse was clicked at the given location
   * @param mouse_location the location where the mouse was clicked
   * @return the type of command evoked by the mouse activity
   */
  CommandType MouseClicked(const ivec2 &mouse_location);

  /**
   * Reacts as if the mouse was dragged at the given location
   * @param mouse_location the location where the mouse was dragged
   * @return the type of command evoked by the mouse activity
   */
  CommandType MouseDragged(const ivec2 &mouse_location);

  /**
   * Draws the toolbar
   */
  void Draw() const;

  /**
   * @return the brush size selected by slider activity within the toolbar calculated
   * using the minimum and maximum brush sizes given by Sketchpad
   */
  size_t GetBrushSize() const;

  const ci::ColorA& GetColor() const;

 private:
  const ci::Area area_;

  // Components on Toolbar
  Button draw_mode_;
  Button save_;
  Slider brush_size_;
  Button undo_;
  ColorSelector color_selector_;
  glm::vec2 brush_display_;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_TOOLBAR_H_
