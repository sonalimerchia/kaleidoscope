#include <core/stroke_maker.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307f

namespace kaleidoscope {

const stroke StrokeMaker::GetStroke() const {
  stroke new_stroke;
  new_stroke.brush_size = brush_size_;
  new_stroke.color = color_;
  new_stroke.points = points_;
  return new_stroke;
}

void StrokeMaker::AddPoint(const glm::ivec2 &point) {
  glm::vec2 realigned_point = glm::vec2(point.x-center_.x, point.y-center_.y);

  double r = abs(glm::length(realigned_point));
  double theta = acos(realigned_point.x/r);
  theta *= (realigned_point.y > 0 ? -1 : 1);
  double sector_angle = 2*PI/num_sectors_;
  while (theta < 0) {
    theta += sector_angle;
  }
  while (theta > sector_angle) {
    theta -= sector_angle;
  }

  points_.push_back(glm::vec2((float)r, (float)theta));
}

void StrokeMaker::StartNewStroke(const glm::ivec2 &point) {
  points_.clear();
}

void StrokeMaker::SetBrushSize(size_t new_size) {
  brush_size_ = new_size;
}

void StrokeMaker::SetColor(const cinder::Color &color) {
  color_ = color;
}

void StrokeMaker::SetNumSectors(size_t new_num_sectors) {
  num_sectors_ = new_num_sectors;
}

void StrokeMaker::SetCenter(const glm::vec2 &center) {
  center_ = center;
}

}