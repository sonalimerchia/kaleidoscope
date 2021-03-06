#include <cinder/gl/gl.h>
#include <visualizer/toolbar.h>

#include <visualizer/sketchpad.h>
#include <visualizer/kaleidoscope_app.h>

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::string;

Toolbar::Toolbar() :
  area_(KaleidoscopeApp::kWindowHeight, 0,
        KaleidoscopeApp::kWindowWidth, KaleidoscopeApp::kWindowHeight),

  draw_mode_(area_.getUL(),
             ivec2(area_.getWidth(), KaleidoscopeApp::kWindowHeight/8),
             "Erase"),

  brush_size_(area_.getUL() + ivec2(0, KaleidoscopeApp::kWindowHeight/8),
              ivec2(area_.getWidth()/5, 2*KaleidoscopeApp::kWindowHeight/8),
              "Brush Size"),

  color_selector_(area_.getUL() + ivec2(0, 3*KaleidoscopeApp::kWindowHeight/8),
                  ivec2(area_.getWidth(), 3*KaleidoscopeApp::kWindowHeight/8)),

  undo_(area_.getUL() + ivec2(0, 6*KaleidoscopeApp::kWindowHeight/8),
        ivec2(area_.getWidth(), KaleidoscopeApp::kWindowHeight/8),
        "Undo"),

  save_(area_.getUL() + ivec2(0, 7*KaleidoscopeApp::kWindowHeight/8),
        ivec2(area_.getWidth(), KaleidoscopeApp::kWindowHeight/8),
        "Save"),

  brush_display_(area_.getUL() + ivec2(3*area_.getWidth()/5, 2*KaleidoscopeApp::kWindowHeight/8)) {}

CommandType Toolbar::MouseClicked(const ivec2 &loc) {
  // Switch draw modes if erase/draw button clicked
  if (draw_mode_.WasPressed(loc)) {
    string title = draw_mode_.GetMessage() == "Erase" ? "Draw" : "Erase";
    draw_mode_.SetMessage(title);
    return CommandType::DrawMode;

    // Indicate brush size change if slider edited
  } else if (brush_size_.WasEdited(loc)) {
    brush_size_.Slide(loc);
    return CommandType::BrushSize;

    // Indicate save if save button is pressed
  } else if (save_.WasPressed(loc)) {
    return CommandType::Save;

    // Indicate undo last stroke/action if undo button clicked
  } else if (undo_.WasPressed(loc)) {
    return CommandType::Undo;

    // Indicate color change if selector edited
  } else if (color_selector_.WasEdited(loc)) {
      color_selector_.ChangeColor(loc);
      return CommandType::ColorChange;
  }

  return CommandType::None;
}

CommandType Toolbar::MouseDragged(const ivec2 &loc) {
  // Change brush size if slider edited
  if (brush_size_.WasEdited(loc)) {
    brush_size_.Slide(loc);
    return CommandType::BrushSize;

    // Change color if color selector edited
  } else if (color_selector_.WasEdited(loc)) {
    color_selector_.ChangeColor(loc);
    return CommandType::ColorChange;
  }

  return CommandType::None;
}

void Toolbar::Draw() const {
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

  ci::gl::color(color_selector_.GetColor());
  ci::gl::drawSolidCircle(brush_display_, GetBrushSize()/2.0f);
}

bool Toolbar::ContainsPoint(const ivec2 &mouse_loc) const {
  return area_.contains(mouse_loc);
}

size_t Toolbar::GetBrushSize() const {
  float size = brush_size_.GetDegree()*(Sketchpad::kMaxBrushSize - Sketchpad::kMinBrushSize);
  size += Sketchpad::kMinBrushSize;
  return (size_t)(size);
}

const ci::ColorA &Toolbar::GetColor() const {
  return color_selector_.GetColor();
}

} // namespace visualizer

} // namespace kaleidoscope