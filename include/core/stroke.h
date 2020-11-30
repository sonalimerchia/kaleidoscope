#include <vector>

#include "cinder/Color.h"

#ifndef KALEIDOSCOPE_INCLUDE_CORE_STROKE_H_
#define KALEIDOSCOPE_INCLUDE_CORE_STROKE_H_

namespace kaleidoscope {

using std::vector;
using ci::Color;
using glm::vec2;

enum StrokeType {
  Draw,
  Erase,
  Clear
};

struct stroke {
  StrokeType type;
  Color color;
  size_t brush_size;
  vector<vector<vec2>> points_by_sector;
};

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_CORE_STROKE_H_
