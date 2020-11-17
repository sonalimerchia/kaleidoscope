#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <visualizer/sketchpad.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307f

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
  ci::gl::color(stroke.color);
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

}
}