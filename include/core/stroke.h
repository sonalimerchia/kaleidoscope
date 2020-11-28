#include <vector>

#include "cinder/Color.h"

#ifndef KALEIDOSCOPE_INCLUDE_CORE_STROKE_H_
#define KALEIDOSCOPE_INCLUDE_CORE_STROKE_H_

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307f

namespace kaleidoscope {

enum StrokeType {
  Draw,
  Erase
};

struct stroke {
  StrokeType type;
  ci::Color color;
  size_t brush_size;
  std::vector<std::vector<glm::vec2>> points_by_sector;
};

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_CORE_STROKE_H_
