#include "core/stroke.h"
#include <glm/glm.hpp>

#ifndef FINAL_PROJECT_SONALIMERCHIA_INCLUDE_SKETCHPAD_H_
#define FINAL_PROJECT_SONALIMERCHIA_INCLUDE_SKETCHPAD_H_

namespace kaleidoscope {

namespace visualizer {

class Sketchpad {
 public:
  /**
   * Clear the current sketchpad and draw all the strokes passed in
   * @param strokes the strokes to be drawn
   */
  void draw(const std::vector<stroke> &strokes);

  /**
   * Draw the stroke passed in without clearing the current sketchpad
   * @param stroke the stroke to be drawn
   */
  void draw(const stroke &stroke);

  /**
   * Set the background of the sketchpad to the color passed in
   * @param color the new color of the sketchpad
   */
  void SetBackground(const ci::Color &color);

 private:
  ci::Color background_;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //FINAL_PROJECT_SONALIMERCHIA_INCLUDE_SKETCHPAD_H_
