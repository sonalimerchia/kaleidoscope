#include "core/stroke.h"
#include "core/stroke_maker.h"
#include <glm/glm.hpp>

#ifndef KALEIDOSCOPE_INCLUDE_SKETCHPAD_H_
#define KALEIDOSCOPE_INCLUDE_SKETCHPAD_H_

namespace kaleidoscope {

namespace visualizer {

class Sketchpad {
 public:
  Sketchpad();


  /**
   * Clear the current sketchpad and draw all the strokes passed in
   * @param strokes the strokes to be drawn
   */
  void ClearAndDraw();

  void DrawCurrentStroke();

  /**
   * Draw the stroke passed in without clearing the current sketchpad
   * @param stroke the stroke to be drawn
   */
  void DrawStroke(const stroke &stroke);

  /**
   * Set the background of the sketchpad to the color passed in
   * @param color the new color of the sketchpad
   */
  void SetBackground(const ci::Color &color);

  void MouseUp();

  void MouseDragged(const glm::ivec2 &loc);

  void MouseDown(const glm::ivec2 &loc);

  void Clear();

  void SetBrushSize(size_t brush_size);

  void ChangeDrawMode();

 private:
  ci::Color background_;
  std::vector<stroke> strokes_;
  StrokeMaker maker_;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_SKETCHPAD_H_
