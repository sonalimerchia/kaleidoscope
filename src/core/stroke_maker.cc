#include <core/stroke_maker.h>
#include <algorithm>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307f

namespace kaleidoscope {

const stroke StrokeMaker::GetStroke() const {
  stroke new_stroke;
  new_stroke.brush_size = brush_size_;
  new_stroke.color = color_;
  new_stroke.points_by_sector = points_by_sector_;
  return new_stroke;
}

glm::vec2 StrokeMaker::CartesianToPolar(const glm::ivec2 &point) {
  glm::vec2 realigned_point = glm::vec2(point.x-center_.x, point.y-center_.y);

  // Translate point into polar coordinates
  double r = abs(glm::length(realigned_point));
  double theta = acos(realigned_point.x/r);
  theta *= (realigned_point.y > 0 ? -1 : 1);

  // Realign so connecting works well
  float sector_angle = 2*PI/num_sectors_;
  theta = sector_angle - theta;

  return glm::vec2((float)r, (float)theta);
}

void StrokeMaker::StartNewStroke(const glm::ivec2 &point) {
  clear();
  AddPointToStroke(point);
}

void StrokeMaker::SetBrushSize(size_t new_size) {
  brush_size_ = new_size;
}

void StrokeMaker::SetColor(const cinder::Color &color) {
  color_ = color;
}

void StrokeMaker::SetNumSectors(size_t new_num_sectors) {
  num_sectors_ = new_num_sectors;
  clear();
}

void StrokeMaker::SetCenter(const glm::vec2 &center) {
  center_ = center;
}

void StrokeMaker::AddPointToStroke(const glm::ivec2 &point) {
  const glm::vec2 &polar_point = CartesianToPolar(point);
  for (size_t sector = 0; sector < num_sectors_; sector++) {
    glm::vec2 polar(polar_point.x, polar_point.y + 2*sector*PI/num_sectors_);
    glm::vec2 cartesian(polar.x*cos(polar.y), polar.x*sin(polar.y));
    points_by_sector_.at(sector).push_back(center_ - cartesian);
  }
}

void StrokeMaker::clear() {
  points_by_sector_ = std::vector<std::vector<glm::vec2>>(num_sectors_);
}

}