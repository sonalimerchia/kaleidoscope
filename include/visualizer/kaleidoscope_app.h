#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "sketchpad.h"
#include "core/stroke.h"
#include "core/stroke_maker.h"
#include "toolbar.h"
#include "core/command_type.h"

#ifndef KALEIDOSCOPE_INCLUDE_KALEIDOSCOPE_APP_H_
#define KALEIDOSCOPE_INCLUDE_KALEIDOSCOPE_APP_H_

namespace kaleidoscope {

namespace visualizer {

class KaleidoscopeApp : public ci::app::App {

 public:
  static size_t kWindowHeight;
  static size_t kWindowWidth;

  /**
   * Sets up the field variables of the app
   */
  void setup() override;

  /**
   * draws the contents of the app
   */
  void draw() override;

  /**
   * start a new stroke at the location where the MouseEvent occurred
   * @param event the information about the place where the mouse clicked down
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /**
   * move the stroke being made from the StrokeMaker to the app's strokes and
   * resetting the StrokeMaker to be blank.
   * @param event the information about the place where the mouse was released
   */
  void mouseUp(ci::app::MouseEvent event) override;

  /**
   * Add the current location of the mouse to the stroke being made
   * @param event the information about the place where the mouse currently is
   */
  void mouseDrag(ci::app::MouseEvent event) override;

  /**
   * Clears the sketchpad when you click backspace
   * @param event the information about the key being clicked down
   */
  void keyDown(ci::app::KeyEvent event) override;

 private:
  Sketchpad pad_;
  Toolbar tools_;
  bool needs_refresh_;

  void ManageCommand(const CommandType &command);
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_KALEIDOSCOPE_APP_H_
