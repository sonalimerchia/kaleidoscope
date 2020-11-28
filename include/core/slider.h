#include <glm/glm.hpp>
#include <string>

#include "core/button.h"

#ifndef KALEIDOSCOPE_INCLUDE_CORE_SLIDER_H_
#define KALEIDOSCOPE_INCLUDE_CORE_SLIDER_H_

namespace kaleidoscope {

class Slider : public Button {
 public:
  Slider(const glm::vec2 &location, const glm::vec2 &dimensions, const std::string &title);

  bool WasPressed(const glm::ivec2 &mouse_loc) const override;
  void Draw() const override;

 private:
  float degree_;
};

}

#endif //KALEIDOSCOPE_INCLUDE_CORE_SLIDER_H_
