#include <visualizer/toolbar.h>
#include <core/constants.h>
#include <cinder/gl/gl.h>

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::string;

Toolbar::Toolbar(float vertical_unit) :
  area_(kWindowHeight, 0, kWindowWidth, kWindowHeight),

  draw_mode_(area_.getUL(),
             glm::ivec2(area_.getWidth(), vertical_unit),
             "Erase"),

  brush_size_(area_.getUL() + glm::ivec2(0, vertical_unit),
              glm::ivec2(area_.getWidth()/5, 2*vertical_unit),
              "Brush Size"),

  color_selector_(area_.getUL() + glm::ivec2(0, 3*vertical_unit),
                  glm::ivec2(area_.getWidth(), 3*vertical_unit)),

  undo_(area_.getUL() + glm::ivec2(0, 6*vertical_unit),
        glm::ivec2(area_.getWidth(), vertical_unit),
        "Undo"),

  save_(area_.getUL() + glm::ivec2(0, 7*vertical_unit),
        glm::ivec2(area_.getWidth(), vertical_unit),
        "Save") {}

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

  } else if (undo_.WasPressed(loc)) {
    return CommandType::Undo;

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
  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(area_);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(area_);

  // Draw components on toolbar
  draw_mode_.Draw();
  brush_size_.Draw();
  undo_.Draw();
  save_.Draw();
  color_selector_.Draw();
}

bool Toolbar::ContainsPoint(const glm::ivec2 &mouse_loc) {
  return area_.contains(mouse_loc);
}
const ci::ColorA &Toolbar::GetColor() {
  return color_selector_.GetColor();
}

} // namespace visualizer

} // namespace kaleidoscope