#include <glm/glm.hpp>
#include <string>

#include "core/button.h"

#ifndef KALEIDOSCOPE_INCLUDE_CORE_SLIDER_H_
#define KALEIDOSCOPE_INCLUDE_CORE_SLIDER_H_

namespace kaleidoscope {

class Slider {
 public:
  Slider(const glm::vec2 &location, const glm::vec2 &dimensions, const std::string &title);

  bool WasEdited(const glm::ivec2 &mouse_loc) const;
  void Draw() const;
  float GetDegree();
  void Slide(const glm::ivec2 &mouse_loc);

 private:
  const glm::vec2 position_;
  const glm::vec2 dimensions_;
  std::string message_;
  float degree_;
};

}

#endif //KALEIDOSCOPE_INCLUDE_CORE_SLIDER_H_
