#include "core/stroke_maker.h"
#include "core/button.h"
#include "core/command_type.h"
#include "core/slider.h"

#ifndef KALEIDOSCOPE_INCLUDE_VISUALIZER_TOOLBAR_H_
#define KALEIDOSCOPE_INCLUDE_VISUALIZER_TOOLBAR_H_

namespace kaleidoscope {

namespace visualizer {

class Toolbar {
 public:
  static size_t kMaxBrushSize;
  static size_t kMinBrushSize;
  static StrokeMaker kTemp;

  Toolbar();

  bool ContainsPoint(const glm::ivec2 &loc);

  void Draw();

  CommandType MouseClicked(const glm::ivec2 &loc);

  CommandType MouseDragged(const glm::ivec2 &loc);

  size_t GetBrushSize();

 private:
  glm::vec2 position_;
  glm::vec2 dimensions_;

  Button draw_mode_;
  Button save_;
  Slider brush_size_;
};

}

}

#endif //KALEIDOSCOPE_INCLUDE_VISUALIZER_TOOLBAR_H_
