#include <glm/glm.hpp>
#include <catch2/catch.hpp>
#include <visualizer/slider.h>

using glm::vec2;
using glm::ivec2;
using kaleidoscope::visualizer::Slider;

// Line from 25 to 51 (y)
// Tab from 3 to 19 (x)

TEST_CASE("Slider corner cases") {
  Slider slider(vec2(1, 1), vec2(20, 50), "Corner");
  ivec2 click;
  float expected_degree;

  SECTION("Top-Left") {
    click = ivec2(3, 25);
    expected_degree = 1;
  }
  SECTION("Top-Right") {
    click = ivec2(19, 25);
    expected_degree = 1;
  }
  SECTION("Bottom-Left") {
    slider.Slide(ivec2(10, 25));

    click = ivec2(3, 51);
    expected_degree = 0;
  }
  SECTION("Bottom-Right") {
    slider.Slide(ivec2(10, 25));

    click = ivec2(19, 51);
    expected_degree = 0;
  }

  REQUIRE(slider.WasEdited(click));
  slider.Slide(click);
  REQUIRE(slider.GetDegree() == expected_degree);
}

TEST_CASE("Slider edge cases") {
  Slider slider(vec2(1, 1), vec2(20, 50), "Edges");
  ivec2 click;
  float expected_degree;

  SECTION("Top") {
    click = ivec2(10, 25);
    expected_degree = 1;
  }
  SECTION("Bottom") {
    slider.Slide(ivec2(10, 25));

    click = ivec2(10, 51);
    expected_degree = 0;
  }
  SECTION("Left") {
    click = ivec2(3, 38);
    expected_degree = 0.5f;
  }
  SECTION("Right") {
    click = ivec2(19, 38);
    expected_degree = 0.5f;
  }

  REQUIRE(slider.WasEdited(click));
  slider.Slide(click);
  REQUIRE(slider.GetDegree() == expected_degree);
}

TEST_CASE("Slider center cases") {
  Slider slider(vec2(1, 1), vec2(20, 50), "Center");
  ivec2 click = ivec2(10, 38);
  REQUIRE(slider.GetDegree() == 0);

  REQUIRE(slider.WasEdited(click));
  slider.Slide(click);
  REQUIRE(slider.GetDegree() == 0.5f);
}

TEST_CASE("Slider outside cases") {
  Slider slider(vec2(1, 1), vec2(20, 50), "Outside");
  ivec2 click;

  SECTION("On Block, Left") {
    click = ivec2(2, 38);
  }
  SECTION("On Block, Right") {
    click = ivec2(20, 38);
  }
  SECTION("Off Block") {
    click = ivec2(0, 0);
  }

  REQUIRE_FALSE(slider.WasEdited(click));
}