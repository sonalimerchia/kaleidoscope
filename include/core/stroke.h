#include <vector>

#include "cinder/Color.h"

#ifndef IDEAL_GAS_INCLUDE_CORE_STROKE_H_
#define IDEAL_GAS_INCLUDE_CORE_STROKE_H_

namespace kaleidoscope {

struct stroke {
  ci::Color color;
  size_t brush_size;
  std::vector<std::vector<glm::vec2>> points_by_sector;
};

}

#endif //IDEAL_GAS_INCLUDE_CORE_STROKE_H_
