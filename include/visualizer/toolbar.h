#pragma once

#include <glm/glm.hpp>

#include "core/stroke_maker.h"
#include "core/command_type.h"

#include "button.h"
#include "slider.h"

#ifndef KALEIDOSCOPE_INCLUDE_TOOLBAR_H_
#define KALEIDOSCOPE_INCLUDE_TOOLBAR_H_

namespace kaleidoscope {

namespace visualizer {

class Toolbar {
 public:

  /**
   * Construct a toolbar
   */
  Toolbar();

  /**
   * Checks to see if the given point is contained within the toolbar
   * @param loc the location being tested to see if it falls within the toolbar
   * @return true if the point is within the toolbar; false otherwise
   */
  bool ContainsPoint(const glm::ivec2 &loc);

  /**
   * Draws the toolbar
   */
  void Draw();

  /**
   * Reacts as if the mouse was clicked at the given location
   * @param loc the location where the mouse was clicked
   * @return the type of command evoked by the mouse activity
   */
  CommandType MouseClicked(const glm::ivec2 &loc);


  /**
   * Reacts as if the mouse was dragged at the given location
   * @param loc the location where the mouse was dragged
   * @return the type of command evoked by the mouse activity
   */
  CommandType MouseDragged(const glm::ivec2 &loc);

  /**
   * @return the brush size selected by slider activity within the toolbar
   */
  size_t GetBrushSize();

 private:
  glm::vec2 position_;
  glm::vec2 dimensions_;

  Button draw_mode_;
  Button save_;
  Slider brush_size_;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_TOOLBAR_H_
