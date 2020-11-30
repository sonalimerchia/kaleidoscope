#include "cinder/gl/gl.h"

#include <core/constants.h>
#include <visualizer/sketchpad.h>

namespace kaleidoscope {

namespace visualizer {

Sketchpad::Sketchpad() {
  // Set up maker
  maker_.SetBrushSize(kMinBrushSize);
  maker_.SetColor(ci::Color("blue"));
  maker_.SetNumSectors(6);
  maker_.SetCenter(glm::vec2(kWindowHeight/2, kWindowHeight/2));
}

void Sketchpad::ClearAndDraw() {
  // Clear and draw all the strokes
  ci::gl::clear(background_);
  for (const stroke &stroke : strokes_) {
    DrawStroke(stroke);
  }
  DrawStroke(maker_.GetStroke());
}

void Sketchpad::DrawCurrentStroke() {
  DrawStroke(maker_.GetStroke());
}

void Sketchpad::DrawStroke(const stroke &stroke) {
  // Set the gl settings to the stroke's settings
  if (stroke.type == StrokeType::Draw) {
    ci::gl::color(stroke.color);
  } else {
    ci::gl::color(background_);
  }

  ci::gl::lineWidth((float)stroke.brush_size);
  // Draw all the sectors
  for (const std::vector<glm::vec2> &sector : stroke.points_by_sector) {
    // Draw lines between the two points to fix lagging issue
    ci::gl::begin(GL_LINE_STRIP);
    for (const glm::vec2 &point : sector) {
      ci::gl::vertex(point);
    }
    ci::gl::end();
  }
}

void Sketchpad::SetBackground(const ci::Color &color) {
  background_ = color;
}

void Sketchpad::MouseUp() {
  strokes_.push_back(maker_.GetStroke());
  maker_.clear();
}

void Sketchpad::MouseDragged(const glm::ivec2 &loc) {
  maker_.AddPointToStroke(loc);
}

void Sketchpad::MouseDown(const glm::ivec2 &loc) {
  maker_.StartNewStroke(loc);
}

void Sketchpad::Clear() {
  strokes_.clear();
  maker_.clear();

}

void Sketchpad::SetBrushSize(size_t brush_size) {
  maker_.SetBrushSize(brush_size);
}

void Sketchpad::ChangeDrawMode() {
  maker_.ChangeMode();
}

void Sketchpad::ChangeNumSectors(int change) {
  if (change + maker_.GetNumSectors() <=1) {
    return;
  }

  std::vector<stroke> old_strokes = strokes_;
  Clear();
  maker_.SetNumSectors(maker_.GetNumSectors() + change);

  for (const stroke &old : old_strokes) {
    if (old.points_by_sector.at(0).size() == 0) {
      continue;
    }

    maker_.SetBrushSize(old.brush_size);
    maker_.SetColor(old.color);
    maker_.StartNewStroke(old.points_by_sector.at(0).at(0));
    for (size_t index = 1; index < old.points_by_sector.at(0).size(); index++) {
      maker_.AddPointToStroke(old.points_by_sector.at(0).at(index));
    }
    strokes_.push_back(maker_.GetStroke());
    maker_.clear();
  }
}

} // namespace visualizer

} // namespace kaleidoscope