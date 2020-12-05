#include <glm/glm.hpp>

#include "core/stroke_maker.h"
#include "core/command_type.h"

#include "core/button.h"
#include "core/slider.h"
#include "core/color_selector.h"
#include "core/constants.h"

#ifndef KALEIDOSCOPE_INCLUDE_TOOLBAR_H_
#define KALEIDOSCOPE_INCLUDE_TOOLBAR_H_

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;

class Toolbar {

 public:
  /**
   * Construct a toolbar
   */
  Toolbar(float vertical_unit = kWindowHeight/8);

  /**
   * Checks to see if the given point is contained within the toolbar
   * @param loc the location being tested to see if it falls within the toolbar
   * @return true if the point is within the toolbar; false otherwise
   */
  bool ContainsPoint(const ivec2 &loc);

  /**
   * Draws the toolbar
   */
  void Draw();

  /**
   * Reacts as if the mouse was clicked at the given location
   * @param loc the location where the mouse was clicked
   * @return the type of command evoked by the mouse activity
   */
  CommandType MouseClicked(const ivec2 &loc);


  /**
   * Reacts as if the mouse was dragged at the given location
   * @param loc the location where the mouse was dragged
   * @return the type of command evoked by the mouse activity
   */
  CommandType MouseDragged(const ivec2 &loc);

  /**
   * @return the brush size selected by slider activity within the toolbar
   */
  size_t GetBrushSize();

  const ci::ColorA& GetColor();

 private:
  vec2 position_;
  vec2 dimensions_;
  const ci::Area area_;

  Button draw_mode_;
  Button save_;
  Slider brush_size_;
  Button undo_;
  ColorSelector color_selector_;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_TOOLBAR_H_
