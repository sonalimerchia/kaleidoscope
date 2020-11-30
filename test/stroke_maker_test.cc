#include <catch2/catch.hpp>
#include <glm/glm.hpp>

#include <core/stroke.h>
#include <core/stroke_maker.h>

using glm::vec2;
using glm::ivec2;

using kaleidoscope::stroke;
using kaleidoscope::StrokeType;
using kaleidoscope::StrokeMaker;

vec2 roundToFive(const vec2 &original) {
  return vec2((int)(original.x*100000)/100000.0, (int)(original.y*100000)/100000.0);
}

TEST_CASE("Two sectors (min)") {
  StrokeMaker maker;
  maker.SetNumSectors(2);
  maker.SetCenter(vec2(5, 5));

  REQUIRE(maker.GetNumSectors() == 2);
  maker.StartNewStroke(ivec2(6, 6));
  maker.AddPointToStroke(ivec2(6, 5));

  const stroke &stroke = maker.GetStroke();
  REQUIRE(stroke.type == StrokeType::Draw);
  REQUIRE(stroke.points_by_sector.size() == 2);

  REQUIRE(stroke.points_by_sector.at(0).size() == 2);
  REQUIRE(stroke.points_by_sector.at(0).at(0) == vec2(4, 4));
  REQUIRE(stroke.points_by_sector.at(0).at(1) == vec2(4, 5));

  REQUIRE(stroke.points_by_sector.at(1).size() == 2);
  REQUIRE(stroke.points_by_sector.at(1).at(0) == vec2(6, 6));
  REQUIRE(stroke.points_by_sector.at(1).at(1) == vec2(6, 5));
}

TEST_CASE("Four sectors (even)") {
  StrokeMaker maker;
  maker.SetNumSectors(4);
  maker.SetCenter(vec2(5, 5));

  REQUIRE(maker.GetNumSectors() == 4);
  maker.StartNewStroke(ivec2(6, 6));
  maker.AddPointToStroke(ivec2(6, 5));

  const stroke &stroke = maker.GetStroke();
  REQUIRE(stroke.type == StrokeType::Draw);
  REQUIRE(stroke.points_by_sector.size() == 4);

  REQUIRE(stroke.points_by_sector.at(0).size() == 2);
  REQUIRE(stroke.points_by_sector.at(0).at(0) == vec2(4, 6));
  REQUIRE(stroke.points_by_sector.at(0).at(1) == vec2(5, 6));

  REQUIRE(stroke.points_by_sector.at(1).size() == 2);
  REQUIRE(stroke.points_by_sector.at(1).at(0) == vec2(6, 6));
  REQUIRE(stroke.points_by_sector.at(1).at(1) == vec2(6, 5));

  REQUIRE(stroke.points_by_sector.at(2).size() == 2);
  REQUIRE(stroke.points_by_sector.at(2).at(0) == vec2(6, 4));
  REQUIRE(stroke.points_by_sector.at(2).at(1) == vec2(5, 4));

  REQUIRE(stroke.points_by_sector.at(3).size() == 2);
  REQUIRE(stroke.points_by_sector.at(3).at(0) == vec2(4, 4));
  REQUIRE(stroke.points_by_sector.at(3).at(1) == vec2(4, 5));
}

TEST_CASE("Three sectors (odd)") {
  StrokeMaker maker;
  maker.SetNumSectors(3);
  maker.SetCenter(vec2(5, 5));

  REQUIRE(maker.GetNumSectors() == 3);
  maker.StartNewStroke(ivec2(6, 6));
  maker.AddPointToStroke(ivec2(6, 5));

  const stroke &stroke = maker.GetStroke();
  REQUIRE(stroke.type == StrokeType::Draw);
  REQUIRE(stroke.points_by_sector.size() == 3);

  REQUIRE(stroke.points_by_sector.at(0).size() == 2);
  REQUIRE(roundToFive(stroke.points_by_sector.at(0).at(0)) == vec2(3.63397, 5.36602));
  REQUIRE(roundToFive(stroke.points_by_sector.at(0).at(1)) == vec2(4.5, 5.86602));

  REQUIRE(stroke.points_by_sector.at(1).size() == 2);
  REQUIRE(roundToFive(stroke.points_by_sector.at(1).at(0)) == vec2(6, 6));
  REQUIRE(roundToFive(stroke.points_by_sector.at(1).at(1)) == vec2(6, 5));

  REQUIRE(stroke.points_by_sector.at(2).size() == 2);
  REQUIRE(roundToFive(stroke.points_by_sector.at(2).at(0)) == vec2(5.36602, 3.63397));
  REQUIRE(roundToFive(stroke.points_by_sector.at(2).at(1)) == vec2(4.5, 4.13397));
}

TEST_CASE("360 sectors (max)") {
  StrokeMaker maker;
  maker.SetNumSectors(360);
  maker.SetCenter(vec2(5, 5));

  REQUIRE(maker.GetNumSectors() == 360);
  maker.StartNewStroke(ivec2(1, 0));

  const stroke &stroke = maker.GetStroke();
  REQUIRE(stroke.type == StrokeType::Draw);
  REQUIRE(stroke.points_by_sector.size() == 360);
}