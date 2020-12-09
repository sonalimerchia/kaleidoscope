#include <algorithm>
#include <math.h>
#include <cinder/gl/gl.h>

#include <core/stroke_maker.h>

namespace kaleidoscope {

using glm::vec2;
using glm::ivec2;
using ci::Color;
using std::vector;
using std::pair;

const size_t StrokeMaker::kDefaultNumSectors = 6;

StrokeMaker::StrokeMaker() {
  current_stroke_.type = StrokeType::Draw;
  num_sectors_ = kDefaultNumSectors;
  clear();
}

const stroke& StrokeMaker::GetStroke() const {
  return current_stroke_;
}

void StrokeMaker::StartNewStroke(const ivec2 &point) {
  clear();
  AddPointToStroke(point);
}

void StrokeMaker::AddPointToStroke(const glm::ivec2 &point) {
  const pair<float, float> &polar_point = CartesianToPolar(point);
  double sector_angle = 2*M_PI/num_sectors_;

  // make one point in each sector
  for (size_t sector = 0; sector < num_sectors_; sector++) {
    double new_theta = polar_point.second - sector*sector_angle;
    vec2 cartesian(polar_point.first*cos(new_theta), polar_point.first*sin(new_theta));

    current_stroke_.points_by_sector.at(sector).push_back(center_ + cartesian);
  }
}

void StrokeMaker::clear() {
  current_stroke_.points_by_sector = vector<vector<vec2>>(num_sectors_);
}

void StrokeMaker::ChangeMode() {
  current_stroke_.type = current_stroke_.type == StrokeType::Draw ? StrokeType::Erase : StrokeType::Draw;
}

size_t StrokeMaker::GetNumSectors() const {
  return num_sectors_;
}

void StrokeMaker::SetCenter(const vec2 &center) {
  center_ = center;
}

void StrokeMaker::SetBrushSize(size_t new_size) {
  current_stroke_.brush_size = new_size;
}

void StrokeMaker::SetColor(const Color &color) {
  current_stroke_.color = color;
}

void StrokeMaker::SetNumSectors(size_t new_num_sectors) {
  num_sectors_ = new_num_sectors;
  clear();
}

pair<float, float> StrokeMaker::CartesianToPolar(const ivec2 &point) {
  vec2 realigned_point = vec2(point.x-center_.x, point.y-center_.y);

  // Translate point into polar coordinates
  double r = abs(length(realigned_point));
  double theta = acos(realigned_point.x/r);
  theta *= (realigned_point.y > 0 ? -1 : 1);

  // Realign so connecting works well
  double sector_angle = 2 * M_PI / num_sectors_;
  theta = sector_angle - theta;

  return pair<float, float>((float)(r), (float)(theta));
}

} // namespace kaleidoscope