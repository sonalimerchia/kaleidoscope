#include <glm/glm.hpp>
#include <vector>

#include "core/stroke.h"
#include "core/stroke_maker.h"

#ifndef KALEIDOSCOPE_INCLUDE_SKETCHPAD_H_
#define KALEIDOSCOPE_INCLUDE_SKETCHPAD_H_

namespace kaleidoscope {

namespace visualizer {

using ci::Color;
using glm::ivec2;
using std::vector;

class Sketchpad {
 public:
  static const size_t kMinBrushSize;
  static const size_t kMaxBrushSize;
  static const ci::Color kDefaultBackgroundColor;
  static const ci::Color kDefaultDrawingColor;
  static const size_t kMinSectors;
  static const size_t kMaxSectors;
  static const int kRefreshConstant;

  Sketchpad();

  void Draw();
  /**
   * Clear the current sketchpad and draw all the strokes passed in
   * @param strokes the strokes to be drawn
   */
  void ClearAndDraw();

  /**
   * Draw the stroke currently being generated by the stroke maker
   */
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
  void SetBackground(const Color &color);

  /**
   * React as if the mouse was lifted up
   */
  void MouseUp();

  /**
   * React as if the mouse was dragged across the sketchpad
   * @param mouse_location the location of the mouse as it is dragged
   */
  void MouseDragged(const ivec2 &mouse_location);

  /**
   * React as if the mouse just pressed down on the sketchpad
   * @param mouse_location the location of the mouse as it is pressed down
   */
  void MouseDown(const ivec2 &mouse_location);

  /**
   * Clear the sketchpad such that next time ClearAndDraw() is called, the current strokes
   * will be gone
   */
  void Clear();

  /**
   * Change the brush size to the new size
   * @param brush_size the new brush size
   */
  void SetBrushSize(size_t brush_size);

  /**
   * Toggle the draw mode such that if it was drawing it starts erasing or if it
   * was erasing, it will now draw
   */
  void ChangeDrawMode();

  /**
   * Recalibrate the strokes on the sketchpad such that there is a new number of sectors
   * @param change +1 or -1 to add or remove a sector accordingly
   */
  void ChangeNumSectors(int change);

  void SetColor(const ci::Color &color);

  void Undo();

 private:
  Color background_;
  vector<stroke> strokes_;
  vector<vector<stroke>> history_;
  StrokeMaker stroke_maker_;

  int refresher_;
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_SKETCHPAD_H_
