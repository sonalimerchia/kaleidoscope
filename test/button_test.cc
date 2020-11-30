#include <catch2/catch.hpp>
#include <glm/glm.hpp>
#include <visualizer/button.h>

using glm::vec2;
using glm::ivec2;
using kaleidoscope::visualizer::Button;

TEST_CASE("Button corner cases") {
  Button button(vec2(1, 1), vec2(10, 10), "Corners");

  SECTION("Top-Left") {
    REQUIRE(button.WasPressed(ivec2(1, 1)));
  }
  SECTION("Top-Right") {
    REQUIRE(button.WasPressed(ivec2(11, 1)));
  }
  SECTION("Bottom-Left") {
    REQUIRE(button.WasPressed(ivec2(1, 11)));
  }
  SECTION("Bottom-Right") {
    REQUIRE(button.WasPressed(ivec2(11, 11)));
  }
}

TEST_CASE("Button edge cases") {
  Button button(vec2(1, 1), vec2(10, 10), "Corners");

  SECTION("Top") {
    REQUIRE(button.WasPressed(ivec2(5, 1)));
  }
  SECTION("Bottom") {
    REQUIRE(button.WasPressed(ivec2(5, 11)));
  }
  SECTION("Left") {
    REQUIRE(button.WasPressed(ivec2(1, 5)));
  }
  SECTION("Right") {
    REQUIRE(button.WasPressed(ivec2(11, 5)));
  }
}

TEST_CASE("Button center cases") {
  Button button(vec2(1, 1), vec2(10, 10), "Center");

  SECTION("X Within button") {
    REQUIRE(button.WasPressed(ivec2(2, 2)));
    REQUIRE(button.WasPressed(ivec2(10, 2)));
    REQUIRE(button.WasPressed(ivec2(2, 10)));
    REQUIRE(button.WasPressed(ivec2(10, 10)));
  }

  SECTION("Center") {
    REQUIRE(button.WasPressed(ivec2(5, 5)));
  }
}

TEST_CASE("Button outside cases") {
  Button button(vec2(1, 1), vec2(10, 10), "Outside");

  SECTION("Above") {
    REQUIRE_FALSE(button.WasPressed(vec2(5, 0)));
  }
  SECTION("Below") {
    REQUIRE_FALSE(button.WasPressed(vec2(5, 12)));
  }
  SECTION("Left") {
    REQUIRE_FALSE(button.WasPressed(vec2(0, 5)));
  }
  SECTION("Right") {
    REQUIRE_FALSE(button.WasPressed(vec2(12, 5)));
  }
  SECTION("Above/Right") {
    REQUIRE_FALSE(button.WasPressed(vec2(0, 12)));
  }
  SECTION("Below/Left") {
    REQUIRE_FALSE(button.WasPressed(vec2(12, 0)));
  }
}