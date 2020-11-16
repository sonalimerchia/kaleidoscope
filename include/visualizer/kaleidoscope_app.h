#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "sketchpad.h"
#include "core/stroke.h"
#include "core/stroke_maker.h"

#ifndef FINAL_PROJECT_SONALIMERCHIA_INCLUDE_KALEIDOSCOPE_H_
#define FINAL_PROJECT_SONALIMERCHIA_INCLUDE_KALEIDOSCOPE_H_

namespace kaleidoscope {

class KaleidoscopeApp : public ci::app::App {
 public:
  void setup() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseUp(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;

 private:
  Sketchpad pad_;
  std::vector<stroke> strokes_;
  StrokeMaker maker_;
  bool needs_refresh_;
};

}

#endif //FINAL_PROJECT_SONALIMERCHIA_INCLUDE_KALEIDOSCOPE_H_
