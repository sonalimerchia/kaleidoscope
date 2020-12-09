#include <vector>

#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#include <visualizer/sketchpad.h>
#include <visualizer/kaleidoscope_app.h>

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using std::vector;
using ci::Color;

const size_t Sketchpad::kMinBrushSize = 1;
const size_t Sketchpad::kMaxBrushSize = 40;

const size_t Sketchpad::kMinSectors = 2;
const size_t Sketchpad::kMaxSectors = 50;

const Color Sketchpad::kDefaultBackgroundColor = Color("white");
const Color Sketchpad::kDefaultDrawingColor = Color("blue");

const int Sketchpad::kRefreshConstant = 10;

Sketchpad::Sketchpad() {
  // Set up pad
  refresher_ = kRefreshConstant;
  background_ = kDefaultBackgroundColor;

  // Set up maker
  stroke_maker_.SetCenter(vec2(KaleidoscopeApp::kWindowHeight/2,
                               KaleidoscopeApp::kWindowHeight/2));
  stroke_maker_.SetBrushSize(kMinBrushSize);
  stroke_maker_.SetColor(kDefaultDrawingColor);
}

void Sketchpad::Draw() {
  // Clear and draw if needs to be refreshed
  if (refresher_ >= 0) {
    ClearAndDraw();
    refresher_--;

    // Just draw current stroke if doesn't need refreshing
  } else {
    DrawCurrentStroke();
  }
}

void Sketchpad::ClearAndDraw() {
  // Clear and draw all the strokes
  ci::gl::clear(background_);
  for (const stroke &stroke : strokes_) {
    DrawStroke(stroke);
  }
  DrawStroke(stroke_maker_.GetStroke());
}

void Sketchpad::DrawCurrentStroke() {
  DrawStroke(stroke_maker_.GetStroke());
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
      ci::gl::drawSolidCircle(point, 0.5f*stroke.brush_size);
    }
    ci::gl::end();
  }
}

void Sketchpad::MouseDown(const ivec2 &loc) {
  stroke_maker_.StartNewStroke(loc);
}

void Sketchpad::MouseDragged(const ivec2 &loc) {
  stroke_maker_.AddPointToStroke(loc);
}

void Sketchpad::MouseUp() {
  const stroke &new_stroke = stroke_maker_.GetStroke();

  // Add new stroke to pad, clear maker, and refresh pad
  if (new_stroke.points_by_sector.at(0).size() != 0) {
    strokes_.push_back(new_stroke);
    stroke_maker_.clear();
    refresher_ += kRefreshConstant;
  }
}

void Sketchpad::Clear() {
  if (strokes_.size() > 0) {
    // Clear current strokes, saving copy in case of undo
    history_.push_back(strokes_);
    strokes_.clear();
    stroke_maker_.clear();

    // Refresh the pad
    refresher_ += kRefreshConstant;
  }
}

void Sketchpad::SetBrushSize(size_t brush_size) {
  stroke_maker_.SetBrushSize(brush_size);
}

void Sketchpad::ChangeDrawMode() {
  stroke_maker_.ChangeMode();
}

void Sketchpad::ChangeNumSectors(int change) {
  // Only do change if there will be between 2 and 100 sectors afterwards
  if (change + stroke_maker_.GetNumSectors() <= kMinSectors-1 ||
      change + stroke_maker_.GetNumSectors() >= kMaxSectors) {
    return;
  }

  // Save the initial strokes before resetting the pad and maker
  vector<stroke> old_strokes = strokes_;
  Clear();
  stroke_maker_.SetNumSectors(stroke_maker_.GetNumSectors() + change);

  // Recalibrate old strokes
  for (const stroke &old : old_strokes) {
    if (old.points_by_sector.at(0).size() == 0) {
      continue;
    }

    // Set maker to old stroke's settings
    stroke_maker_.SetBrushSize(old.brush_size);
    stroke_maker_.SetColor(old.color);

    // Add all points from one sector in the old stroke to the maker
    stroke_maker_.StartNewStroke(old.points_by_sector.at(0).at(0));
    for (size_t index = 1; index < old.points_by_sector.at(0).size(); index++) {
      stroke_maker_.AddPointToStroke(old.points_by_sector.at(0).at(index));
    }

    // Push back the resultant stroke and clear the maker
    strokes_.push_back(stroke_maker_.GetStroke());
    strokes_.back().type = old.type;

    stroke_maker_.clear();
  }
}

void Sketchpad::SetBrushColor(const Color &color) {
  stroke_maker_.SetColor(color);
}

void Sketchpad::Undo() {
  // If there are no strokes currently drawn, try to undo the last clear
  if (strokes_.size() == 0 && history_.size() != 0) {
    strokes_ = history_.back();
    history_.pop_back();

    // If there strokes currently drawn, undo the last
  } else if (strokes_.size() != 0) {
    strokes_.pop_back();
  }

  // Refresh the pad
  refresher_+= kRefreshConstant;
}

} // namespace visualizer

} // namespace kaleidoscope