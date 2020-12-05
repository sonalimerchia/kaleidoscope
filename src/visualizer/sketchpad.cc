#include <vector>
#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#include <core/constants.h>
#include <visualizer/sketchpad.h>

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::vector;
using ci::Color;

Sketchpad::Sketchpad() {
  maker_.SetCenter(vec2(kWindowHeight/2, kWindowHeight/2));
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
  for (const vector<vec2> &sector : stroke.points_by_sector) {
    // Draw lines between the two points to fix lagging issue
    ci::gl::begin(GL_LINE_STRIP);
    for (const vec2 &point : sector) {
      ci::gl::vertex(point);
      ci::gl::drawSolidCircle(point, stroke.brush_size/2.0f);
    }
    ci::gl::end();
  }
}

void Sketchpad::MouseDown(const ivec2 &loc) {
  maker_.StartNewStroke(loc);
}

void Sketchpad::MouseDragged(const ivec2 &loc) {
  maker_.AddPointToStroke(loc);
}

void Sketchpad::MouseUp() {
  strokes_.push_back(maker_.GetStroke());
  maker_.clear();
}

void Sketchpad::SetBackground(const Color &color) {
  background_ = color;
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
  // Only do change if there will be between 2 and 360 sectors afterwards
  if (change + maker_.GetNumSectors() <= 1 || change + maker_.GetNumSectors() >= 360) {
    return;
  }

  // Save the initial strokes before resetting the pad and maker
  vector<stroke> old_strokes = strokes_;
  Clear();
  maker_.SetNumSectors(maker_.GetNumSectors() + change);

  // Recalibrate old strokes
  for (const stroke &old : old_strokes) {
    if (old.points_by_sector.at(0).size() == 0) {
      continue;
    }

    // Set maker to old stroke's settings
    maker_.SetBrushSize(old.brush_size);
    maker_.SetColor(old.color);

    // Add all points from one sector in the old stroke to the maker
    maker_.StartNewStroke(old.points_by_sector.at(0).at(0));
    for (size_t index = 1; index < old.points_by_sector.at(0).size(); index++) {
      maker_.AddPointToStroke(old.points_by_sector.at(0).at(index));
    }

    // Push back the resultant stroke and clear the maker
    strokes_.push_back(maker_.GetStroke());
    maker_.clear();
  }
}
void Sketchpad::SetColor(const ci::Color &color) {
  maker_.SetColor(color);
}

} // namespace visualizer

} // namespace kaleidoscope