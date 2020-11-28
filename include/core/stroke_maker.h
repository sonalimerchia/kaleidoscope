#include <glm/glm.hpp>

#include "stroke.h"

//TODO:: Find pi in math.h

#ifndef KALEIDOSCOPE_INCLUDE_CORE_STROKE_MAKER_H_
#define KALEIDOSCOPE_INCLUDE_CORE_STROKE_MAKER_H_

namespace kaleidoscope {

class StrokeMaker {
 public:
  StrokeMaker();

  /**
   * @return the current stroke being created
   */
  const stroke& GetStroke() const;

  /**
   * Add a new point to the ongoing stroke, adding its corresponding location to
   * each of the sectors
   * @param point the original point
   */
  void AddPointToStroke(const glm::ivec2 &point);

  /**
   * Reset the stroke maker to clear current stroke and add the first point
   * @param point the first point where the stroke begins
   */
  void StartNewStroke(const glm::ivec2 &point);

  /**
   * Reset the stroke maker to clear current stroke
   */
  void clear();

  /**
   * Change the thickness of the stroke to the new size
   * @param new_size the new thickness of the current stroke
   */
  void SetBrushSize(size_t new_size);

  /**
   * Change the color of the current stroke
   * @param color the new color of the current stroke
   */
  void SetColor(const ci::Color &color);

  /**
   * Change the number of sectors the maker generates strokes for
   * @param new_num_sectors the new number of sectors
   */
  void SetNumSectors(size_t new_num_sectors);

  /**
   * Change the center of the current stroke maker
   * @param center the new center of the sketchpad
   */
  void SetCenter(const glm::vec2 &center);

  void ChangeMode();

 private:
  glm::vec2 center_;
  size_t num_sectors_;
  stroke current_stroke_;

  /**
   * Change the point based in the cartesian coordinate system to
   * a point based in polar coordinates
   * @param point the original point based in the cartesian coordinate system
   *        (same orientation as cinder's coordinate system where top left is 0,0)
   * @return the point based in the polar coordinate system (centered at origin)
   */
  glm::vec2 CartesianToPolar(const glm::ivec2 &point);
};

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_CORE_STROKE_MAKER_H_
