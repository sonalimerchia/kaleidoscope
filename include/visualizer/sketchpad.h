#include "core/stroke.h"
#include <glm/glm.hpp>

#ifndef FINAL_PROJECT_SONALIMERCHIA_INCLUDE_SKETCHPAD_H_
#define FINAL_PROJECT_SONALIMERCHIA_INCLUDE_SKETCHPAD_H_

namespace kaleidoscope {
namespace visualizer {
class Sketchpad {
 public:
  void draw(const std::vector<stroke> &strokes);
  void draw(const stroke &stroke);

  void SetBackground(const ci::Color &color);
  void SetCenter(const glm::vec2 &center);
  void SetNumSectors(size_t num_sectors);

 private:
  ci::Color background_;
  glm::vec2 center_;
  size_t num_sectors_;
};
}
}

#endif //FINAL_PROJECT_SONALIMERCHIA_INCLUDE_SKETCHPAD_H_
