#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <visualizer/sketchpad.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307f

namespace kaleidoscope {
namespace visualizer {

void Sketchpad::draw(const std::vector<stroke> &strokes) {
  ci::gl::clear("white");
  for (const stroke &stroke : strokes) {
    draw(stroke);
  }
}

void Sketchpad::draw(const stroke &stroke) {
  ci::gl::color(stroke.color);
  for (const glm::vec2 &point : stroke.points) {
    float x = center_.x - point.x * cos(point.y);
    float y = center_.y + point.x * sin(point.y);
    ci::gl::drawSolidCircle(glm::vec2(x, y), (float) stroke.brush_size);
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
}