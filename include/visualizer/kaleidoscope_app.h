#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "visualizer/sketchpad.h"
#include "visualizer/toolbar.h"
#include "core/command_type.h"

#include <string>

#ifndef KALEIDOSCOPE_INCLUDE_KALEIDOSCOPE_APP_H_
#define KALEIDOSCOPE_INCLUDE_KALEIDOSCOPE_APP_H_

namespace kaleidoscope {

namespace visualizer {

using ci::app::App;
using ci::app::MouseEvent;
using ci::app::KeyEvent;

class KaleidoscopeApp : public App {

 public:
  static const size_t kWindowHeight;
  static const size_t kWindowWidth;
  static const std::string kImagesFolderPath;
  static const std::string kDefaultImageExtension;

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
  void mouseDown(MouseEvent event) override;

  /**
   * move the stroke being made from the StrokeMaker to the app's strokes and
   * resetting the StrokeMaker to be blank.
   * @param event the information about the place where the mouse was released
   */
  void mouseUp(MouseEvent event) override;

  /**
   * Add the current location of the mouse to the stroke being made
   * @param event the information about the place where the mouse currently is
   */
  void mouseDrag(MouseEvent event) override;

  /**
   * Clears the sketchpad when you click backspace
   * @param event the information about the key being clicked down
   */
  void keyDown(KeyEvent event) override;

 private:
  Sketchpad pad_;
  Toolbar toolbar_;

  /**
   * Changes the sketchpad and settings as if a command of the given command type
   * has just been given
   * @param command the type of command given
   */
  void ManageCommand(const CommandType &command);
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_KALEIDOSCOPE_APP_H_
