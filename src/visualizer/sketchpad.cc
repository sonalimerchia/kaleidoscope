#include "cinder/gl/gl.h"

#include <visualizer/sketchpad.h>

namespace kaleidoscope {
namespace visualizer {

void Sketchpad::draw(const std::vector<stroke> &strokes) {
  // Clear and draw all the strokes
  ci::gl::clear(background_);
  for (const stroke &stroke : strokes) {
    draw(stroke);
  }
}

void Sketchpad::draw(const stroke &stroke) {
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
    //TODO:: Quote from basicapp
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

}
}