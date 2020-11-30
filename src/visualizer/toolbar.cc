#include "cinder/gl/gl.h"
#include <visualizer/toolbar.h>
#include <core/constants.h>

namespace kaleidoscope {

namespace visualizer {

Toolbar::Toolbar() : position_(750, 0),
                     dimensions_(250, 750),
                     draw_mode_(position_, glm::vec2(dimensions_.x, 50),
                                    "Erase"),
                     brush_size_(glm::vec2(position_.x, 50),
                                 glm::vec2(dimensions_.x, 300), "Brush Size"),
                     save_(glm::vec2(position_.x, 700), glm::vec2(dimensions_.x, 50), "Save"){}

CommandType Toolbar::MouseClicked(const glm::ivec2 &loc) {
  if (draw_mode_.WasPressed(loc)) {
    std::string title = draw_mode_.GetMessage() == "Erase" ? "Draw" : "Erase";
    draw_mode_.SetMessage(title);
    return CommandType::DrawMode;

  } else if (brush_size_.WasEdited(loc)) {
    brush_size_.Slide(loc);
    return CommandType::BrushSize;

  } else if (save_.WasPressed(loc)) {
    return CommandType::Save;
  }

  return CommandType::None;
}

CommandType Toolbar::MouseDragged(const glm::ivec2 &loc) {
  if (brush_size_.WasEdited(loc)) {
    brush_size_.Slide(loc);
    return CommandType::BrushSize;
  }

  return CommandType::None;
}

size_t Toolbar::GetBrushSize() {
  float size = brush_size_.GetDegree()*(kMaxBrushSize - kMinBrushSize) + kMinBrushSize;
  return (size_t)(size);
}

void Toolbar::Draw() {
  ci::gl::lineWidth(1);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(position_, position_+dimensions_));
  draw_mode_.Draw();
  brush_size_.Draw();
  save_.Draw();
}

bool Toolbar::ContainsPoint(const glm::ivec2 &mouse_loc) {
  return mouse_loc.x >= position_.x &&
         mouse_loc.x <= position_.x + dimensions_.x &&
         mouse_loc.y >= position_.y &&
         mouse_loc.y <= position_.y + dimensions_.y;
}

} // namespace visualizer

} // namespace kaleidoscope