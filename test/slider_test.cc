#include <glm/glm.hpp>
#include <catch2/catch.hpp>
#include <core/slider.h>

using glm::vec2;
using glm::ivec2;
using kaleidoscope::Slider;

float roundToFivePlaces(float original) {
  return (int)(100000*original)/100000.0f;
}

TEST_CASE("Slider corner cases") {
  Slider slider(vec2(1, 1), vec2(30, 50), "Corner");
  ivec2 click;
  float expected_degree;

  SECTION("Top-Left") {
    click = ivec2(5, 37);
    expected_degree = 1;
  }
  SECTION("Top-Right") {
    click = ivec2(27, 37);
    expected_degree = 1;
  }
  SECTION("Bottom-Left") {
    slider.Slide(ivec2(27, 37));

    click = ivec2(5, 50);
    expected_degree = 0.07142f;
  }
  SECTION("Bottom-Right") {
    slider.Slide(ivec2(27, 37));

    click = ivec2(27, 50);
    expected_degree = 0.07142f;
  }

  REQUIRE(slider.WasEdited(click));
  slider.Slide(click);
  REQUIRE(roundToFivePlaces(slider.GetDegree()) == expected_degree);
}

TEST_CASE("Slider edge cases") {
  Slider slider(vec2(1, 1), vec2(30, 50), "Edges");
  ivec2 click;
  float expected_degree;

  SECTION("Top") {
    click = ivec2(16, 37);
    expected_degree = 1;
  }
  SECTION("Bottom") {
    slider.Slide(ivec2(16, 25));

    click = ivec2(16, 50);
    expected_degree = 0.07142f;
  }
  SECTION("Left") {
    click = ivec2(27, 44);
    expected_degree = 0.5f;
  }
  SECTION("Right") {
    click = ivec2(4, 44);
    expected_degree = 0.5f;
  }

  REQUIRE(slider.WasEdited(click));
  slider.Slide(click);
  REQUIRE(roundToFivePlaces(slider.GetDegree()) == expected_degree);
}

TEST_CASE("Slider center cases") {
  Slider slider(vec2(1, 1), vec2(30, 50), "Center");
  REQUIRE(slider.GetDegree() == 0.0f);

  ivec2 click = ivec2(16, 44);
  REQUIRE(slider.WasEdited(click));
  slider.Slide(click);
  REQUIRE(slider.GetDegree() == 0.5f);
}

TEST_CASE("Slider outside cases") {
  Slider slider(vec2(1, 1), vec2(30, 50), "Outside");
  ivec2 click;

  SECTION("On Block, Left") {
    click = ivec2(2, 44);
  }
  SECTION("On Block, Right") {
    click = ivec2(28, 44);
  }
  SECTION("Off Block") {
    click = ivec2(0, 0);
  }

  REQUIRE_FALSE(slider.WasEdited(click));
}