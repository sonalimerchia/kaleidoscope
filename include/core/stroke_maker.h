#include <glm/glm.hpp>

#include "stroke.h"

#ifndef IDEAL_GAS_INCLUDE_CORE_STROKE_MAKER_H_
#define IDEAL_GAS_INCLUDE_CORE_STROKE_MAKER_H_

namespace kaleidoscope {

class StrokeMaker {
 public:
  const stroke GetStroke() const;
  void AddPoint(const glm::ivec2 &point);
  void StartNewStroke(const glm::ivec2 &point);

  void SetBrushSize(size_t new_size);
  void SetColor(const ci::Color &color);
  void SetNumSectors(size_t new_num_sectors);
  void SetCenter(const glm::vec2 &center);

 private:
  glm::vec2 center_;
  std::vector<glm::vec2> points_;
  ci::Color color_;
  size_t brush_size_;
  size_t num_sectors_;
};

}

#endif //IDEAL_GAS_INCLUDE_CORE_STROKE_MAKER_H_
