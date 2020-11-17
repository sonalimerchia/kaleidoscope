#include <visualizer/kaleidoscope_app.h>

namespace kaleidoscope {

namespace visualizer {

using ci::app::MouseEvent;
using ci::app::KeyEvent;

void KaleidoscopeApp::mouseUp(MouseEvent event) {
  // Add stroke to app, refresh maker
  strokes_.push_back(maker_.GetStroke());
  maker_.clear();
  needs_refresh_ = true;
}

void KaleidoscopeApp::mouseDrag(MouseEvent event) {
  maker_.AddPointToStroke(event.getPos());
}

void KaleidoscopeApp::mouseDown(MouseEvent event) {
  maker_.StartNewStroke(event.getPos());
}

void KaleidoscopeApp::draw() {
  // Draw stroke in progress unless you need to refresh. In which case, draw all
  if (needs_refresh_) {
    pad_.draw(strokes_);
    needs_refresh_ = false;
  } else {
    pad_.draw(maker_.GetStroke());
  }
}

void KaleidoscopeApp::setup() {
  setWindowSize(1000, 750);

  // Set Up Pad
  pad_.SetBackground(ci::Color("white"));

  // Set up maker
  maker_.SetBrushSize(3);
  maker_.SetColor(ci::Color("blue"));
  maker_.SetNumSectors(7);
  maker_.SetCenter(getWindowSize()/2);

  needs_refresh_ = true;
}

void KaleidoscopeApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_BACKSPACE) {
    strokes_.clear();
    maker_.clear();
    needs_refresh_ = true;
  }
}

}

}