#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <visualizer/sketchpad.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307f

namespace kaleidoscope {

void Sketchpad::clear() {
  ci::gl::clear(background_);
}

void Sketchpad::draw(const std::vector<stroke> &strokes) {
  for (const stroke &stroke : strokes) {
    draw(stroke);
  }
}

void Sketchpad::draw(const stroke &stroke) {
  ci::gl::color(stroke.color);
  for (const glm::vec2 &point : stroke.points) {
    float theta = point.y;
    for (size_t sector = 1; sector < num_sectors_; sector++) {
      glm::vec2(center_.x + point.x * cos(theta),
                center_.y + point.x * sin(theta));
      ci::gl::drawSolidCircle(point,
                              (float) stroke.brush_size);
      theta += 2*PI/num_sectors_;
    }
  }
}

void Sketchpad::SetBackground(const ci::Color &color) {
  background_ = color;
}

void Sketchpad::SetCenter(const glm::vec2 &center) {
  center_ = center;
}

void Sketchpad::SetNumSectors(size_t num_sectors) {
  num_sectors_ = num_sectors;
}

}