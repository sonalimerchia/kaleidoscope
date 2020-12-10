#include <catch2/catch.hpp>
#include <glm/glm.hpp>
#include <core/color_selector.h>
#include <iostream>

using kaleidoscope::ColorSelector;
using glm::ivec2;
using glm::vec3;

float roundToFourPlaces(float original) {
  return (int)(10000*original)/10000.0f;
}

vec3 roundToFourPlaces(const vec3 &original) {
  return vec3(roundToFourPlaces(original.x),
              roundToFourPlaces(original.y),
              roundToFourPlaces(original.z));
}

TEST_CASE("Editing hue/saturation palette") {
  ColorSelector selector(ivec2(1, 1), ivec2(80, 100));
  ivec2 click;
  vec3 expected_hsv;

  SECTION("Top") {
    click = ivec2(41, 11);
    expected_hsv = vec3(0.5f, 1.0f, 1.0f);
  }
  SECTION("Bottom") {
    click = ivec2(41, 50);
    expected_hsv = vec3(0.5f, 0.0249f, 1.0f);
  }
  SECTION("Left") {
    click = ivec2(11, 31);
    expected_hsv = vec3(0.0f, 0.5f, 1.0f);
  }
  SECTION("Right") {
    click = ivec2(70, 31);
    expected_hsv = vec3(59.0f/60.0f, 0.5f, 1.0f);
  }
  SECTION("Corner") {
    click = ivec2(11, 11);
    expected_hsv = vec3(0.0f, 1.0f, 1.0f);
  }

  REQUIRE(selector.WasEdited(click));
  selector.ChangeColor(click);
  vec3 hsv = selector.GetColor().get(ci::ColorModel::CM_HSV);
  REQUIRE(roundToFourPlaces(hsv) == roundToFourPlaces(expected_hsv));
}

TEST_CASE("Editing value slider") {
  ColorSelector selector(ivec2(1, 1), ivec2(80, 100));
  selector.ChangeColor(ivec2(11, 11));
  REQUIRE(selector.GetColor().get(ci::ColorModel::CM_HSV) == vec3(0.0f, 1.0f, 1.0f));

  ivec2 click;
  vec3 expected_hsv;

  SECTION("Top") {
    click = ivec2(41, 61);
    expected_hsv = vec3(0.0f, 1.0f, 0.5f);
  }
  SECTION("Bottom") {
    click = ivec2(41, 70);
    expected_hsv = vec3(0.0f, 1.0f, 0.5f);
  }
  SECTION("Left") {
    click = ivec2(11, 66);
    expected_hsv = vec3(0.0f, 0.0f, 0.0f);
  }
  SECTION("Right") {
    click = ivec2(70, 66);
    expected_hsv = vec3(0.0f, 1.0f, 59.0f/60.0f);
  }
  SECTION("Corner") {
    click = ivec2(11, 61);
    expected_hsv = vec3(0.0f, 0.0f, 0.0f);
  }

  REQUIRE(selector.WasEdited(click));
  selector.ChangeColor(click);
  REQUIRE(selector.GetColor().get(ci::ColorModel::CM_HSV) == expected_hsv);
}

TEST_CASE("Check clicks that don't edit color") {
  ColorSelector selector(ivec2(1, 1), ivec2(80, 100));
  ivec2 click;

  SECTION("Top") {
    click = ivec2(41, 0);
  }
  SECTION("Bottom") {
    click = ivec2(41, 101);
  }
  SECTION("Left") {
    click = ivec2(0, 31);
  }
  SECTION("Right") {
    click = ivec2(81, 31);
  }
  SECTION("Corner") {
    click = ivec2(0, 0);
  }
  SECTION("Inside but not on slider or palette") {
    click = ivec2(41, 55);
  }

  REQUIRE_FALSE(selector.WasEdited(click));
}