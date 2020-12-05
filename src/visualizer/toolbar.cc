#include <visualizer/toolbar.h>
#include <core/constants.h>

#include "cinder/gl/gl.h"

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::string;

Toolbar::Toolbar() : position_(kWindowHeight, 0),
                     dimensions_(kWindowWidth - kWindowHeight, kWindowHeight),
                     draw_mode_(position_, vec2(dimensions_.x, kButtonHeight),"Erase"),
                     brush_size_(vec2(position_.x, kButtonHeight),vec2(dimensions_.x/5.0f, kSliderHeight), "Brush Size"),
                     color_selector_(vec2(position_.x, kButtonHeight+kSliderHeight), vec2(dimensions_.x, 700 - kButtonHeight-kSliderHeight)),
                     save_(vec2(position_.x, kWindowHeight - kButtonHeight),vec2(dimensions_.x, kButtonHeight), "Save"){}

CommandType Toolbar::MouseClicked(const ivec2 &loc) {
  if (draw_mode_.WasPressed(loc)) {
    string title = draw_mode_.GetMessage() == "Erase" ? "Draw" : "Erase";
    draw_mode_.SetMessage(title);
    return CommandType::DrawMode;

  } else if (brush_size_.WasEdited(loc)) {
    brush_size_.Slide(loc);
    return CommandType::BrushSize;

  } else if (save_.WasPressed(loc)) {
    return CommandType::Save;

  } else if (color_selector_.WasEdited(loc)) {
    color_selector_.ChangeColor(loc);
    return CommandType::ColorChange;
  }

  return CommandType::None;
}

CommandType Toolbar::MouseDragged(const ivec2 &loc) {
  if (brush_size_.WasEdited(loc)) {
    brush_size_.Slide(loc);
    return CommandType::BrushSize;

  } else if (color_selector_.WasEdited(loc)) {
    color_selector_.ChangeColor(loc);
    return CommandType::ColorChange;
  }

  return CommandType::None;
}

size_t Toolbar::GetBrushSize() {
  float size = brush_size_.GetDegree()*(kMaxBrushSize - kMinBrushSize) + kMinBrushSize;
  return (size_t)(size);
}

void Toolbar::Draw() {
  ci::gl::lineWidth(1);

  // Draw toolbar background
  ci::gl::color(kButtonTextColor);
  ci::gl::drawSolidRect(ci::Rectf(position_, position_ + dimensions_));
  ci::gl::color(kButtonColor);
  ci::gl::drawStrokedRect(ci::Rectf(position_, position_+dimensions_));

  // Draw components on toolbar
  draw_mode_.Draw();
  brush_size_.Draw();
  save_.Draw();
  color_selector_.Draw();
}

bool Toolbar::ContainsPoint(const glm::ivec2 &mouse_loc) {
  return mouse_loc.x >= position_.x &&
         mouse_loc.x <= position_.x + dimensions_.x &&
         mouse_loc.y >= position_.y &&
         mouse_loc.y <= position_.y + dimensions_.y;
}
const ci::ColorA &Toolbar::GetColor() {
  return color_selector_.GetColor();
}

} // namespace visualizer

} // namespace kaleidoscope